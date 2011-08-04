#pragma once

//
#include <GLion/_Prerequisites.h>
#include <GLion/IRoot.h>

//
#include <CoreFoundation/CoreFoundation.h>

//
class NSAutoreleasePool;
class NSWindow;
class NSOpenGLView;
class NSOpenGLContext;

//
namespace GLion{
  
  class CRoot : public IRoot{
  public:
    CRoot();
    ~CRoot();
    
    virtual bool initialize(const CStringParam& title);
    
    virtual bool run(void);
    
  public:
    
    // Render One Frame
    void _kickOneFrame();
    
    // Init SubSystems
    void _initSystem();
    
    // Destroy SubSystems
    void _destroySystem();
    
  private:
    NSAutoreleasePool* m_Pool;
    
  public:
    static CRoot* inst(){ return &sm_Instance; }
    static CRoot sm_Instance;
  };
  
}


