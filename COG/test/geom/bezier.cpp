#include "../vmath/unit_test.h"
#include <stdio.h>

using namespace cog;

int main()
{
  
  // Test: Cubic Bezier Curve
  {
    const vec3 input[] = { 
      vec3(0.0f), 
      vec3(1.0f, 10.0f, 0.0f), 
      vec3(2.0f, -10.0f, 0.0f), 
      vec3(3.0f, 0.0f, 0.0f) 
    };
    
    for(float t = 0.0f; t<=1.0f; t+=0.1f){
      const vec3 vt = bezier_curve(0.0f, 1.0f, 4, input, t);
      
      if(!_test(vt.getZ(), 0.0f))
        return 1;
      if(!_test(vt.getX(), 3.0f*t))
        return 1;
      if(!_test(vt.getY(), 3.0f*t*(1-t)*(1-2.0f*t)*10.0f))
        return 1;
      
    }
  }
  
  // Test: Cubic Bezier Patch
  {
    const vec3 input[4][4] = {
      { 
        vec3(0.0f, 0.0f, 0.0f), 
        vec3(0.0f, 1.0f, 0.0f), 
        vec3(0.0f, 2.0f, 0.0f),
        vec3(0.0f, 3.0f, 0.0f)
      },
      { 
        vec3(1.0f, 0.0f, 0.0f), 
        vec3(1.0f, 1.0f, 0.0f), 
        vec3(1.0f, 2.0f, 0.0f),
        vec3(1.0f, 3.0f, 0.0f)
      },
      {
        vec3(2.0f, 0.0f, 0.0f), 
        vec3(2.0f, 1.0f, 0.0f), 
        vec3(2.0f, 2.0f, 0.0f),
        vec3(2.0f, 3.0f, 0.0f)
      },
      {
        vec3(3.0f, 0.0f, 0.0f), 
        vec3(3.0f, 1.0f, 0.0f), 
        vec3(3.0f, 2.0f, 0.0f),
        vec3(3.0f, 3.0f, 0.0f)
      }
    };
    
    for(float u = 0.0f; u<=1.0f; u+=0.1f)
      for(float v = 0.0f; v<=1.0f; v+=0.1f){
        const vec3 vt = bezier_patch(0.0f, 1.0f, 0.0f, 1.0f, 4, 4, 
                                     (vec3*)input, u, v);
        
        if(!_test(vt.getZ(), 0.0f))
          return 1;
        if(!_test(vt.getX(), u*3.0f))
          return 1;
        if(!_test(vt.getY(), v*3.0f))
          return 1;
      }
    
  }

  // 

  return 0;
}
