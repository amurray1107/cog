#ifndef __SSE__
#  error _float_sse.h is included while SSE is not supported
#endif

#ifndef __SSE2__
#  error _float_sse.h is included while SSE2 is not supported
#endif

#include <xmmintrin.h>
#include <emmintrin.h>

namespace cog{
  
  //
  typedef __m128 vec_float;
  
  //
  const size_t VEC_FLOAT_LENGTH = sizeof(vec_float)/sizeof(float);
  
  //
  inline vec_float splats(float s)
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
  
  inline vec_float abs(vec_float x)
  {
    return _mm_andnot_ps(_mm_set1_ps(-0.0f), x);
  }
  
  inline vec_float negate(vec_float x)
  {
    return _mm_xor_ps(_mm_set1_ps(-0.0f), x);
  }
  
  inline vec_float add(vec_float a, vec_float b)
  {
    return _mm_add_ps(a, b);
  }
  
  inline vec_float sub(vec_float a, vec_float b)
  {
    return _mm_sub_ps(a, b);
  }
  
  inline vec_float mul(vec_float a, vec_float b)
  {
    return _mm_mul_ps(a, b);
  }
  
  inline vec_float madd(vec_float a, vec_float b, vec_float c)
  {
    return _mm_add_ps(c, _mm_mul_ps(a, b));
  }
  
  inline vec_float nmsub(vec_float a, vec_float b, vec_float c)
  {
    return _mm_sub_ps(c, _mm_mul_ps(a, b));
  }
  
  inline vec_float min(vec_float a, vec_float b)
  {
    return _mm_min_ps(a, b);
  }
  
  inline vec_float max(vec_float a, vec_float b)
  {
    return _mm_max_ps(a, b);
  }
  
  //
  
  extern vec_float recip(vec_float x);
  extern vec_float rsqrt(vec_float x);
  extern vec_float acos(vec_float x);
  extern vec_float floor(vec_float x);
  extern vec_float mod(vec_float a, vec_float b);
  
  //
  
  inline vec_float div(vec_float a, vec_float b)
  {
    return _mm_div_ps(a, b);
  }
  
  inline vec_float sqrt(vec_float x)
  {
    return mul(x, rsqrt(x));
  }
  
  inline vec_float sin(vec_float x)
  {
    extern void _sincos(vec_float x, vec_float& s, vec_float& c);
    
    vec_float s, c;
    _sincos(x, s, c);
    return s;
  }
  
  inline vec_float cos(vec_float x)
  {
    extern void _sincos(vec_float x, vec_float& s, vec_float& c);
    
    vec_float s, c;
    _sincos(x, s, c);
    return c;
  }
  
  inline vec_float tan(vec_float x)
  {
    extern void _sincos(vec_float x, vec_float& s, vec_float& c);
    
    vec_float s, c;
    _sincos(x, s, c);
    return div(s, c);
  }
  
  inline vec_float copysign(vec_float x, vec_float y)
  {
    return _mm_sel_ps(x, y, _mm_set1_ps(-0.0f));
  }
  
  // 
}
