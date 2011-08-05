#pragma once

//
#include <Leo/_Prerequisites.h>
#include <Leo/IViewport.h>

//
namespace Leo{
  
  //
  class CRenderTarget;
  
  //
  class CViewport : extends IViewport{
  public: // Constructor & Destructor
    //
    CViewport();
    
    //
    virtual ~CViewport();
    
  public: // Inherited From Interface
    //
    virtual F32 getOriginX()const;
    virtual F32 getOriginY()const;
    
    //
    virtual F32 getWidth()const;
    virtual F32 getHeight()const;
    
  public: // Extended Methods
    //
    void _setFrame(F32 x, F32 y, F32 width, F32 height);
    
    //
    void _render();
    
  private: // Private Fields
    //
    F32 m_OriginX;
    F32 m_OriginY;
    F32 m_Width;
    F32 m_Height;
    
  };
  
}
