#include "unit_test.h"

using namespace cog;

int main()
{
  const F32 PI = 3.141592653589793f;
  
  // Test: make_rotate (radian + axis)
  {
    mat3 p;
    for(F32 r= -PI; r<=PI; r+=PI*0.5f){
      p = make_rotate(r, vec3(1.0f, 0.0f, 0.0f));
      p = make_rotate(r, vec3(0.0f, 1.0f, 0.0f));
      p = make_rotate(r, vec3(0.0f, 0.0f, 1.0f));
    }
  }
  
  // Test: make_scale
  {
    mat3 p;
    for(F32 s=0.1f; s<=3.0f; s+=0.1f){
      p = make_scale(vec3(s));
    }
  }
  
  // Test: make_rotate (3 axis)
  {
    mat3 ma = make_rotate(vec3(0.0f, -1.0f, 0.0f),
                          vec3(1.0f, 0.0f, 0.0f),
                          vec3(0.0f, 0.0f, 1.0f));
    mat3 mb = make_rotate(PI/2, vec3(0.0f, 0.0f, 1.0f));
    if(!_test(ma, mb))
      return 1;
  }
  
  // Test: make_perspective
  {
    mat4 p = make_perspective(-1.0f, 1.0f, -1.0f, 1.0f, 5.0f, 50.0f);
    p = p;
  }
  
  // Test: make_orthographic
  {
    mat4 p = make_orthographic(-1.0f, 1.0f, -1.0f, 1.0f, 5.0f, 50.0f);
    p = p;
  }
  
  //
  quat q = make_quat(PI, vec3(0.0f, 0.0f, 1.0f));
  dualquat dq = dualquat(q, vec3(1.0f));
  mat3 m3 = make_rotate(q);
  mat4 m4 = mat4(m3, vec3(1.0f));
  
  // Test: rotate
  if(!_test(rotate(m3, vec3(1.0f, 0.0f, 0.0f)), -1.0f, 0.0f, 0.0f))
    return 1;
  if(!_test(rotate(m4, vec3(1.0f, 0.0f, 0.0f)), -1.0f, 0.0f, 0.0f))
    return 1;
  if(!_test(rotate(q, vec3(1.0f, 0.0f, 0.0f)), -1.0f, 0.0f, 0.0f))
    return 1;
  if(!_test(rotate(dq, vec3(1.0f, 0.0f, 0.0f)), -1.0f, 0.0f, 0.0f))
    return 1;
  
  // Test: transform
  if(!_test(transform(m4, vec3(1.0f, 0.0f, 0.0f)), 0.0f, 1.0f, 1.0f))
    return 1;
  if(!_test(transform(dq, vec3(1.0f, 0.0f, 0.0f)), 0.0f, 1.0f, 1.0f))
    return 1;
  
  return 0;
}
