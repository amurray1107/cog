#pragma once

//
#include <GLion/_Prerequisites.h>
#include <GLion/IRoot.h>

//
#import <Cocoa/Cocoa.h>

namespace GLion{
  
  class CRoot : public IRoot{
  public:
    CRoot();
    ~CRoot();
    
    virtual bool initialize(const CStringParam& title);
    
    virtual bool run();
    
    
  private:
    NSAutoreleasePool* m_Pool;
    NSApplication* m_App;
    
  public:
    static CRoot sm_Instance;
  };
  
}
