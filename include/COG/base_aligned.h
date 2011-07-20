#pragma once

#include "base_type.h"

////////////////////////////////////////////////////////////////////////////////
// PACKED TYPE

#ifdef COG_TYPE_PACKED
#  undef COG_TYPE_PACKED
#endif

#if defined(__GNUC__)
#  define COG_TYPE_PACKED(t) t __attribute__((__packed__))

#elif defined(_MSC_VER)
#  define COG_TYPE_PACKED(t) __declspec(align(1)) t

#endif

#ifndef COG_TYPE_PACKED
#  error COG_TYPE_PACKED is not defined
#endif

////////////////////////////////////////////////////////////////////////////////
// ALIGNED TYPE

#ifdef COG_ALIGNED
#  undef COG_ALIGNED
#endif

#ifdef COG_TYPE_ALIGNED
#  undef COG_TYPE_ALIGNED
#endif

#if defined(__GNUC__)
#  define COG_ALIGNED(a) __attribute__((__aligned__(a)))
#  define COG_TYPE_ALIGNED(t, a) t COG_ALIGNED(a)

#elif defined(_MSC_VER)
#  define COG_ALIGNED(a) __declspec(align(a))
#  define COG_TYPE_ALIGNED(t, a) COG_ALIGNED(a) t

#endif

#ifndef COG_ALIGNED
#  error COG_ALIGNED is not defined
#endif

#ifndef COG_TYPE_ALIGNED
#  error COG_TYPE_ALIGNED is not defined
#endif

////////////////////////////////////////////////////////////////////////////////

namespace cog{
  
  union pointer_union{
    ptrdiff_t signed_ptr;
    void* raw_ptr;
    const void* const_raw_ptr;
  };
  
  ///////
  
  template<typename P>
  inline P _align_address(P addr, size_t alignment)
  {
    COG_ASSERT( alignment > 0 );
    COG_ASSERT( (alignment & (alignment-1)) == 0 );
    return (addr+alignment-1) & (alignment-1);
  }
  
  inline ptrdiff_t align_address(ptrdiff_t addr, size_t alignment)
  {
    return _align_address(addr, alignment);
  }
  
  inline void* align_address(void* addr, size_t alignment)
  {
    pointer_union u; u.raw_ptr = addr;
    u.signed_ptr = _align_address(u.signed_ptr, alignment);
    return u.raw_ptr;
  }
  
  inline const void* align_address(const void* addr, size_t alignment)
  {
    pointer_union u; u.const_raw_ptr = addr;
    u.signed_ptr = _align_address(u.signed_ptr, alignment);
    return u.const_raw_ptr;
  }
  
}

////////////////////////////////////////////////////////////////////////////////

