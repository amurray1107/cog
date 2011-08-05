#include "CRootWIN.h"

namespace Leo{

  CRootWIN::CRootWIN()
  {
    m_ExecutionResult = 0;
    m_NumWindowsCreated = 0;
  }

  CRootWIN::~CRootWIN()
  {
  }

  //

  void CRootWIN::run()
  {
    ::MSG msg = {0};

    //
    if(m_NumWindowsCreated==0){
      TCHAR* s = TEXT("CRootWIN: No Window Created, Quit Message Loop\n");
      ::OutputDebugString(s);
      return;
    }

    //
    while(true){
      if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
        if(msg.message == WM_QUIT)
          break;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }else{
        // Idle Event
      }
    }

    //
    m_ExecutionResult = msg.wParam;
  }

  //
  void CRootWIN::_preInitialize(::HINSTANCE hInst)
  {
    m_Instance = hInst;
  }

  int CRootWIN::_getMessageLoopResult()const
  {
    return m_ExecutionResult;
  }

}

