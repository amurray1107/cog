#include <COG/vmath_base.h>

#ifdef __X86_SSE__

namespace cog{
  const float _SINCOSF_CC0 = -0.0013602249f;
  const float _SINCOSF_CC1 =  0.0416566950f;
  const float _SINCOSF_CC2 = -0.4999990225f;
  const float _SINCOSF_SC0 = -0.0001950727f;
  const float _SINCOSF_SC1 =  0.0083320758f;
  const float _SINCOSF_SC2 = -0.1666665247f;
  const float _SINCOSF_KC1 = 1.57079625129f;
  const float _SINCOSF_KC2 = 7.54978995489e-8f;
  
  inline __m128 _mm_signbit_ps(__m128 x)
  {
    return _i2f(_mm_srai_epi32(_f2i(x), 31));
  }
  
  inline vec_float _fill(float x)
  {
    return _mm_set1_ps(x);
  }
  
}

namespace cog{
  
  vec_float recip(vec_float x)
  {
    const __m128 one = _fill(1.0f);
    const __m128 y0 = _mm_rcp_ps(x);
    __m128 y = nmsub(x, y0, one);
    y = madd(y, y0, y0);
    return y;
  }
  
  vec_float rsqrt(vec_float x)
  {
    const __m128 y0 = _mm_rsqrt_ps(x);
    const __m128 y0x = mul(y0, x);
    __m128 y0half = mul(y0, _fill(0.5f));
    __m128 y1nmsub = nmsub(y0, y0x, _fill(1.0f));
    __m128 y2madd = madd(y1nmsub, y0half, y0);
    return y2madd;
  }
  
  vec_float acos(vec_float x)
  {
    const __m128 select = _mm_signbit_ps(x);
    const __m128 xabs = abs(x);
    
    const __m128 t1 = sqrt(sub(_fill(1.0f), xabs));
    
    /* Instruction counts can be reduced if the polynomial was
     * computed entirely from nested (dependent) fma's. However, 
     * to reduce the number of pipeline stalls, the polygon is evaluated 
     * in two halves (hi amd lo). 
     */
    const __m128 xabs2 = mul(xabs,  xabs);
    const __m128 xabs4 = mul(xabs2, xabs2);
    __m128 hi, lo;
    hi = madd(_fill(-0.0012624911f) , xabs, _fill(0.0066700901f));
    hi = madd(hi, xabs, _fill(-0.0170881256f));
    hi = madd(hi, xabs, _fill( 0.0308918810f));
    lo = madd(_fill(-0.0501743046f), xabs, _fill(0.0889789874f));
    lo = madd(lo, xabs, _fill(-0.2145988016f));
    lo = madd(lo, xabs, _fill( 1.5707963050f));
    
    __m128 result = madd(hi, xabs4, lo);
    
    // Adjust the result if x is negactive.
    const __m128 neg = nmsub(t1, result, _fill(3.1415926535898f));
    const __m128 pos = mul(t1, result);
    
    result = _mm_sel_ps(pos, neg, select);
    
    return result;
  }
  
  vec_float floor(vec_float x)
  {
    const __m128 xacmp = _i2f(_mm_set1_epi32(0x4b000000));
    const __m128 inrange = _mm_cmpgt_ps(xacmp, abs(x));
    const __m128i xi = _mm_cvttps_epi32(x);
    const __m128i xi1 = _mm_sub_epi32(xi, _mm_set1_epi32(1));
    const __m128 truncated0 = _mm_sel_ps(x, _mm_cvtepi32_ps(xi), inrange);
    const __m128 truncated1 = _mm_sel_ps(x, _mm_cvtepi32_ps(xi1), inrange);
    const __m128 resel = _mm_cmpgt_ps(truncated0, x);
    return _mm_sel_ps(truncated0, truncated1, resel);
  }
  
