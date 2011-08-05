#include "CRootNS.h"
#include <Leo/Leo.h>

//
namespace
{
  Leo::CRootNS g_RootInstance;
}

//
int main(int argc, char* argv[])
{
  LeoMain(&g_RootInstance);
  
  return 0;
}

