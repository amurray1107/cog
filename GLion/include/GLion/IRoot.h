#pragma once

#include "_Prerequisites.h"

namespace GLion{
  
  class IRoot{
  public:
    
    //
    virtual bool initialize(const CStringParam& title)=0;
    
    //
    virtual bool run(void)=0;
    
  public:
    static IRoot& instance();
    
  };
  
}
