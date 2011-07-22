#pragma once

#include <COG/cog.h>

namespace cog{
  
  inline bool _test
  (vec_float x, 
   vec_float (*f)(vec_float), 
   float (*g)(float) )
  {
    vec_float result = f(x);
    
    const float* inx = (float*)&x;
    const float* res = (float*)&result;
    
    for(int i=0; i<(int)VEC_FLOAT_LENGTH; i++){
      float r = g(inx[i]);
      if( abs(res[i] - r) > FLOAT_ERROR_TOLERANCE )
        return false;
    }
    
    return true;
  }
  
  inline bool _test
  (vec_float x, vec_float y, 
   vec_float (*f)(vec_float, vec_float), 
   float (*g)(float, float) )
  {
    vec_float result = f(x, y);
    
    const float* inx = (float*)&x;
    const float* iny = (float*)&y;
    const float* res = (float*)&result;
    
    for(int i=0; i<(int)VEC_FLOAT_LENGTH; i++){
      float r = g(inx[i], iny[i]);
      if( abs(res[i] - r) > FLOAT_ERROR_TOLERANCE )
        return false;
    }
    
    return true;
  }
  
  inline bool _test
  (vec_float x, vec_float y, vec_float z, 
   vec_float (*f)(vec_float, vec_float, vec_float), 
   float (*g)(float, float, float) )
  {
    vec_float result = f(x, y, z);
    
    const float* inx = (float*)&x;
    const float* iny = (float*)&y;
    const float* inz = (float*)&z;
    const float* res = (float*)&result;
    
    for(int i=0; i<(int)VEC_FLOAT_LENGTH; i++){
      float r = g(inx[i], iny[i], inz[i]);
      if( abs(res[i] - r) > FLOAT_ERROR_TOLERANCE )
        return false;
    }
    
    return true;
  }
  
  inline bool _test(float c, float ex)
  {
    if(abs(c-ex)>FLOAT_ERROR_TOLERANCE)
      return false;
    return true;
  }
  
}

namespace cog{
  
  typedef basic_vector3<float> vec3;
  typedef basic_vector4<float> vec4;
  
  inline bool _test(const vec3& c, float ex, float ey, float ez)
  {
    if(abs(c.getX()-ex)>FLOAT_ERROR_TOLERANCE)
      return false;
    if(abs(c.getY()-ey)>FLOAT_ERROR_TOLERANCE)
      return false;
    if(abs(c.getZ()-ez)>FLOAT_ERROR_TOLERANCE)
      return false;
    return true;
  }
  
  inline bool _test(const vec4& c, float ex, float ey, float ez, float ew)
  {
    if(abs(c.getX()-ex)>FLOAT_ERROR_TOLERANCE)
      return false;
    if(abs(c.getY()-ey)>FLOAT_ERROR_TOLERANCE)
      return false;
    if(abs(c.getZ()-ez)>FLOAT_ERROR_TOLERANCE)
      return false;
    if(abs(c.getW()-ew)>FLOAT_ERROR_TOLERANCE)
      return false;
    return true;
  }
  
  inline bool _test(const vec3& c, const vec3& ex)
  {
    return _test(c, ex.getX(), ex.getY(), ex.getZ());
  }
  
  inline bool _test(const vec4& c, const vec4& ex)
  {
    return _test(c, ex.getX(), ex.getY(), ex.getZ(), ex.getW());
  }
  
}

namespace cog{
  
  typedef basic_matrix3<float> mat3;
  typedef basic_matrix4<float> mat4;
  
  inline bool _test
  (const mat3& c, const vec3& v0, const vec3& v1, const vec3& v2)
  {
    if(!_test(c.getColumn0(), v0))
      return false;
    if(!_test(c.getColumn1(), v1))
      return false;
    if(!_test(c.getColumn2(), v2))
      return false;
    return true;
  }
  
  inline bool _test
  (const mat4& c, const vec4& v0,const vec4& v1,const vec4& v2,const vec4& v3)
  {
    if(!_test(c.getColumn0(), v0))
      return false;
    if(!_test(c.getColumn1(), v1))
      return false;
    if(!_test(c.getColumn2(), v2))
      return false;
    if(!_test(c.getColumn3(), v3))
      return false;
    return true;
  }
  
  inline bool _test(const mat3& c, const mat3& ex)
  {
    return _test(c, ex.getColumn0(), ex.getColumn1(), ex.getColumn2());
  }
  
  inline bool _test(const mat4& c, const mat4& ex)
  {
    return _test(c, ex.getColumn0(), ex.getColumn1(), 
                 ex.getColumn2(), ex.getColumn3());
  }
  
}

namespace cog{
  
  typedef basic_quaternion<float> quat;
  
  inline bool _test
  (const quat& c, const vec3& v, float w)
  {
    if(!_test(c.getV(), v))
      return false;
    if(!_test(c.getW(), w))
      return false;
    return true;
  }
  
  inline bool _test
  (const quat& c, const quat& ex)
  {
    return _test(c, ex.getV(), ex.getW());
  }
  
}

namespace cog{
  
  typedef basic_dualquat<float> dualquat;
  
  inline bool _test
  (const dualquat& c, const quat& q0, const quat& qe)
  {
    if(!_test(c.getQ0(), q0))
      return false;
    if(!_test(c.getQe(), qe))
      return false;
    return true;
  }
  
  inline bool _test
  (const dualquat& c, const dualquat& ex)
  {
    return _test(c, ex.getQ0(), ex.getQe());
  }
  
}
