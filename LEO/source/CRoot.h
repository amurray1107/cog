#pragma once

//
#include <Leo/_Prerequisites.h>
#include <Leo/IRoot.h>

//
namespace Leo{
  
  class CRoot : extends IRoot{
  public: // Constructor & Destructor
    //
    CRoot();
    
    //
    virtual ~CRoot();
    
  public: // Inherited From Interface
    //
    virtual bool initialize();
    
    //
    virtual void run();
    
  public: // Extended Methods
    //
    
    
    
  private: // Private Fields
    
    
  };
  
}
