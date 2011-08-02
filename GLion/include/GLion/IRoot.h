#pragma once

#include "_Prerequistes.h"

namespace GLion{
  
  class IDisplay;
  
  class IRoot{
  public:
    
    //
    
    
    //
    IDisplay* initialize(const CStringParam& title);
    
    //
    bool run();
    
    //
    const char* getError()const;
    
  };
  
}