  void _sincos(vec_float x, vec_float& s, vec_float& c)
  {
    __m128 xl;
    __m128 ts, tc, sx, cx;
    
    // Range reduction using : xl = angle * TwoOverPi;
    xl = mul(x, _fill( 0.63661977236f) );
    xl = add(xl, copysign( _fill(0.5f), xl) );
    
    // Find the quadrant the angle falls in
    // using:  q = (int) (ceil(abs(xl))*sign(xl))
    const __m128i q = _mm_cvttps_epi32(xl);
    
    // Compute the offset based on the quadrant that the angle falls in.
    // Add 1 to the offset for the cosine. 
    const __m128i offsetSin = _mm_and_si128(q, _mm_set1_epi32(0x3));
    const __m128i offsetCos = _mm_add_epi32(offsetSin, _mm_set1_epi32(1));
    
    // Remainder in range [-pi/4..pi/4]
    const __m128 qf = _mm_cvtepi32_ps(q);
    const __m128 p1 = nmsub(qf, _fill(_SINCOSF_KC1), x);
    xl = nmsub(qf, _fill(_SINCOSF_KC2), p1);
    
    // Compute x^2 and x^3
    const __m128 xl2 = mul(xl, xl);
    const __m128 xl3 = mul(xl, xl2);
    
    // Compute both the sin and cos of the angles
    // using a polynomial expression:
    //   cx = 1.0f + xl2 * ((C0 * xl2 + C1) * xl2 + C2), and
    //   sx = xl + xl3 * ((S0 * xl2 + S1) * xl2 + S2)
    {
      __m128 ct1 = madd(_fill(_SINCOSF_CC0), xl2, _fill(_SINCOSF_CC1));
      __m128 st1 = madd(_fill(_SINCOSF_SC0), xl2, _fill(_SINCOSF_SC1));
      __m128 ct2 = madd(ct1, xl2, _fill(_SINCOSF_CC2));
      __m128 st2 = madd(st1, xl2, _fill(_SINCOSF_SC2));
      cx = madd(ct2, xl2, _fill(1.0f));
      sx = madd(st2, xl3, xl);
    }
    
    // Use the cosine when the offset is odd and the sin
    // when the offset is even
    //
    // Flip the sign of the result when (offset mod 4) = 1 or 2
    //
    {
      const __m128i vi_0 = _mm_setzero_si128();
      const __m128i vi_1 = _mm_set1_epi32(0x1);
      const __m128i vi_2 = _mm_set1_epi32(0x2);
      __m128 sinMask, cosMask;
      sinMask = _i2f(_mm_cmpeq_epi32(_mm_and_si128(offsetSin, vi_1), vi_0));
      cosMask = _i2f(_mm_cmpeq_epi32(_mm_and_si128(offsetCos, vi_1), vi_0));
      ts = _mm_sel_ps(cx,sx,sinMask);
      tc = _mm_sel_ps(cx,sx,cosMask);
      
      sinMask = _i2f(_mm_cmpeq_epi32(_mm_and_si128(offsetSin, vi_2), vi_0));
      cosMask = _i2f(_mm_cmpeq_epi32(_mm_and_si128(offsetCos, vi_2), vi_0));
      ts = _mm_sel_ps(negate(ts), ts, sinMask);
      tc = _mm_sel_ps(negate(tc), tc, cosMask);
    }
    
    s = ts;
    c = tc;
  }
  
  vec_float mod(vec_float a, vec_float b)
  {
    vec_float c = floor(div(a, b));
    return sub(a, mul(c, b));
  }
  
}

#include <cog/vmath_const.h>
#include <cog/vmath_vector.h>

namespace cog{
  
  /////////////////////////////////////////////////
  
  /*
   
   XMM REGISTER:
   
   127    95     63     31     0
   | r[3] | r[2] | r[1] | r[0] | = { r[0], r[1], r[2], r[3] } (IN MEMORY)
   |  z   |  y   |  x   |  w   | = { w, x, y, z }
   
   
   SHUFFLE (SWIZZLING)
   
   _mm_shuffle_ps(r, s, _MM_SHUFFLE(0,1,2,3)) = { r[3], r[2], s[1], s[0] }
   
   */
  
