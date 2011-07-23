#include "unit_test.h"

using namespace cog;

int main()
{
  // Test: sizeof
  if(sizeof(vec3)!=sizeof(F32)*3)
    return 1;
  
  // Test: Constructor
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(vec3(x), x, x, x))
      return 1;
    if(!_test(vec3(x, -x, x), x, -x, x))
      return 1;
    if(!_test(vec3(x, -x, -x), x, -x, -x))
      return 1;
    if(!_test(vec3(x, x-1.0f, x-2.0f), x, x-1.0f, x-2.0f))
      return 1;
    if(!_test(vec3(vec3(x)), vec3(x)))
      return 1;
    if(!_test(vec3(vec3(x, 0.0f, x-1.0f)), vec3(x, 0.0f, x-1.0f)))
      return 1;
  }
  
  // Test: Operator =
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    vec3 t = vec3(0.0f);
    const vec3 vx = vec3(x, x-2.0f, x-4.0f);
    t = vx;
    if(!_test(t, vx))
      return 1;
  }
  
  // Test: unary operator - (negation)
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(-vec3(x, x-1.5f, x-1.0f), -x, -(x-1.5f), -(x-1.0f)))
      return 1;
  }
  
  // Test: operator + 
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(vec3(x, y, x-10.0f)+vec3(y, x, 10.0f+y), x+y, x+y, x+y))
        return 1;
    }
  }
  
  // Test: operator -
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(vec3(x, y, x+10.0f)-vec3(y, x, 10.0f+y), x-y, y-x, x-y))
        return 1;
    }
  }
  
  // Test: operator * (scalar)
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(vec3(x, y, 2.0f)*y, x*y, y*y, 2.0f*y))
        return 1;
      if(!y*_test(vec3(x, y, 2.0f), x*y, y*y, 2.0f*y))
        return 1;
    }
  }
  
  // Test: dot product
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(dot(vec3(x), vec3(y)), x*y*3.0f))
        return 1;
      if(!_test(dot(vec3(x), vec3(y,-y,0.0f)), 0.0f))
        return 1;
    }
  }
  
  // Test: cross product
  if(!_test(cross(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)), 
            vec3(0.0f, 0.0f, 1.0f)))
    return 1;
  
  // Test: abs
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(abs(vec3(x, x-1.5f, x-1.0f)), abs(x), abs(x-1.5f), abs(x-1.0f)))
      return 1;
  }
  
  // Test: min
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(min(vec3(x), vec3(x,-x,x)), min(x,x), min(x,-x), min(x,x)))
        return 1;
    }
  }
  
  // Test: max
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(max(vec3(x), vec3(x,-x,x)), max(x,x), max(x,-x), max(x,x)))
        return 1;
    }
  }
  
  // Test: lerp
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      for(F32 t=0.0f; t<=1.0f; t+=0.1f){
        if(!_test(lerp(vec3(x), vec3(y), t), vec3(x+(y-x)*t)))
          return 1;
      }
    }
  }
  
  // Test: lengthSqr
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(lengthSqr(vec3(x,y,1.0f)), x*x+y*y+1.0f))
        return 1;
    }
  }
  
  // Test: length
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(length(vec3(x,y,1.0f)), sqrt(x*x+y*y+1.0f)))
        return 1;
    }
  }
  
  // Test: normalize
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(normalize(vec3(x,0.0f,0.0f)), 
              vec3(copysign(1.0f,x), 0.0f, 0.0f)))
      return 1;
    if(!_test(normalize(vec3(0.0f, x, 0.0f)), 
              vec3(0.0f, copysign(1.0f,x), 0.0f)))
      return 1;
    if(!_test(normalize(vec3(0.0f, 0.0f, x)), 
              vec3(0.0f, 0.0f, copysign(1.0f,x))))
      return 1;
  }
  
  // Test: reflect
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(reflect(vec3(-1.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
              vec3(-1.0f, 1.0f, 0.0f)))
      return 1;
  }
  
  // Test: refract
  for(F32 x=0.5f; x<=2.0f; x+=0.5f)
    if(!_test(refract(vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), x), 
              vec3(0.0f, -1.0f, 0.0f)))
      return 1;
  
  // Test: select
  {
    const vec3 v0 = vec3(1.0f, 2.0f, 3.0f);
    const vec3 v1 = vec3(-4.0f, -8.0f, -16.0f);
    if(!_test(select(v0, v1, bool_<F32>::yes()), v1))
      return 1;
    if(!_test(select(v0, v1, bool_<F32>::no()), v0))
      return 1;
  }
  
  // Test: slerp
  {
    const F32 PI = 3.14159f;
    for(F32 angle = 0.0f; angle <= PI; angle += PI * 0.25f){
      const vec3 v0 = vec3(1.0f, 0.0f, 0.0f);
      const vec3 v1 = vec3(cos(angle), sin(angle), 0.0f);
      for(F32 t=0.0f; t<=1.0f; t+=0.1f){
        const vec3 vt = slerp(v0, v1, t);
        if(!_test(length(vt), 1.0f))
          return 1;
      }
      if(!_test(slerp(v0, v1, 0.0f), v0))
        return 1;
      if(!_test(slerp(v0, v1, 1.0f), v1))
        return 1;
    }
  }
  
  return 0;
}
