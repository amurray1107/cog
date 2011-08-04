#import <Cocoa/Cocoa.h>
#include <Leo/Leo.h>
#include "CRootNS.h"

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

