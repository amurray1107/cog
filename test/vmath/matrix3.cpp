#include <iostream>
#include "unit_test.h"

using namespace cog;

const float PI = 3.141592653589793f;

int main()
{
  const mat3 identity = mat3(vec3(1.0f, 0.0f, 0.0f),
                             vec3(0.0f, 1.0f, 0.0f),
                             vec3(0.0f, 0.0f, 1.0f));
  const mat3 identity_2 = mat3(vec3(2.0f, 0.0f, 0.0f),
                               vec3(0.0f, 2.0f, 0.0f),
                               vec3(0.0f, 0.0f, 2.0f));
  
  // Test: sizeof
  if(sizeof(mat3)!=sizeof(vec3)*3)
    return 1;
  
  // Test: Constructor
  if(!_test(mat3(0.0f), vec3(0.0f), vec3(0.0f), vec3(0.0f)))
    return 1;
  if(!_test(mat3(1.0f), vec3(1.0f), vec3(1.0f), vec3(1.0f)))
    return 1;
  if(!_test(identity, vec3(1.0f, 0.0f, 0.0f), 
            vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)))
    return 1;
  if(!_test(mat3(vec3(1.0f, 1.0f, 0.0f),
                 vec3(-1.0f, 1.0f, 0.0f),
                 vec3(0.0f, 0.0f, 2.0f)), vec3(1.0f, 1.0f, 0.0f), 
            vec3(-1.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 2.0f)))
    return 1;
  if(!_test(mat3(mat3(100.0f)), mat3(100.0f)))
    return 1;
  if(!_test(mat3(identity), identity))
    return 1;
  
  // Test: operator =
  {
    mat3 o(0.0f);
    o = mat3(10.0f);
    if(!_test(o, mat3(10.0f)))
      return 1;
    o = identity;
    if(!_test(o, identity))
      return 1;
  }
  
  // Test: unary operator -
  if(!_test(-mat3(0.0f), mat3(-0.0f)))
    return 1;
  if(!_test(-mat3(1.0f), mat3(-1.0f)))
    return 1;
  if(!_test(-mat3(-1.0f), mat3(1.0f)))
    return 1;
  
  // Test: operator +
  if(!_test(mat3(1.0f)+mat3(0.0f), mat3(1.0f)))
    return 1;
  if(!_test(mat3(1.0f)+mat3(10.0f), mat3(11.0f)))
    return 1;
  if(!_test(identity+identity, identity_2))
    return 1;
  
  // Test: operator -
  if(!_test(mat3(1.0f)-mat3(0.0f), mat3(1.0f)))
    return 1;
  if(!_test(mat3(100.0f)-mat3(200.0f), mat3(-100.0f)))
    return 1;
  if(!_test(identity-identity, mat3(0.0f)))
    return 1;
  
  // Test: operator * (scalar)
  if(!_test(mat3(1.0f)*0.0f, mat3(0.0f)))
    return 1;
  if(!_test(mat3(4.0f)*2.0f, mat3(8.0f)))
    return 1;
  if(!_test(identity*2.0f, identity_2))
    return 1;
  
  // Test: operator * (vector)
  if(!_test(identity*vec3(2.0f), vec3(2.0f)))
    return 1;
  if(!_test(mat3(0.0f)*vec3(2.0f), vec3(0.0f)))
    return 1;
  if(!_test(identity*vec3(2.0f, -1.0f, 100.0f), vec3(2.0f, -1.0f, 100.0f)))
    return 1;
  
  // Test: operator * (matrix)
  if(!_test(mat3(1.0f)*mat3(0.0f), mat3(0.0f)))
    return 1;
  if(!_test(mat3(1.0f)*mat3(1.0f), mat3(3.0f)))
    return 1;
  if(!_test(mat3(2.0f)*identity, mat3(2.0f)))
    return 1;
  
  // Test: lerp
  for(float x=-2.0f; x<=2.0f; x+=0.1f){
    for(float y=-2.0f; y<=2.0f; y+=0.1f){
      for(float t=0.0f; t<=1.0f; t+=0.1f){
        if(!_test(lerp(mat3(x), mat3(y), t), mat3(x+(y-x)*t)))
          return 1;
      }
    }
  }
  
  // Test: transpose
  if(!_test(transpose(identity), identity))
    return 1;
  
  // Test: inverse
  if(!_test(inverse_transposed(identity), identity))
    return 1;
  if(!_test(inverse(identity), identity))
    return 1;
  if(!_test(inverse(identity)*identity, identity))
    return 1;
  
  return 0;
}
