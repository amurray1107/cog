#include <iostream>
#include "unit_test.h"

using namespace cog;

int main()
{
  // Test: sizeof
  if(sizeof(vec3)!=sizeof(float)*3)
    return 1;
  
  // Test: Constructor
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
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
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    vec3 t = vec3(0.0f);
    const vec3 vx = vec3(x, x-2.0f, x-4.0f);
    t = vx;
    if(!_test(t, vx))
      return 1;
  }
  
  // Test: unary operator - (negation)
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(-vec3(x, x-1.5f, x-1.0f), -x, -(x-1.5f), -(x-1.0f)))
      return 1;
  }
  
  // Test: operator + 
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(vec3(x, y, x-10.0f)+vec3(y, x, 10.0f+y), x+y, x+y, x+y))
        return 1;
    }
  }
  
  // Test: operator -
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(vec3(x, y, x+10.0f)-vec3(y, x, 10.0f+y), x-y, y-x, x-y))
        return 1;
    }
  }
  
  // Test: operator * (scalar)
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(vec3(x, y, 2.0f)*y, x*y, y*y, 2.0f*y))
        return 1;
      if(!y*_test(vec3(x, y, 2.0f), x*y, y*y, 2.0f*y))
        return 1;
    }
  }
  
  // Test: dot product
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
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
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(abs(vec3(x, x-1.5f, x-1.0f)), abs(x), abs(x-1.5f), abs(x-1.0f)))
      return 1;
  }
  
  // Test: min
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(min(vec3(x), vec3(x,-x,x)), min(x,x), min(x,-x), min(x,x)))
        return 1;
    }
  }
  
  // Test: max
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(max(vec3(x), vec3(x,-x,x)), max(x,x), max(x,-x), max(x,x)))
        return 1;
    }
  }
  
  // Test: lerp
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      for(float t=0.0f; t<=1.0f; t+=0.1f){
        if(!_test(lerp(vec3(x), vec3(y), t), vec3(x+(y-x)*t)))
          return 1;
      }
    }
  }
  
  // Test: lengthSqr
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(lengthSqr(vec3(x,y,1.0f)), x*x+y*y+1.0f))
        return 1;
    }
  }
  
  // Test: length
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(length(vec3(x,y,1.0f)), sqrt(x*x+y*y+1.0f)))
        return 1;
    }
  }
  
  // Test: normalize
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
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
  
  return 0;
}
