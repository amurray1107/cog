#include <COG/cog.h>
#include <stdio.h>

using namespace cog;

#pragma pack(push)
#pragma pack(1)
COG_TYPE_PACKED(struct) packed_type{
  U8 x;
  U32 y;
};

COG_TYPE_ALIGNED(struct, 16) aligned16_type{
  U32 x;
};

#pragma pack(pop)

int main()
{
  if(sizeof(packed_type)!=5)
    return 1;
  if(sizeof(aligned16_type)!=16)
    return 1;

  if(align_address((ptrdiff_t)0, 16)!=0)
    return 1;
  if(align_address((ptrdiff_t)10, 16)!=16)
    return 1;
  if(align_address((ptrdiff_t)32, 16)!=32)
    return 1;

  {
    U8* test_ptr = NULL;
    if(align_address(test_ptr, 16)!=test_ptr)
      return 1;
    if(align_address(test_ptr+11, 16)!=test_ptr+16)
      return 1;
    if(align_address(test_ptr+32, 16)!=test_ptr+32)
      return 1;
  }

  {
    const U8* test_ptr = NULL;
    if(align_address(test_ptr, 16)!=test_ptr)
      return 1;
    if(align_address(test_ptr+11, 16)!=test_ptr+16)
      return 1;
    if(align_address(test_ptr+32, 16)!=test_ptr+32)
      return 1;
  }

  COG_ALIGNED(16) U8 x;
  COG_ALIGNED(16) U8 y;
  COG_ALIGNED(16) U32 z;

  if(reinterpret_cast<ptrdiff_t>(&x) & 0xf)
    return 1;
  if(reinterpret_cast<ptrdiff_t>(&y) & 0xf)
    return 1;
  if(reinterpret_cast<ptrdiff_t>(&z) & 0xf)
    return 1;

  return 0;
}

