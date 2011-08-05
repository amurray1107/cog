#pragma once

//
#include "_Prerequisites.h"

//
namespace Leo{
  
  //
  class IRenderTarget{
  public:
    
    //
    virtual U32 getWidth()const=0;
    virtual U32 getHeight()const=0;
    
  };
  
}
