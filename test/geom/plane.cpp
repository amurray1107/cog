#include "../vmath/unit_test.h"

using namespace cog;

typedef basic_plane<float> plane;

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
  
  //
  
  return 0;
}

