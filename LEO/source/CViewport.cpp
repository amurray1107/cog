#include "CViewport.h"
#include "CRenderTarget.h"

namespace Leo{
  
  CViewport::CViewport()
  {
  }
  
  CViewport::~CViewport()
  {
  }
  
  //
  
  F32 CViewport::getOriginX()const
  {
    return m_OriginX;
  }
  
  F32 CViewport::getOriginY()const
  {
    return m_OriginY;
  }
  
  F32 CViewport::getWidth()const
  {
    return m_Width;
  }
  
  F32 CViewport::getHeight()const
  {
    return m_Height;
  }
  
  //
  
  void CViewport::_setFrame(F32 x, F32 y, F32 width, F32 height)
  {
    m_OriginX = x;
    m_OriginY = y;
    m_Width = width;
    m_Height = height;
  }
  
  void CViewport::_render()
  {
  }
  
  //
  
  namespace{
    void _dummy()
    {
      CViewport a;
    }
  }
  
}

