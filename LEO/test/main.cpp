#include <Leo/Leo.h>

using namespace Leo;

int LeoMain(IRoot* root)
{
  root->initialize();
  
  root->run();
  
  return 0;
}
