#include "unit_test.h"

using namespace cog;

const F32 PI = 3.141592653589793f;

int main()
{
  const dualquat identity = dualquat(quat(vec3(0.0f), 1.0f), 
                                     quat(vec3(0.0f), 0.0f));
  
  // Test: sizeof
  if(sizeof(dualquat)!=sizeof(quat)*2)
    return 1;
  
  // Test: Constructor
  if(!_test(dualquat(quat(vec3(2.0f), 0.0f), quat(vec3(3.0f), 1.0f)), 
            quat(vec3(2.0f), 0.0f), quat(vec3(3.0f), 1.0f)))
    return 1;
  if(!_test(dualquat(identity), identity))
    return 1;
  if(!_test(dualquat(quat(vec3(0.0f), 1.0f), vec3(4.0f)), 
            quat(vec3(0.0f), 1.0f), quat(vec3(2.0f), 0.0f)))
    return 1;
  
  // Test: operator =
  {
    dualquat o;
    o = identity;
    if(!_test(o, identity))
      return 1;
  }
  
  // Test: unary operator -
  if(!_test(-dualquat(quat(vec3(2.0f), 0.0f), quat(vec3(3.0f), 1.0f)), 
            -quat(vec3(2.0f), 0.0f), -quat(vec3(3.0f), 1.0f)))
    return 1;
  
  // Test: operator +
  if(!_test(dualquat(quat(vec3(1.0f), 2.0f), quat(vec3(4.0f), 0.0f)) + 
            dualquat(quat(vec3(1.0f), 2.0f), quat(vec3(4.0f), 0.0f)),
            quat(vec3(2.0f), 4.0f), quat(vec3(8.0f), 0.0f)))
    return 1;
  
  // Test: operator -
  if(!_test(dualquat(quat(vec3(1.0f), 2.0f), quat(vec3(4.0f), 0.0f)) - 
            dualquat(quat(vec3(1.0f), 2.0f), quat(vec3(4.0f), 0.0f)),
            quat(vec3(0.0f), 0.0f), quat(vec3(0.0f), 0.0f)))
    return 1;
  
  // Test: operator * (scalar)
  if(!_test(identity * 2.0f, quat(vec3(0.0f), 2.0f), quat(vec3(0.0f), 0.0f)))
    return 1;
  
  // Test: operator * (dualquat)
  if(!_test(identity * identity, identity))
    return 1;
  
  // Test: getDisplacement
  if(!_test(identity.getDisplacement(), vec3(0.0f)))
    return 1;
  
  // Test: getRotation
  if(!_test(identity.getRotation(), quat(vec3(0.0f), 1.0f)))
    return 1;
  
  // Test: normalize
  if(!_test(normalize(identity), identity))
    return 1;
  
  return 0;
}
