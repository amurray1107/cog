#pragma once

//
#include <Leo/_Prerequisites.h>
#include <Leo/IDisplay.h>

//
#include "CRenderTarget.h"

//
namespace Leo{
  
  class CDisplay : public CRenderTarget, extends IDisplay{
  public: // Constructor & Destructor
    //
    CDisplay();
    
    //
    virtual ~CDisplay();
    
  public: // Inherited From Interface
    //
    
    
  public: // Inherited From Super
    //
    virtual void _beginRender();
    virtual void _endRender();
    virtual void _flipBuffer();
    
  public: // Extended Methods
    //
    virtual void _create(U32 width, U32 height);
    
    //
    virtual void _destroy();
    
    //
    virtual void _resize(U32 width, U32 height);
    
  private: // Private Fields
    
    
  };
  
}

