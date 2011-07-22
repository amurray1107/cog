#include "../vmath/unit_test.h"

using namespace cog;

typedef basic_plane<float> plane;
typedef basic_ray<float> ray;

int main()
{
  // Test: Constructor
  {
    plane p1(vec3(1.0f, 0.0f, 0.0f), 1.0f);
    if(!_test(p1.getNormal(), vec3(1.0f, 0.0f, 0.0f)) || 
       !_test(p1.getDistance(), 1.0f))
      return 1;
    
    plane p2 = p1;
    if(!_test(p2.getNormal(), p1.getNormal()) || 
       !_test(p2.getDistance(), p1.getDistance()))
      return 1;
    
    plane p0;
    p0 = plane(vec3(0.0f), 0.0);
    if(!_test(p0.getNormal(), vec3(0.0f)) ||
       !_test(p0.getDistance(), (0.0f)))
      return 1;
    
    p0 = p1;
    if(!_test(p0.getNormal(), p1.getNormal()) ||
       !_test(p0.getDistance(), p1.getDistance()))
      return 1;
    
    plane p3(vec4(1.0f, 2.0f, 3.0f, 4.0f));
    if(!_test(p3.getNormal(), vec3(1.0f, 2.0f, 3.0f)) ||
       !_test(p3.getDistance(), 4.0f))
      return 1;
    
  }
  
  // Test: func
  {
    if(plane(vec4(1.0f, 0.0f, 0.0f, 1.0f)).func(vec3(1.0f, 2.0f, 3.0f))!=2.0f)
      return 1;
  }
  
  // Test: normalize
  {
    vec3 n0 = vec3(1.0f, 2.0f, 3.0f);
    vec3 v0 = vec3(0.0f, 0.0f, 0.0f);
    plane p0(n0, dot(n0, v0));
    p0 = normalize(p0);
    if(!_test(p0.getNormal(), normalize(n0)) ||
       !_test(p0.getDistance(), dot(normalize(n0), v0)))
      return 1;
  }
  
  // Test: test_frontface (point)
  {
    plane p0 = normalize(plane(vec3(1.0f, 0.0f, 0.0f), 0.0f));
    
    
  }
  
  return 0;
}

