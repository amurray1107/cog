#include <COG/cog.h>

using namespace cog;

int main()
{
  volatile I32 x = 0;
  I32 y;

  y = atomic::exchange(&x, 10);
  if(x!=10 || y!=0)
    return 1;

  y = atomic::exchagne_add(&x, 100);
  if(x!=110 || y!=10)
    return 1;

  atomic::increase(&x);
  if(x!=111)
    return 1;

  atomic::decrease(&x);
  if(x!=110)
    return 1;

  y = atomic::compare_exchange(&x, -10, 1);
  if(x!=110 || y!=110)
    return 1;

  y = atomic::compare_exchange(&x, -10, 110);
  if(x!=-10 || y!=110)
    return 1;

  return 0;
}

