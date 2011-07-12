#pragma once

#include <float.h>

// MARK: float op

namespace cog{
  
  // Properties of Single Precision Float Type
  const float FLOAT_EPSILON = FLT_EPSILON;
  const float FLOAT_MIN = FLT_MIN;
  const float FLOAT_MAX = FLT_MAX;
  
  // Some math constants
  const float FLOAT_ERROR_TOLERANCE = 0.0001f;
  
  /////////////
  
  /// Basic Arithmetic Operators
  
  // // @ Private Members
  
  union _f32_union{
    float typeF;
    int typeI;
  };
  
  inline float _i2f(int x)
  {
    _f32_union u; u.typeI = x;
    return u.typeF;
  }
  
  inline int _f2i(float x)
  {
    _f32_union u; u.typeF = x;
    return u.typeI;
  }
  
  // // @ Public Members
  
  inline float abs(float x)
  {
    return _i2f( _f2i(x) & 0x7fffffff );
  }
  
  inline float negate(float x)
  {
    return -x;
  }
  
  inline float add(float a, float b)
  {
    return a + b;
  }
  
  inline float sub(float a, float b)
  {
    return a - b;
  }
  
  inline float mul(float a, float b)
  {
    return a * b;
  }
  
  inline float madd(float a, float b, float c)
  {
    return a * b + c;
  }
  
  inline float nmsub(float a, float b, float c)
  {
    return c - a * b;
  }
  
  inline float min(float x, float y)
  {
    return (x < y ? x : y);
  }
  
  inline float max(float x, float y)
  {
    return (x > y ? x : y);
  }
  
  /// Composited Arithmetic Operators
  
  inline float recip(float x)
  {
    return 1.0f / x;
  }
  
  inline float div(float a, float b)
  {
    return a / b;
  }
  
  inline float rsqrt(float x)
  {
    extern float _sqrt(float);
    return 1.0f / _sqrt(x);
  }
  
  inline float sqrt(float x)
  {
    extern float _sqrt(float);
    return _sqrt(x);
  }
  
  extern float floor(float x);
  
  extern float acos(float x);
  
  extern float sin(float x);
  
  extern float cos(float x);
  
  extern float tan(float x);
  
  inline float mod(float a, float b)
  {
    return a - b * floor(a/b);
  }
  
  inline float copysign(float x, float y)
  {
    return _i2f((_f2i(x) & 0x7fffffff) | (_f2i(y) & 0x80000000));
  }
  
}

// MARK: some func

namespace cog{
  
  template<typename V>
  inline const V lerp(const V& v0, const V& v1, typename V::scalar_type s)
  {
    return v0 + ((v1-v0) * s);
  }
  
  template<typename V>
  inline typename V::scalar_type lengthSqr(const V& v)
  {
    return dot(v, v);
  }
  
  template<typename V>
  inline typename V::scalar_type length(const V& v)
  {
    return sqrt(lengthSqr(v));
  }
  
  template<typename V>
  inline const V normalize(const V& v)
  {
    return v * rsqrt(lengthSqr(v));
  }
  
}

// MARK: SIMD op

#ifdef __SSE__
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
  
  void convert(basic_vector3<vec_float>& soa, const basic_vector3<float>* aos);
  
  void convert(basic_vector3<float>* aos, const basic_vector3<vec_float>& soa);
  
  void convert(basic_vector4<vec_float>& soa, const basic_vector4<float>* aos);
  
  void convert(basic_vector4<float>* aos, const basic_vector4<vec_float>& soa);
  
}

