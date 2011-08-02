#include <GLion/GLion.h>

using namespace GLion;

int main()
{
  GLion::IRoot::instance().initialize("Hello");
  
  GLion::IRoot::instance().run();
  
  return 0;
}
