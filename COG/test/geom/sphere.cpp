#include "../vmath/unit_test.h"

using namespace cog;

typedef basic_sphere<F32> sphere;

int main()
{
  // Test: Constructor
  {
    sphere s1(vec3(1.0f, 2.0f, 3.0f), 1.0f);
    if(!_test(s1.getCenter(), vec3(1.0f, 2.0f, 3.0f)) || 
       !_test(s1.getRadius(), 1.0f))
      return 1;
    
    sphere s2 = s1;
    if(!_test(s2.getCenter(), s1.getCenter()) || 
       !_test(s2.getRadius(), s1.getRadius()))
      return 1;
    
    sphere s0;
    s0 = sphere(vec3(0.0f), 0.0);
    if(!_test(s0.getCenter(), vec3(0.0f)) ||
       !_test(s0.getRadius(), (0.0f)))
      return 1;
    
    s0 = s1;
    if(!_test(s0.getCenter(), s1.getCenter()) ||
       !_test(s0.getRadius(), s1.getRadius()))
      return 1;
  }
  
  // Test: func
  {
    if(sphere(vec3(0.0f), 1.0f).func(vec3(3.0f, 4.0f, 0.0f))!=24.0f)
      return 1;
  }
  
  // Test: intersect (sphere)
  {
    if(intersect(sphere(vec3(0.0f), 1.0f), 
                 sphere(vec3(0.0f), 1.0f))._getRawValue()!=true)
      return 1;
    if(intersect(sphere(vec3(0.0f), 1.0f), 
                 sphere(vec3(0.0f), 3.0f))._getRawValue()!=true)
      return 1;
    if(intersect(sphere(vec3(0.0f), 3.0f), 
                 sphere(vec3(0.0f), 1.0f))._getRawValue()!=true)
      return 1;
    if(intersect(sphere(vec3(1.0f), 1.0f), 
                 sphere(vec3(0.0f), 1.5f))._getRawValue()!=true)
      return 1;
  }

  return 0;
}

