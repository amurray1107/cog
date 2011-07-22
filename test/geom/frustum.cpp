#include "../vmath/unit_test.h"
#include <stdlib.h>
#include <string.h>

using namespace cog;

typedef basic_frustum<float> frustum;
typedef basic_sphere<float> sphere;

int main()
{
  mat4 m1 = make_perspective(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 10.0f);
  mat4 m2 = make_orthographic(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 10.0f);
  
  // Test: Constructor
  {
    frustum f1(m1);
    frustum f2(m2);
    
    frustum f0 = f1;
    if(memcmp(&f0, &f1, sizeof(frustum)))
      return 1;
    
    f0 = f2;
    if(memcmp(&f0, &f2, sizeof(frustum)))
      return 1;
  }
  
  // Test: test_visible (point)
  {
    frustum f2(m2);
    
    if(f2.test_visible(vec3(0.0f, 0.0f, 5.0f))._getRawValue()!=true)
      return false;
    if(f2.test_visible(vec3(0.0f, 0.0f, 0.0f))._getRawValue()!=false)
      return false;
    if(f2.test_visible(vec3(0.0f, 0.0f, 20.0f))._getRawValue()!=false)
      return false;
    if(f2.test_visible(vec3(0.5f, 0.5f, 5.0f))._getRawValue()!=true)
      return false;
  }
  
  // Test: test_visible (sphere)
  {
    frustum f2(m2);
    
    if(f2.test_visible(sphere(vec3(0.0f), 1.0f))._getRawValue()!=true)
      return false;
    if(f2.test_visible(sphere(vec3(1.0f), 1.0f))._getRawValue()!=true)
      return false;
  }
  
  
  return 0;
}

