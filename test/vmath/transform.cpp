#include <iostream>
#include "unit_test.h"

using namespace cog;

int main()
{
  const float PI = 3.141592653589793f;
  
  // Test: make_rotate (radian + axis)
  {
    mat3 p;
    for(float r= -PI; r<=PI; r+=PI*0.5f){
      p = make_rotate(r, vec3(1.0f, 0.0f, 0.0f));
      p = make_rotate(r, vec3(0.0f, 1.0f, 0.0f));
      p = make_rotate(r, vec3(0.0f, 0.0f, 1.0f));
    }
  }
  
  // Test: make_scale
  {
    mat3 p;
    for(float s=0.1f; s<=3.0f; s+=0.1f){
      p = make_scale(vec3(s));
    }
  }
  
  // Test: make_perspective
  {
    mat4 p = make_perspective(-1.0f, 1.0f, -1.0f, 1.0f, 5.0f, 50.0f);
  }
  
  // Test: make_orthographic
  {
    mat4 p = make_orthographic(-1.0f, 1.0f, -1.0f, 1.0f, 5.0f, 50.0f);
  }
  
  return 0;
}
