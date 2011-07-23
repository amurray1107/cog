#include "unit_test.h"

using namespace cog;

typedef bool_<F32> boolf;
typedef bool_<VF32> boolvf;

int main()
{
  // Test: Constructor
  {
    boolf b0 = boolf::yes();
    boolf b1 = boolf::no();
    boolvf vb0 = boolvf::yes();
    boolvf vb1 = boolvf::no();
    
    if(b0._getRawValue() != true)
      return 1;
    if(b1._getRawValue() != false)
      return 1;
    if(!vb0._isSameAs(true))
      return 1;
    if(!vb1._isSameAs(false))
      return 1;
    
    b1 = b0;
    if(b1._getRawValue() != true)
      return 1;
    
    vb1 = vb0;
    if(!vb1._isSameAs(true))
      return 1;
  }
  
  // Test: Not
  if(( !boolf::yes())._getRawValue() != false)
    return 1;
  if(( !boolf::no())._getRawValue() != true)
    return 1;
  if(!(!boolvf::yes())._isSameAs(false))
    return 1;
  if(!(!boolvf::no())._isSameAs(true))
    return 1;
  
  // Test: And
  if((boolf::yes() && boolf::yes())._getRawValue() != true)
    return 1;
  if((boolf::yes() && boolf::no())._getRawValue() != false)
    return 1;
  if((boolf::no() && boolf::yes())._getRawValue() != false)
    return 1;
  if((boolf::no() && boolf::no())._getRawValue() != false)
    return 1;
  if(!(boolvf::yes() && boolvf::yes())._isSameAs(true))
    return 1;
  if(!(boolvf::yes() && boolvf::no())._isSameAs(false))
    return 1;
  if(!(boolvf::no() && boolvf::yes())._isSameAs(false))
    return 1;
  if(!(boolvf::no() && boolvf::no())._isSameAs(false))
    return 1;
  
  // Test: Or
  if((boolf::yes() || boolf::yes())._getRawValue() != true)
    return 1;
  if((boolf::yes() || boolf::no())._getRawValue() != true)
    return 1;
  if((boolf::no() || boolf::yes())._getRawValue() != true)
    return 1;
  if((boolf::no() || boolf::no())._getRawValue() != false)
    return 1;
  if(!(boolvf::yes() || boolvf::yes())._isSameAs(true))
    return 1;
  if(!(boolvf::yes() || boolvf::no())._isSameAs(true))
    return 1;
  if(!(boolvf::no() || boolvf::yes())._isSameAs(true))
    return 1;
  if(!(boolvf::no() || boolvf::no())._isSameAs(false))
    return 1;
  
  // Test: select
  if(boolf::yes().select(1.0f, -1.0f) != -1.0f)
    return 1;
  if(boolf::no().select(1.0f, -1.0f) != 1.0f)
    return 1;
  if(!_test(boolvf::yes().select(splats(1.0f), splats(-1.0f)), -1.0f))
    return 1;
  if(!_test(boolvf::no().select(splats(1.0f), splats(-1.0f)), 1.0f))
    return 1;
  
  // Test: less
  if(boolf::less(1.0f, 2.0f)._getRawValue() != true)
    return 1;
  if(boolf::less(1.0f, 1.0f)._getRawValue() != false)
    return 1;
  if(boolf::less(1.0f, -1.0f)._getRawValue() != false)
    return 1;
  if(!boolvf::less(splats(1.0f), splats(2.0f))._isSameAs(true))
    return 1;
  if(!boolvf::less(splats(1.0f), splats(1.0f))._isSameAs(false))
    return 1;
  if(!boolvf::less(splats(1.0f), splats(-1.0f))._isSameAs(false))
    return 1;
  
  // Test: less equal
  if(boolf::less_eq(1.0f, 2.0f)._getRawValue() != true)
    return 1;
  if(boolf::less_eq(1.0f, 1.0f)._getRawValue() != true)
    return 1;
  if(boolf::less_eq(1.0f, -1.0f)._getRawValue() != false)
    return 1;
  if(!boolvf::less_eq(splats(1.0f), splats(2.0f))._isSameAs(true))
    return 1;
  if(!boolvf::less_eq(splats(1.0f), splats(1.0f))._isSameAs(true))
    return 1;
  if(!boolvf::less_eq(splats(1.0f), splats(-1.0f))._isSameAs(false))
    return 1;
  
  // Test: equal
  if(boolf::equal(1.0f, 2.0f)._getRawValue() != false)
    return 1;
  if(boolf::equal(1.0f, 1.0f)._getRawValue() != true)
    return 1;
  if(boolf::equal(1.0f, -1.0f)._getRawValue() != false)
    return 1;
  if(!boolvf::equal(splats(1.0f), splats(2.0f))._isSameAs(false))
    return 1;
  if(!boolvf::equal(splats(1.0f), splats(1.0f))._isSameAs(true))
    return 1;
  if(!boolvf::equal(splats(1.0f), splats(-1.0f))._isSameAs(false))
    return 1;
  
  return 0;
}

