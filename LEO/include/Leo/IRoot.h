#pragma once

//
#include "_Prerequisites.h"

//
namespace Leo{
  
  class IRoot{
  public:
    
    //
    virtual bool initialize()=0;
    
    //
    virtual void run()=0;
    
  };
  
}

//
// Main Entrypoint of The App
// User Defined
extern int LeoMain(Leo::IRoot* root);
//
