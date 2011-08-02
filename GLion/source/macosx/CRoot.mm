#include "CRoot.h"

namespace GLion{
  
  CRoot::CRoot()
  {
    m_Pool = [[NSAutoreleasePool alloc] init];
    NSLog(@"CRoot constructor...");
    
    m_App = [NSApplication sharedApplication];
    
    
  }
  
  CRoot::~CRoot()
  {
    NSLog(@"CRoot destructor...");
    [m_Pool drain];
    //[m_Pool release];
  }
  
  bool CRoot::initialize(const CStringParam& title)
  {
    NSLog(@"Initalizing... title = %s", title.get());
    
    
    return true;
  }
  
  bool CRoot::run()
  {
    NSLog(@"Start Running...");
    
    NSLog(@"End Running...");
    return true;
  }
  
  //////
  
  CRoot CRoot::sm_Instance;
  
  IRoot& IRoot::instance()
  {
    return CRoot::sm_Instance;
  }
  
}
