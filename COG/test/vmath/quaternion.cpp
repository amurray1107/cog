#include "unit_test.h"

using namespace cog;

int main()
{
  const quat identity (vec3(0.0f), 1.0f);
  const F32 PI = 3.141592653589793f;
  
  // Test: sizeof
  if(sizeof(quat)!=sizeof(F32)*4)
    return 1;
  
  // Test: Constructor
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(quat(vec3(1.0f), 2.0f), vec3(1.0f), 2.0f))
      return 1;
  }
  
  // Test: Operator =
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    quat t;
    const quat vx = quat(vec3(x, x-2.0f, x-4.0f), x+1.0f);
    t = vx;
    if(!_test(t, vx))
      return 1;
  }
  
  // Test: unary operator - (negation)
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(-quat(vec3(x,x-1.5f,x-1.0f),x+1.0f),
              vec3(-x,-(x-1.5f),-(x-1.0f)),-(x+1.0f)))
      return 1;
  }
  
  // Test: operator + 
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(quat(vec3(x,y,x-10.0f),x)+quat(vec3(y,x,10.0f+y),-y), 
                vec3(x+y,x+y,x+y),x-y))
        return 1;
    }
  }
  
  // Test: operator -
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(quat(vec3(x, y, x+10.0f),x)-quat(vec3(y, x, 10.0f+y),-y),
                vec3(x-y,y-x,x-y),x+y))
        return 1;
    }
  }
  
  // Test: operator * (scalar)
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(quat(vec3(x,y,2.0f),x-y)*y,vec3(x*y,y*y,2.0f*y),(x-y)*y))
        return 1;
    }
  }
  
  // Test: operator * (quaternion)
  if(!_test(identity*identity, identity))
    return 1;
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(identity*quat(vec3(-x), x), vec3(-x), x))
      return 1;
    if(!_test(quat(vec3(-x), x)*identity, vec3(-x), x))
      return 1;
  }
  
  // Test: operator * (vector3)
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(identity*vec3(x, x-1.0f, x+0.5f), vec3(x, x-1.0f, x+0.5f)))
      return 1;
  }
  
  // Test: dot product
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(dot(quat(vec3(x), x), quat(vec3(y), y)), x*y*4.0f))
        return 1;
      if(!_test(dot(quat(vec3(x), x), quat(vec3(y,-y,0.0f),0.0f)), 0.0f))
        return 1;
    }
  }
  
  // Test: lerp
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      for(F32 t=0.0f; t<=1.0f; t+=0.1f){
        if(!_test(lerp(quat(vec3(x), 0.0f), quat(vec3(y), 1.0f), t), 
                  quat(vec3(x+(y-x)*t), t)))
          return 1;
      }
    }
  }
  
  // Test: lengthSqr
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(lengthSqr(quat(vec3(x,y,1.0f),2.0f)), x*x+y*y+5.0f))
        return 1;
    }
  }
  
  // Test: length
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    for(F32 y=-2.0f; y<=2.0f; y+=0.1f){
      if(!_test(length(quat(vec3(x,y,1.0f),2.0f)), sqrt(x*x+y*y+5.0f)))
        return 1;
    }
  }
  
  // Test: normalize
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(normalize(quat(vec3(0.0f, 0.0f, 0.0f), x)), 
              quat(vec3(0.0f, 0.0f, 0.0f), copysign(1.0f,x))))
      return 1;
  }
  
  // Test: make_quat
  for(F32 r=0.0f; r<=PI; r+=PI*0.1f){
    quat q;
    q = make_quat(r, vec3(0.0f, 0.0f, 1.0f));
    if(!_test(q*vec3(1.0f, 0.0f, 0.0f), cos(r), sin(r), 0.0f))
      return 1;
  }
  
  // Test: make_rotate
  for(F32 r=0.0f; r<=PI; r+=PI*0.1f){
    mat3 m;
    quat q;
    q = make_quat(r, vec3(0.0f, 0.0f, 1.0f));
    m = make_rotate(q);
    if(!_test(m*vec3(1.0f, 0.0f, 0.0f), q*vec3(1.0f, 0.0f, 0.0f)))
      return 1;
  }
  
  // Test: conjugate
  for(F32 x=-2.0f; x<=2.0f; x+=0.1f){
    if(!_test(conjugate(quat(vec3(1.0f), 2.0f)), vec3(-1.0f), 2.0f))
      return 1;
  }
  
  // Test: inverse
  if(!_test(inverse(identity), identity))
    return 1;
  if(!_test(inverse(identity)*identity, identity))
    return 1;
  
  return 0;
}
