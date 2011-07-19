#pragma once

#include "base_type.h"

namespace cog{
  namespace atomic{
    
    // Assign
    inline I32 exchange( volatile I32* target, I32 value )
    {
#if defined(__GNUC__)
      return __sync_lock_test_and_set( target, value );
#elif defined(_MSC_VER)
      return _InterlockedExchange( (long*)target, value );
#else
#  error cog::atomic::exchange is not defined
#endif
    }
    
    // Fetch and Add
    inline I32 exchagne_add( volatile I32* target, I32 value )
    {
#if defined(__GNUC__)
      return __sync_fetch_and_add( target, value );
#elif defined(_MSC_VER)
      return _InterlockedExchangeAdd( (long*)target, value );
#else
#  error cog::atomic::exchagne_add is not defined
#endif
    }
    
    // Compare And Swap
    inline I32 compare_exchange( volatile I32* target, I32 exchg, I32 old )
    {
#if defined(__GNUC__)
      return __sync_val_compare_and_swap( target, old, exchg );
#elif defined(_MSC_VER)
      return _InterlockedCompareExchange( (long*)target, exchg, old );
#else
#  error cog::atomic::compare_exchange is not defined
#endif
    }
    
    // Increment
    inline I32 increase( volatile I32* target )
    {
#if defined(__GNUC__)
      return __sync_add_and_fetch( target, 1 );
#elif defined(_MSC_VER)
      return _InterlockedIncrement( (long*)target );
#else
#  error cog::atomic::increase is not defined
#endif
    }
    
    // Decrement
    inline I32 decrease( volatile I32* target )
    {
#if defined(__GNUC__)
      return __sync_add_and_fetch( target, -1 );
#elif defined(_MSC_VER)
      return _InterlockedDecrement( (long*)target );
#else
#  error cog::atomic::decrease is not defined
#endif
    }
    
  }
}
