#pragma once

#include <cstddef>
#include <climits>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////

#ifdef COG_ASSERT
#  undef COG_ASSERT
#endif

#define COG_ASSERT(x) assert(x)

////////////////////////////////////////////////////////////////////////////////

namespace cog{
  
  // 8-bit Char Type
#if (CHAR_BIT==8)
  typedef char C8;
#else
#  error Cannot Define C8
#endif
  
  // 8-bit Int Type
#if (UCHAR_MAX==0xff)
  typedef unsigned char U8;
#else
#  error Cannot Define U8
#endif
  
  // 8-bit Int Type
#if (SCHAR_MAX==0x7f)
  typedef signed char I8;
#else
#  error Cannot Define I8
#endif
  
  // 16-bit Int Type
#if (UINT_MAX==0xffff)
  typedef unsigned int U16;
#elif (USHRT_MAX==0xffff)
  typedef unsigned short U16;
#else
#  error Cannot Define U16
#endif
  
  // 16-bit Int Type
#if (SINT_MAX==0x7fff)
  typedef signed int I16;
#elif (SHRT_MAX==0x7fff)
  typedef signed short I16;
#else
#  error Cannot Define I16
#endif
  
  // 32-bit Int Type
#if (ULONG_MAX==0xffffffffUL)
  typedef unsigned long U32;
#elif (UINT_MAX==0xffffffff)
  typedef unsigned int U32;
#else
#  error Cannot Define U32
#endif
  
  // 32-bit Int Type
#if (LONG_MAX==0x7fffffffL)
  typedef signed long I32;
#elif (INT_MAX==0x7fffffff)
  typedef signed int I32;
#else
#  error Cannot Define I32
#endif
  
  // 64-bit Int Type
#if (ULONG_MAX==0xffffffffffffffffUL)
  typedef unsigned long U64;
#elif (ULLONG_MAX==0xffffffffffffffffULL)
  typedef unsigned long long U64;
#else
#  error Cannot Define U64
#endif
  
  // 64-bit Int Type
#if (LONG_MAX==0x7fffffffffffffffL)
  typedef signed long I64;
#elif (LLONG_MAX==0x7fffffffffffffffLL)
  typedef signed long long I64;
#else
#  error Cannot Define I64
#endif
  
  /*
  // Int Pointer Type
#if MOCHA_ADDRBITS == 64
  typedef U64 UnsignedPtr;
  typedef I64 SignedPtr;
#elif MOCHA_ADDRBITS == 32
  typedef U32 UnsignedPtr;
  typedef I32 SignedPtr;
#else
#  error Cannot Define UnsignedPtr and SignedPtr
#endif
  */
  
  // Size Type
  using std::size_t;
  
  // PitDiff Type
  using std::ptrdiff_t;
  
  // Single Float Type
  typedef float F32;
  
  // Double Float Type
  typedef double F64;
  
}

////////////////////////////////////////////////////////////////////////////////
