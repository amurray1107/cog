#include "CDisplay.h"

namespace Leo{
  
  CDisplay::CDisplay()
  {
  }
  
  CDisplay::~CDisplay()
  {
  }
  
  //
  
  
  
  //
  
  void CDisplay::_beginRender()
  {
    // glDrawBuffer
  }
  
  void CDisplay::_endRender()
  {
    // glFlush()
  }
  
  void CDisplay::_flipBuffer()
  {
  }
  
  //
  
  void CDisplay::_create(U32 width, U32 height)
  {
    
  }
  
  void CDisplay::_destroy()
  {
  }
  
  void CDisplay::_resize(U32 width, U32 height)
  {
    m_Width = width;
    m_Height = height;
  }
  
  // 
  namespace{
    void _dummy()
    {
      CDisplay a;
    }
  }
  
}

