//
#include <Leo/Leo.h>
#include "CRootWIN.h"

//
namespace
{
  Leo::CRootWIN g_RootInstance;
}

//
int CALLBACK WinMain
(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  //
  g_RootInstance._preInitialize(hInstance);

  //
  LeoMain(&g_RootInstance);

  //
  return g_RootInstance._getMessageLoopResult();
}

