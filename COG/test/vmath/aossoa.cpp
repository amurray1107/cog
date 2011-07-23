#include "unit_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace cog;

#define ALIGNED COG_ALIGNED(128)

typedef basic_vector3<VF32> vfvec3;
typedef basic_vector4<VF32> vfvec4;

int main()
{
  ALIGNED vec3 aos3[VF32_LENGTH];
  ALIGNED vec4 aos4[VF32_LENGTH];
  ALIGNED vfvec3 soa3;
  ALIGNED vfvec4 soa4;
  ALIGNED F32 ex3[3][VF32_LENGTH];
  ALIGNED F32 ex4[4][VF32_LENGTH];

  if(sizeof(soa3) != sizeof(aos3))
    return 1;
  if(sizeof(soa4) != sizeof(aos4))
    return 1;
  if(sizeof(soa3) != sizeof(ex3))
    return 1;
  if(sizeof(soa4) != sizeof(ex4))
    return 1;
  
  for(unsigned i=0;i<VF32_LENGTH;i++){
    aos3[i] = vec3(F32(i*3+1), F32(i*3+2), F32(i*3+3));
    aos4[i] = vec4(F32(i*4+1), F32(i*4+2), F32(i*4+3), F32(i*4+4));
    ex3[0][i] = aos3[i].getX();
    ex3[1][i] = aos3[i].getY();
    ex3[2][i] = aos3[i].getZ();
    ex4[0][i] = aos4[i].getX();
    ex4[1][i] = aos4[i].getY();
    ex4[2][i] = aos4[i].getZ();
    ex4[3][i] = aos4[i].getW();
  }
  
  convert(soa3, aos3);
  if(memcmp(&soa3, ex3, sizeof(soa3))!=0)
    return 1;
  
  convert(soa4, aos4);
  if(memcmp(&soa4, ex4, sizeof(soa4))!=0)
    return 1;
  
  memset(&aos3, 0, sizeof(aos3));
  memset(&aos4, 0, sizeof(aos4));
  
  convert(aos3, soa3);
  
  for(unsigned i=0;i<VF32_LENGTH;i++){
    if(aos3[i].getX() != F32(i*3+1))
      return 1;
    if(aos3[i].getY() != F32(i*3+2))
      return 1;
    if(aos3[i].getZ() != F32(i*3+3))
      return 1;
  }
  
  convert(aos4, soa4);
  
  for(unsigned i=0;i<VF32_LENGTH;i++){
    if(aos4[i].getX() != F32(i*4+1))
      return 1;
    if(aos4[i].getY() != F32(i*4+2))
      return 1;
    if(aos4[i].getZ() != F32(i*4+3))
      return 1;
    if(aos4[i].getW() != F32(i*4+4))
      return 1;
  }
  
  return 0;
}

