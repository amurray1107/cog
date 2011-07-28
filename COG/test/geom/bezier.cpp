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
    
    for(F32 t = 0.0f; t<=1.0f; t+=0.1f){
      const vec3 vt = bezier_curve(4, input, t);
      const vec3 vd = bezier_curve_der(4, input, t);
      
      if(!_test(vt.getZ(), 0.0f))
        return 1;
      if(!_test(vt.getX(), 3.0f*t))
        return 1;
      if(!_test(vt.getY(), 3.0f*t*(1-t)*(1-2.0f*t)*10.0f))
        return 1;
      if(!_test(vd.getX(), 3.0f))
        return 1;
      if(!_test(vd.getZ(), 0.0f))
        return 1;
      if(!_test(vd.getY(), 30.0f*(1.0f-6.0f*t+6.0f*t*t)))
        return 1;
    }
  }
  
  // Test: Cubic Bezier Patch
  {
    const vec3 input[4][3] = {
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
      },
      {
        vec3(3.0f, 0.0f, 0.0f), 
        vec3(3.0f, 1.0f, 0.0f), 
        vec3(3.0f, 2.0f, 0.0f)
      }
    };
    
    for(F32 u = 0.0f; u<=1.0f; u+=0.1f)
      for(F32 v = 0.0f; v<=1.0f; v+=0.1f){
        const vec3 vt = bezier_patch(4, 3, (vec3*)input, u, v);
        const vec3 vdv = bezier_patch_dv(4, 3, (vec3*)input, u, v);
        const vec3 vdu = bezier_patch_du(4, 3, (vec3*)input, u, v);
        const vec3 normal = normalize(cross(vdu, vdv));
        
        if(!_test(vt.getZ(), 0.0f))
          return 1;
        if(!_test(vt.getX(), u*3.0f))
          return 1;
        if(!_test(vt.getY(), v*2.0f))
          return 1;
        if(!_test(vdv, vec3(0.0f, 2.0f, 0.0f)))
          return 1;
        if(!_test(vdu, vec3(3.0f, 0.0f, 0.0f)))
          return 1;
        if(!_test(normal, vec3(0.0f, 0.0f, 1.0f)))
          return 1;
      }
    
  }

  // 

  return 0;
}
