#pragma once

//
#include <Leo/_Prerequisites.h>
#include <Leo/IRenderTarget.h>

//
namespace Leo{
  
  //
  class CViewport;
  
  //
  class CRenderTarget : extends IRenderTarget{
  public: // Constructor & Destructor
    //
    CRenderTarget();
    
    //
    virtual ~CRenderTarget();
    
  public: // Inherited From Interface
    //
    virtual U32 getWidth()const;
    virtual U32 getHeight()const;
    
  public: // Extended Methods
    //
    virtual void _beginRender();
    void _render(CViewport* viewport);
    virtual void _endRender();
    
    //
    virtual void _flipBuffer();
    
  protected: // Protected Fields
    //
    U32 m_Width;
    U32 m_Height;
    
  };
  
}
