#include "../vmath/unit_test.h"
#include <stdio.h>

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
      const vec3 vt = quadratic_bezier_curve<F32, 1>(input, t);
      const vec3 vd = quadratic_bezier_curve_dt<F32, 1>(input, t);

      if(!_test(vt.getZ(), 0.0f))
        return 1;
      if(!_test(vt.getX(), 2.0f*t))
        return 1;
      if(!_test(vt.getY(), 20.0f*t*(1-t)))
        return 1;
      if(!_test(vd.getX(), 2.0f))
        return 1;
      if(!_test(vd.getY(), 20.0f*(1-2.0f*t)))
        return 1;
      if(!_test(vd.getZ(), 0.0f))
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
      const vec3 vt = cubic_bezier_curve<F32, 1>(input, t);
      const vec3 vd = cubic_bezier_curve_dt<F32, 1>(input, t);

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
        const vec3 vdu = quadratic_bezier_patch_du(input, u, v);
        const vec3 vdv = quadratic_bezier_patch_dv(input, u, v);

        if(!_test(vt.getZ(), 0.0f))
          return 1;
        if(!(dot(cross(vdu, vdv), vec3(0.0f, 0.0f, 1.0f)) > 0.0f))
          return 1;
        if(!_test(normalize(cross(vdu, vdv)), vec3(0.0f, 0.0f, 1.0f)))
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
        const vec3 vdu = cubic_bezier_patch_du(input, u, v);
        const vec3 vdv = cubic_bezier_patch_dv(input, u, v);

        if(!_test(vt.getZ(), 0.0f))
          return 1;
        if(!(dot(cross(vdu, vdv), vec3(0.0f, 0.0f, 1.0f)) > 0.0f))
          return 1;
        if(!_test(normalize(cross(vdu, vdv)), vec3(0.0f, 0.0f, 1.0f)))
          return 1;
      }
    
  }

  // 

  return 0;
}
