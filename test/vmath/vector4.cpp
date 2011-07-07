#include <iostream>
#include "unit_test.h"

using namespace cog;

int main()
{
  // Test: sizeof
  if(sizeof(vec4)!=sizeof(float)*4)
    return 1;
  
  // Test: Constructor
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(vec4(x), x, x, x, x))
      return 1;
    if(!_test(vec4(x, -x, x, -x), x, -x, x, -x))
      return 1;
    if(!_test(vec4(x, -x, -x, -x), x, -x, -x, -x))
      return 1;
    if(!_test(vec4(x, x-1.0f, x-2.0f, x-3.0f), x, x-1.0f, x-2.0f, x-3.0f))
      return 1;
    if(!_test(vec4(vec4(x)), vec4(x)))
      return 1;
    if(!_test(vec4(vec4(x,0.0f,x-1.0f,x-2.0f)), vec4(x,0.0f,x-1.0f,x-2.0f)))
      return 1;
    if(!_test(vec4(vec3(1.0f), 2.0f), vec4(1.0f, 1.0f, 1.0f, 2.0f)))
      return 1;
  }
  
  // Test: Operator =
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    vec4 t = vec4(0.0f);
    const vec4 vx = vec4(x, x-2.0f, x-4.0f, x+1.0f);
    t = vx;
    if(!_test(t, vx))
      return 1;
  }
  
  // Test: unary operator - (negation)
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(-vec4(x,x-1.5f,x-1.0f,x+1.0f),-x,-(x-1.5f),-(x-1.0f),-(x+1.0f)))
      return 1;
  }
  
  // Test: operator + 
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(vec4(x,y,x-10.0f,x)+vec4(y,x,10.0f+y,-y), x+y,x+y,x+y,x-y))
        return 1;
    }
  }
  
  // Test: operator -
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(vec4(x, y, x+10.0f,x)-vec4(y, x, 10.0f+y,-y),x-y,y-x,x-y,x+y))
        return 1;
    }
  }
  
  // Test: operator * (scalar)
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(vec4(x,y,2.0f,x-y)*y,x*y,y*y,2.0f*y,(x-y)*y))
        return 1;
      if(!_test(y*vec4(x,y,2.0f,x-y),x*y,y*y,2.0f*y,(x-y)*y))
        return 1;
    }
  }
  
  // Test: dot product
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(dot(vec4(x), vec4(y)), x*y*4.0f))
        return 1;
      if(!_test(dot(vec4(x), vec4(y,-y,0.0f,0.0f)), 0.0f))
        return 1;
    }
  }
  
  // Test: abs
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(abs(vec4(x, x-1.5f, x-1.0f, x+1.0f)), 
              abs(x), abs(x-1.5f), abs(x-1.0f), abs(x+1.0f)))
      return 1;
  }
  
  // Test: min
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(min(vec4(x), vec4(x,-x,x,-x)),
                min(x,x), min(x,-x), min(x,x), min(x,-x)))
        return 1;
    }
  }
  
  // Test: max
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(max(vec4(x), vec4(x,-x,x,-x)), 
                max(x,x), max(x,-x), max(x,x), max(x,-x)))
        return 1;
    }
  }
  
  // Test: lerp
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      for(float t=0.0f; t<=1.0f; t+=0.1f){
        if(!_test(lerp(vec4(x), vec4(y), t), vec4(x+(y-x)*t)))
          return 1;
      }
    }
  }
  
  // Test: lengthSqr
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(lengthSqr(vec4(x,y,1.0f,2.0f)), x*x+y*y+5.0f))
        return 1;
    }
  }
  
  // Test: length
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(length(vec4(x,y,1.0f,2.0f)), sqrt(x*x+y*y+5.0f)))
        return 1;
    }
  }
  
  // Test: normalize
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(normalize(vec4(x,0.0f,0.0f,0.0f)), 
              vec4(copysign(1.0f,x), 0.0f, 0.0f, 0.0f)))
      return 1;
    if(!_test(normalize(vec4(0.0f, x, 0.0f, 0.0f)), 
              vec4(0.0f, copysign(1.0f,x), 0.0f, 0.0f)))
      return 1;
    if(!_test(normalize(vec4(0.0f, 0.0f, x, 0.0f)), 
              vec4(0.0f, 0.0f, copysign(1.0f,x), 0.0f)))
      return 1;
    if(!_test(normalize(vec4(0.0f, 0.0f, 0.0f, x)), 
              vec4(0.0f, 0.0f, 0.0f, copysign(1.0f,x))))
      return 1;
  }
  
  return 0;
}
