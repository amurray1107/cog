#include <iostream>
#include "unit_test.h"

using namespace cog;

int main()
{
  const mat3 m3_identity = mat3(vec3(1.0f, 0.0f, 0.0f),
                                vec3(0.0f, 1.0f, 0.0f),
                                vec3(0.0f, 0.0f, 1.0f));
  
  const mat4 identity = mat4(vec4(1.0f, 0.0f, 0.0f, 0.0f),
                             vec4(0.0f, 1.0f, 0.0f, 0.0f),
                             vec4(0.0f, 0.0f, 1.0f, 0.0f),
                             vec4(0.0f, 0.0f, 0.0f, 1.0f));
  const mat4 identity_2 = mat4(vec4(2.0f, 0.0f, 0.0f, 0.0f),
                               vec4(0.0f, 2.0f, 0.0f, 0.0f),
                               vec4(0.0f, 0.0f, 2.0f, 0.0f),
                               vec4(0.0f, 0.0f, 0.0f, 2.0f));
  
  // Test: sizeof
  if(sizeof(mat4)!=sizeof(vec4)*4)
    return 1;
  
  // Test: Constructor
  if(!_test(mat4(0.0f), vec4(0.0f), vec4(0.0f), vec4(0.0f), vec4(0.0f)))
    return 1;
  if(!_test(mat4(1.0f), vec4(1.0f), vec4(1.0f), vec4(1.0f), vec4(1.0f)))
    return 1;
  if(!_test(identity, 
            vec4(1.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 0.0f), 
            vec4(0.0f, 0.0f, 1.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f)))
    return 1;
  if(!_test(mat4(vec4(1.0f, 1.0f, 0.0f, 0.0f),
                 vec4(-1.0f, 1.0f, 0.0f, 0.0f),
                 vec4(0.0f, 0.0f, 2.0f, 0.0f),
                 vec4(0.0f, 0.0f, -10.0f, 1.0f)), 
            vec4(1.0f, 1.0f, 0.0f, 0.0f), vec4(-1.0f, 1.0f, 0.0f, 0.0f), 
            vec4(0.0f, 0.0f, 2.0f, 0.0f), vec4(0.0f, 0.0f, -10.0f, 1.0f)))
    return 1;
  if(!_test(mat4(mat4(100.0f)), mat4(100.0f)))
    return 1;
  if(!_test(mat4(identity), identity))
    return 1;
  if(!_test(mat4(m3_identity, vec3(4.0f)), mat4(vec4(1.0f, 0.0f, 0.0f, 0.0f),
                                                vec4(0.0f, 1.0f, 0.0f, 0.0f),
                                                vec4(0.0f, 0.0f, 1.0f, 0.0f),
                                                vec4(4.0f, 4.0f, 4.0f, 1.0f))))
    return 1;
  
  // Test: operator =
  {
    mat4 o(0.0f);
    o = mat4(10.0f);
    if(!_test(o, mat4(10.0f)))
      return 1;
    o = identity;
    if(!_test(o, identity))
      return 1;
  }
  
  // Test: unary operator -
  if(!_test(-mat4(0.0f), mat4(-0.0f)))
    return 1;
  if(!_test(-mat4(1.0f), mat4(-1.0f)))
    return 1;
  if(!_test(-mat4(-1.0f), mat4(1.0f)))
    return 1;
  
  // Test: operator +
  if(!_test(mat4(1.0f)+mat4(0.0f), mat4(1.0f)))
    return 1;
  if(!_test(mat4(1.0f)+mat4(10.0f), mat4(11.0f)))
    return 1;
  if(!_test(identity+identity, identity_2))
    return 1;
  
  // Test: operator -
  if(!_test(mat4(1.0f)-mat4(0.0f), mat4(1.0f)))
    return 1;
  if(!_test(mat4(100.0f)-mat4(200.0f), mat4(-100.0f)))
    return 1;
  if(!_test(identity-identity, mat4(0.0f)))
    return 1;
  
  // Test: operator * (scalar)
  if(!_test(mat4(1.0f)*0.0f, mat4(0.0f)))
    return 1;
  if(!_test(mat4(4.0f)*2.0f, mat4(8.0f)))
    return 1;
  if(!_test(identity*2.0f, identity_2))
    return 1;
  
  // Test: operator * (vector)
  if(!_test(identity*vec4(2.0f), vec4(2.0f)))
    return 1;
  if(!_test(mat4(0.0f)*vec4(2.0f), vec4(0.0f)))
    return 1;
  if(!_test(identity*vec4(2.0f, -1.0f, 100.0f, 1.0f), 
            vec4(2.0f, -1.0f, 100.0f, 1.0f)))
    return 1;
  
  // Test: operator * (matrix)
  if(!_test(mat4(1.0f)*mat4(0.0f), mat4(0.0f)))
    return 1;
  if(!_test(mat4(1.0f)*mat4(1.0f), mat4(4.0f)))
    return 1;
  if(!_test(mat4(2.0f)*identity, mat4(2.0f)))
    return 1;
  
  // Test: lerp
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      for(float t=0.0f; t<=1.0f; t+=0.1f){
        if(!_test(lerp(mat4(x), mat4(y), t), mat4(x+(y-x)*t)))
          return 1;
      }
    }
  }
  
  // Test: transpose
  if(!_test(transpose(identity), identity))
    return 1;
  
  return 0;
}
