#pragma once

//
#include "../CRoot.h"

//
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

//
namespace Leo{
  
  class CRootNS : public CRoot{
  public:
    CRootNS();
    virtual ~CRootNS();
    
    virtual void run(void);
    
  private:
    
    
  };
  
}

//
@interface LeoAppDelegate : NSObject<NSApplicationDelegate>
{
  @private Leo::CRootNS* m_RootInstance;
}

- (id)initWithRoot:(Leo::CRootNS*)instance;

@end
