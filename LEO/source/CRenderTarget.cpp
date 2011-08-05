#include "CRenderTarget.h"
#include "CViewport.h"

namespace Leo{
  
  CRenderTarget::CRenderTarget()
  {
  }
  
  CRenderTarget::~CRenderTarget()
  {
  }
  
  //
  
  U32 CRenderTarget::getWidth()const
  {
    return m_Width;
  }
  
  U32 CRenderTarget::getHeight()const
  {
    return m_Height;
  }
  
  //
  
  void CRenderTarget::_beginRender()
  {
    
  }
  
  void CRenderTarget::_render(CViewport* viewport)
  {
    // glViewport
    
    //
    viewport->_render();
  }
  
  void CRenderTarget::_endRender()
  {
  }
  
  void CRenderTarget::_flipBuffer()
  {
  }
  
  //
  namespace{
    void _dummy()
    {
      CRenderTarget a;
    }
  }
  
}
