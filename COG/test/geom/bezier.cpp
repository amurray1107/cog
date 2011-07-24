#include "../vmath/unit_test.h"

using namespace cog;

int main()
{
  
  // Test: Quadratic Bezier Curve
  {
    const vec3 input[] = { 
      vec3(0.0f), 
      vec3(1.0f, 10.0f, 0.0f), 
      vec3(2.0f, 0.0f, 0.0f) 
    };
    
    for(float t = 0.0f; t<=1.0f; t+=0.1f){
      const vec3 vt = quadratic_bezier_curve(input, t);
      if(vt.getZ()!=0.0f)
        return 1;
    }
    
  }
  
  // Test: Cubic Bezier Curve
  {
    const vec3 input[] = { 
      vec3(0.0f), 
      vec3(1.0f, 10.0f, 0.0f), 
      vec3(2.0f, -10.0f, 0.0f), 
      vec3(3.0f, 0.0f, 0.0f) 
    };
    
    for(float t = 0.0f; t<=1.0f; t+=0.1f){
      const vec3 vt = cubic_bezier_curve(input, t);
      if(vt.getZ()!=0.0f)
        return 1;
    }
  }
  
  // Test: Quadratic Bezier Patch
  {
    const vec3 input[3][3] = {
      { 
        vec3(0.0f, 0.0f, 0.0f), 
        vec3(0.0f, 1.0f, 0.0f), 
        vec3(0.0f, 2.0f, 0.0f) 
      },
      { 
        vec3(1.0f, 0.0f, 0.0f), 
        vec3(1.0f, 1.0f, 0.0f), 
        vec3(1.0f, 2.0f, 0.0f) 
      },
      {
        vec3(2.0f, 0.0f, 0.0f), 
        vec3(2.0f, 1.0f, 0.0f), 
        vec3(2.0f, 2.0f, 0.0f)
      }
    };
    
    for(float u = 0.0f; u<=1.0f; u+=0.1f)
      for(float v = 0.0f; v<=1.0f; v+=0.1f){
        const vec3 vt = quadratic_bezier_patch(input, u, v);
        if(vt.getZ()!=0.0f)
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
        const vec3 vt = cubic_bezier_patch(input, u, v);
        if(vt.getZ()!=0.0f)
          return 1;
      }
    
  }
  
  return 0;
}