  /////////////////////////////////////////////////
  
  void convert(basic_vector3<vec_float>& soa, const basic_vector3<float>* aos)
  {
    __m128 a0 = _mm_load_ps((float*)aos);
    __m128 a1 = _mm_load_ps((float*)aos+4);
    __m128 a2 = _mm_load_ps((float*)aos+8);
    
    __m128 m0 = _mm_shuffle_ps(a0, a1, _MM_SHUFFLE(1,0,2,1));
    __m128 m1 = _mm_shuffle_ps(a1, a2, _MM_SHUFFLE(2,1,3,2));
    
    a0 = _mm_shuffle_ps(a0, m1, _MM_SHUFFLE(2,0,3,0));
    a1 = _mm_shuffle_ps(m0, m1, _MM_SHUFFLE(3,1,2,0));
    a2 = _mm_shuffle_ps(m0, a2, _MM_SHUFFLE(3,0,3,1));
    
    soa = basic_vector3<vec_float>(a0, a1, a2);
  }
  
  void convert(basic_vector3<float>* aos, const basic_vector3<vec_float>& soa)
  {
    __m128 a0 = soa.getX();
    __m128 a1 = soa.getY();
    __m128 a2 = soa.getZ();
    
    __m128 m0 = _mm_shuffle_ps(a0, a1, _MM_SHUFFLE(2,0,2,0));
    __m128 m1 = _mm_shuffle_ps(a2, a0, _MM_SHUFFLE(3,1,2,0));
    __m128 m2 = _mm_shuffle_ps(a1, a2, _MM_SHUFFLE(3,1,3,1));
    
    a0 = _mm_shuffle_ps(m0, m1, _MM_SHUFFLE(2,0,2,0));
    a1 = _mm_shuffle_ps(m2, m0, _MM_SHUFFLE(3,1,2,0));
    a2 = _mm_shuffle_ps(m1, m2, _MM_SHUFFLE(3,1,3,1));
    
    _mm_store_ps((float*)aos, a0);
    _mm_store_ps((float*)aos+4, a1);
    _mm_store_ps((float*)aos+8, a2);
  }
  
  inline void _transpose(__m128& a0, __m128& a1, __m128& a2, __m128& a3)
  {
    __m128 tmp0, tmp1, tmp2, tmp3;
    
    tmp0 = _mm_unpacklo_ps(a0, a2);
    tmp1 = _mm_unpacklo_ps(a1, a3);
    tmp2 = _mm_unpackhi_ps(a0, a2);
    tmp3 = _mm_unpackhi_ps(a1, a3);
    
    a0 = _mm_unpacklo_ps(tmp0, tmp1);
    a1 = _mm_unpackhi_ps(tmp0, tmp1);
    a2 = _mm_unpacklo_ps(tmp2, tmp3);
    a3 = _mm_unpackhi_ps(tmp2, tmp3);
  }
  
  void convert(basic_vector4<vec_float>& soa, const basic_vector4<float>* aos)
  {
    __m128 a0 = _mm_load_ps((float*)aos);
    __m128 a1 = _mm_load_ps((float*)aos+4);
    __m128 a2 = _mm_load_ps((float*)aos+8);
    __m128 a3 = _mm_load_ps((float*)aos+12);
    
    _transpose(a0, a1, a2, a3);
    
    soa = basic_vector4<vec_float>(a0, a1, a2, a3);
  }
  
  void convert(basic_vector4<float>* aos, const basic_vector4<vec_float>& soa)
  {
    __m128 a0 = soa.getX();
    __m128 a1 = soa.getY();
    __m128 a2 = soa.getZ();
    __m128 a3 = soa.getW();
    
    _transpose(a0, a1, a2, a3);
    
    _mm_store_ps((float*)aos, a0);
    _mm_store_ps((float*)aos+4, a1);
    _mm_store_ps((float*)aos+8, a2);
    _mm_store_ps((float*)aos+12, a3);
  }
  
}

#endif
