#pragma once

//
#include "../CRoot.h"

//
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

//
namespace Leo{
  
  class CRootNS : public CRoot{
  public: // Constructor & Destructor
    CRootNS();
    virtual ~CRootNS();
    
  public: // Inherited From Super
    virtual void run(void);
    
  public: // Extended Methods
    
    
  private: // Private Fields
    
    
  };
  
}

//
@interface LeoAppDelegate : NSObject<NSApplicationDelegate>
{
  @private Leo::CRootNS* m_RootInstance;
}

- (id)initWithRoot:(Leo::CRootNS*)instance;

@end
