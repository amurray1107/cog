#pragma once

#include "base_type.h"

#include <float.h>

// MARK: float op

namespace cog{
  
  // Properties of Single Precision Float Type
  const F32 FLOAT_EPSILON = FLT_EPSILON;
  const F32 FLOAT_MIN = FLT_MIN;
  const F32 FLOAT_MAX = FLT_MAX;
  
  // Some math constants
  const F32 FLOAT_ERROR_TOLERANCE = 0.0001f;
  
  /////////////
  
  /// Basic Arithmetic Operators
  
  // // @ Private Members
  
  union _f32_union{
    F32 typeF;
    I32 typeI;
  };
  
  inline F32 _i2f(I32 x)
  {
    _f32_union u; u.typeI = x;
    return u.typeF;
  }
  
  inline I32 _f2i(F32 x)
  {
    _f32_union u; u.typeF = x;
    return u.typeI;
  }
  
  // // @ Public Members
  
  inline F32 abs(F32 x)
  {
    return _i2f( _f2i(x) & 0x7fffffff );
  }
  
  inline F32 negate(F32 x)
  {
    return -x;
  }
  
  inline F32 add(F32 a, F32 b)
  {
    return a + b;
  }
  
  inline F32 sub(F32 a, F32 b)
  {
    return a - b;
  }
  
  inline F32 mul(F32 a, F32 b)
  {
    return a * b;
  }
  
  inline F32 madd(F32 a, F32 b, F32 c)
  {
    return a * b + c;
  }
  
  inline F32 nmsub(F32 a, F32 b, F32 c)
  {
    return c - a * b;
  }
  
  inline F32 min(F32 x, F32 y)
  {
    return (x < y ? x : y);
  }
  
  inline F32 max(F32 x, F32 y)
  {
    return (x > y ? x : y);
  }
  
  /// Composited Arithmetic Operators
  
  inline F32 recip(F32 x)
  {
    return 1.0f / x;
  }
  
  inline F32 div(F32 a, F32 b)
  {
    return a / b;
  }
  
  inline F32 rsqrt(F32 x)
  {
    extern F32 _sqrt(F32);
    return 1.0f / _sqrt(x);
  }
  
  inline F32 sqrt(F32 x)
  {
    extern F32 _sqrt(F32);
    return _sqrt(x);
  }
  
  extern F32 floor(F32 x);
  
  extern F32 acos(F32 x);
  
  extern F32 sin(F32 x);
  
  extern F32 cos(F32 x);
  
  extern F32 tan(F32 x);
  
  inline F32 mod(F32 a, F32 b)
  {
    return a - b * floor(a/b);
  }
  
  inline F32 copysign(F32 x, F32 y)
  {
    return _i2f((_f2i(x) & 0x7fffffff) | (_f2i(y) & 0x80000000));
  }
  
}

// MARK: SIMD op

#ifdef __X86_SSE__
#  include "vmath_base_sse.h"
#endif

// MARK: Vector Math prototypes

namespace cog{
  
  template<typename T> class basic_vector3;
  template<typename T> class basic_vector4;
  template<typename T> class basic_matrix3;
  template<typename T> class basic_matrix4;
  template<typename T> class basic_quaternion;
  template<typename T> class basic_dualquat;
  
}

// MARK: AOS v.s. SOA

namespace cog{
  
  void convert(basic_vector3<VF32>& soa, const basic_vector3<F32>* aos);
  
  void convert(basic_vector3<F32>* aos, const basic_vector3<VF32>& soa);
  
  void convert(basic_vector4<VF32>& soa, const basic_vector4<F32>* aos);
  
  void convert(basic_vector4<F32>* aos, const basic_vector4<VF32>& soa);
  
}

