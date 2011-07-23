#ifndef __X86_SSE__
#  error _float_sse.h is included while SSE is not supported
#endif

#ifndef __X86_SSE2__
#  error _float_sse.h is included while SSE2 is not supported
#endif

#include <xmmintrin.h>
#include <emmintrin.h>

namespace cog{
  
  //
  typedef __m128 VF32;
  
  //
  const size_t VF32_LENGTH = sizeof(VF32)/sizeof(F32);
  
  //
  inline VF32 splats(F32 s)
  {
    return _mm_set1_ps(s);
  }
  
  // @Private Member
  
  union _vec_float_union{
    __m128 typeF;
    __m128i typeI;
  };
  
  inline __m128 _i2f(__m128i x)
  {
    _vec_float_union u; u.typeI = x;
    return u.typeF;
  }
  
  inline __m128i _f2i(__m128 x)
  {
    _vec_float_union u; u.typeF = x;
    return u.typeI;
  }
  
  inline __m128 _mm_sel_ps(__m128 x, __m128 y, __m128 s)
  {
    __m128 mx = _mm_andnot_ps(s, x);
    __m128 my = _mm_and_ps(s, y);
    return _mm_or_ps(mx, my);
  }
  
  // @Public Member
  
  inline VF32 abs(VF32 x)
  {
    return _mm_andnot_ps(_mm_set1_ps(-0.0f), x);
  }
  
  inline VF32 negate(VF32 x)
  {
    return _mm_xor_ps(_mm_set1_ps(-0.0f), x);
  }
  
  inline VF32 add(VF32 a, VF32 b)
  {
    return _mm_add_ps(a, b);
  }
  
  inline VF32 sub(VF32 a, VF32 b)
  {
    return _mm_sub_ps(a, b);
  }
  
  inline VF32 mul(VF32 a, VF32 b)
  {
    return _mm_mul_ps(a, b);
  }
  
  inline VF32 madd(VF32 a, VF32 b, VF32 c)
  {
    return _mm_add_ps(c, _mm_mul_ps(a, b));
  }
  
  inline VF32 nmsub(VF32 a, VF32 b, VF32 c)
  {
    return _mm_sub_ps(c, _mm_mul_ps(a, b));
  }
  
  inline VF32 min(VF32 a, VF32 b)
  {
    return _mm_min_ps(a, b);
  }
  
  inline VF32 max(VF32 a, VF32 b)
  {
    return _mm_max_ps(a, b);
  }
  
  //
  
  extern VF32 recip(VF32 x);
  extern VF32 rsqrt(VF32 x);
  extern VF32 acos(VF32 x);
  extern VF32 floor(VF32 x);
  extern VF32 mod(VF32 a, VF32 b);
  
  //
  
  inline VF32 div(VF32 a, VF32 b)
  {
    return _mm_div_ps(a, b);
  }
  
  inline VF32 sqrt(VF32 x)
  {
    return mul(x, rsqrt(x));
  }
  
  inline VF32 sin(VF32 x)
  {
    extern void _sincos(VF32 x, VF32& s, VF32& c);
    
    VF32 s, c;
    _sincos(x, s, c);
    return s;
  }
  
  inline VF32 cos(VF32 x)
  {
    extern void _sincos(VF32 x, VF32& s, VF32& c);
    
    VF32 s, c;
    _sincos(x, s, c);
    return c;
  }
  
  inline VF32 tan(VF32 x)
  {
    extern void _sincos(VF32 x, VF32& s, VF32& c);
    
    VF32 s, c;
    _sincos(x, s, c);
    return div(s, c);
  }
  
  inline VF32 copysign(VF32 x, VF32 y)
  {
    return _mm_sel_ps(x, y, _mm_set1_ps(-0.0f));
  }
  
  // 
}
