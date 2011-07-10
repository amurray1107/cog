#include <cfloat>
#include <cmath>
#include <algorithm>

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
  
  inline float abs(float x)
  {
    return std::fabs(x);
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
    return std::min(x, y);
  }
  
  inline float max(float x, float y)
  {
    return std::max(x, y);
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
    return 1.0f / std::sqrt(x);
  }
  
  inline float sqrt(float x)
  {
    return std::sqrt(x);
  }
  
  inline float floor(float x)
  {
    return std::floor(x);
  }
  
  inline float acos(float x)
  {
    return std::acos(x);
  }
  
  inline float sin(float x)
  {
    return std::sin(x);
  }
  
  inline float cos(float x)
  {
    return std::cos(x);
  }
  
  inline float tan(float x)
  {
    return std::tan(x);
  }
  
  inline float mod(float a, float b)
  {
    return a - b * std::floor(a/b);
  }
  
}

// MARK: const prototype
namespace cog{
  
  namespace
  {
    template<typename T>
    struct const_{
      //
    };
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
