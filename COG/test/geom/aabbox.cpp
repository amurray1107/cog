#include "../vmath/unit_test.h"

using namespace cog;

typedef basic_aabbox<F32> aabbox;
typedef basic_sphere<F32> sphere;
typedef basic_plane<F32> plane;

int main()
{
  // Test: Constructor
  {
    aabbox b1(vec3(-1.0f), vec3(1.0f, 2.0f, 3.0f));
    if(!_test(b1.getMinVec(), vec3(-1.0f)) || 
       !_test(b1.getMaxVec(), vec3(1.0f, 2.0f, 3.0f)))
      return 1;
    
    aabbox b2 = b1;
    if(!_test(b2.getMinVec(), b1.getMinVec()) ||
       !_test(b2.getMaxVec(), b1.getMaxVec()))
      return 1;
    
    aabbox b0;
    b0 = aabbox(vec3(0.0f), vec3(0.0f));
    if(!_test(b0.getMinVec(), vec3(0.0f)) ||
       !_test(b0.getMaxVec(), vec3(0.0f)))
      return 1;
    
    b0 = b1;
    if(!_test(b0.getMinVec(), b1.getMinVec()) ||
       !_test(b0.getMaxVec(), b1.getMaxVec()))
      return 1;
    
    aabbox b3(5.0f);
    if(!_test(b3.getMinVec(), vec3(5.0f)) ||
       !_test(b3.getMaxVec(), vec3(5.0f)))
      return 1;
    
  }
  
  // Test: Insert
  {
    aabbox b0(0.0f);
    
    b0.join(vec3(1.0f));
    if(!_test(b0.getMinVec(), vec3(0.0f)) || 
       !_test(b0.getMaxVec(), vec3(1.0f)))
      return 1;
    
    b0.join(vec3(2.0f, -1.0f, 0.0f));
    if(!_test(b0.getMinVec(), vec3(0.0f, -1.0f, 0.0f)) || 
       !_test(b0.getMaxVec(), vec3(2.0f, 1.0f, 1.0f)))
      return 1;
  }

  // Test: Intersect (AABB vs AABB)
  {
    const aabbox aabb(vec3(1.0f), vec3(2.0f));

    if(intersect(aabb, aabbox(vec3(-2.0f), vec3(-1.0f)))._getRawValue()!=false)
      return 1;
    if(intersect(aabb, aabbox(vec3(-1.0f), vec3(2.0f)))._getRawValue()!=true)
      return 1;
    if(intersect(aabb, aabbox(vec3(0.0f), vec3(1.5f)))._getRawValue()!=true)
      return 1;
  }

  // Test: Intersect (AABB vs Sphere)
  {
    const aabbox aabb(vec3(1.0f), vec3(2.0f));

    if(intersect(aabb, sphere(vec3(-1.0f), 1.0f))._getRawValue()!=false)
      return 1;
    if(intersect(aabb, sphere(vec3(1.0f), 1.0f))._getRawValue()!=true)
      return 1;
    if(intersect(aabb, sphere(vec3(1.5f), 1.0f))._getRawValue()!=true)
      return 1;
    if(intersect(aabb, sphere(vec3(2.0f), 1.0f))._getRawValue()!=true)
      return 1;
    if(intersect(aabb, sphere(vec3(4.0f), 1.0f))._getRawValue()!=false)
      return 1;
  }

  // Test: Intersect (AABB vs Plane)
  {
    const aabbox aabb(vec3(1.0f), vec3(2.0f));
    plane p;

    p = plane(vec3(1.0f, 0.0f, 0.0f), 0.0f);
    if(intersect(p, aabb)._getRawValue()!=false)
      return 1;

    p = plane(vec3(1.0f, 0.0f, 0.0f), -1.5f);
    if(intersect(p, aabb)._getRawValue()!=true)
      return 1;

    p = plane(vec3(1.0f, 0.0f, 0.0f), -3.0f);
    if(intersect(p, aabb)._getRawValue()!=false)
      return 1;
  }

  // Test: FrontFace (AABB vs Plane)
  {
    const aabbox aabb(vec3(1.0f), vec3(2.0f));
    plane p;

    p = plane(vec3(1.0f, 0.0f, 0.0f), 0.0f);
    if(frontface(p, aabb)._getRawValue()!=true)
      return 1;

    p = plane(vec3(1.0f, 0.0f, 0.0f), -1.5f);
    if(frontface(p, aabb)._getRawValue()!=false)
      return 1;

    p = plane(vec3(1.0f, 0.0f, 0.0f), -3.0f);
    if(frontface(p, aabb)._getRawValue()!=false)
      return 1;
  }

  // Test: Backface (AABB vs Plane)
  {
    const aabbox aabb(vec3(1.0f), vec3(2.0f));
    plane p;

    p = plane(vec3(1.0f, 0.0f, 0.0f), 0.0f);
    if(backface(p, aabb)._getRawValue()!=false)
      return 1;

    p = plane(vec3(1.0f, 0.0f, 0.0f), -1.5f);
    if(backface(p, aabb)._getRawValue()!=false)
      return 1;

    p = plane(vec3(1.0f, 0.0f, 0.0f), -3.0f);
    if(backface(p, aabb)._getRawValue()!=true)
      return 1;
  }
  
  return 0;
}

