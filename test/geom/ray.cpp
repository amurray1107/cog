#include "../vmath/unit_test.h"

using namespace cog;

typedef basic_ray<float> ray;

int main()
{
  // Test: Constructor
  {
    ray r1(vec3(2.0f), vec3(1.0f, 0.0f, 0.0f));
    if(!_test(r1.getOrigin(), vec3(2.0f)) || 
       !_test(r1.getDirection(), vec3(1.0f, 0.0f, 0.0f)))
      return 1;
    
    ray r2 = r1;
    if(!_test(r2.getOrigin(), r1.getOrigin()) ||
       !_test(r2.getDirection(), r1.getDirection()))
      return 1;
    
    ray r0;
    r0 = ray(vec3(0.0f), vec3(0.0f));
    if(!_test(r0.getOrigin(), vec3(0.0f)) ||
       !_test(r0.getDirection(), vec3(0.0f)))
      return 1;
    
    r0 = r1;
    if(!_test(r0.getOrigin(), r1.getOrigin()) ||
       !_test(r0.getDirection(), r1.getDirection()))
      return 1;
  }
  
  // Test: normalize
  {
    ray r1(vec3(2.0f), vec3(1.0f));
    r1 = normalize(r1);
    if(!_test(r1.getOrigin(), vec3(2.0f)) || 
       !_test(r1.getDirection(), normalize(vec3(1.0f))))
      return 1;
  }
  
  return 0;
}

