#pragma once

#include <cstddef>

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
