#pragma once

//
#include <Leo/_Prerequisites.h>
#include <Leo/IRoot.h>

//
namespace Leo{
  
  class CRoot : public IRoot{
  public: // Constructor & Destructor
    //
    CRoot();
    
    //
    virtual ~CRoot();
    
  public: // Inherited From Super
    //
    virtual bool initialize();
    
    //
    virtual void run();
    
  public: // Extended Methods
    //
    
    
    
  private: // Private Fields
    
    
  };
  
}
