#include <COG/cog.h>

int main()
{
  // Test: Assert
  COG_ASSERT(true);
  COG_ASSERT(1);
  COG_ASSERT(0xff00);

  // Test: C8
  if(sizeof(cog::C8)!=1)
    return 1;

  // Test: U8
  if(sizeof(cog::U8)!=1)
    return 1;

  // Test: I8
  if(sizeof(cog::I8)!=1)
    return 1;

  // Test: U16
  if(sizeof(cog::U16)!=2)
    return 1;

  // Test: I16
  if(sizeof(cog::I16)!=2)
    return 1;

  // Test: U32
  if(sizeof(cog::U32)!=4)
    return 1;

  // Test: I32
  if(sizeof(cog::I32)!=4)
    return 1;

  // Test: U64
  if(sizeof(cog::U64)!=8)
    return 1;

  // Test: I64
  if(sizeof(cog::I64)!=8)
    return 1;

  // Test: size_t
  if(sizeof(cog::size_t)==0)
    return 1;

  // Test: ptrdiff_t
  if(sizeof(cog::ptrdiff_t)==0)
    return 1;

  // Test: F32
  if(sizeof(cog::F32)!=4)
    return 1;

  // Test: F64
  if(sizeof(cog::F64)!=8)
    return 1;

  return 0;
}

