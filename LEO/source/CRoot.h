#pragma once

#include <Leo/_Prerequisites.h>
#include <Leo/IRoot.h>

namespace Leo{
  
  class CRoot : public IRoot{
  public:
    //
    CRoot();
    
    //
    virtual ~CRoot();
    
  public:
    //
    virtual bool initialize();
    
    //
    virtual void run();
    
  public:
    //
    
    
    
  private:
    
    
  };
  
}
