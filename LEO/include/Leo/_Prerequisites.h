#pragma once

//
#include <COG/cog.h>

//
namespace Leo{
  
  using cog::I32;
  using cog::U32;
  using cog::F32;
  
}

//
#define extends virtual public

//
namespace Leo{
  
  //
  // Interface Rules
  //
  // 1. Naming: 'I'-leading. EX: IRoot
  //
  // 2. Declaration: class IRoot
  //
  // 3. Inheritance: class IDisplay : extends IRenderTarget
  //
  
  //
  // Implementation Runles
  //
  // 1. Naming: 'C'-leading. EX: CRoot
  // 
  // 2. Declaration: class CRoot : extends IRoot
  //
  // 3. Extend: class CDisplay : public CRenderTarget, extends IDisplay
  //
  
  /////////////////////////////
  
  // Forward Declaration
  //
  class IRoot;
  class IRenderTarget;
  class IDisplay;
  
}

