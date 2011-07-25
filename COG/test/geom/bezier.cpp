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
      const vec3 vt = quadratic_bezier_curve(input, t);
      if(!_test(vt.getZ(), 0.0f))
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
      if(!_test(vt.getZ(), 0.0f))
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
        if(!_test(vt.getZ(), 0.0f))
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
        if(!_test(vt.getZ(), 0.0f))
          return 1;
      }
    
  }

  // Test: Cubic Hermite Curve
  {
    const vec3 input[] = { 
      vec3(0.0f), 
      vec3(2.0f, 0.0f, 0.0f) 
    };
    const vec3 tangent[] = {
      vec3(1.0f, 1.0f, 0.0f), 
      vec3(-1.0f, 1.0f, 0.0f)
    };
    
    for(float t = 0.0f; t<=1.0f; t+=0.1f){
      const vec3 vt = cubic_hermite_curve(input, tangent, t);
      if(!_test(vt.getZ(), 0.0f))
        return 1;
    }
  }

  // Test: Kochanek Bartels Curve
  {
    const vec3 input[] = { 
      vec3(0.0f), 
      vec3(1.0f, 0.0f, 0.0f), 
      vec3(2.0f, 0.0f, 0.0f), 
      vec3(3.0f, 0.0f, 0.0f)
    };
    const F32 tpos[] = { 0.0f, 1.0f, 2.0f, 3.0f };
    vec3 tg[4];
    
    kochanek_bartels_curve(input, tpos, 0.0f, 0.0f, 0.0f, tg[0], tg[1]);
    kochanek_bartels_curve(input+1, tpos, 0.0f, 0.0f, 0.0f, tg[2], tg[3]);

    //for(int i=0;i<4;i++)
      //printf("%f %f %f\n", tg[i].getX(), tg[i].getY(), tg[i].getZ());

    for(float t = 0.0f; t<=1.0f; t+=0.1f){
      const vec3 vt = cubic_hermite_curve(input+1, tg+1, t);
      //printf("[%f %f %f]\n", vt.getX(), vt.getY(), vt.getZ());

      if(!_test(vt.getX(), 1.0f+t))
        return 1;
      if(!_test(vt.getY(), 0.0f))
        return 1;
      if(!_test(vt.getZ(), 0.0f))
        return 1;
    }
  }

  // 

  return 0;
}
