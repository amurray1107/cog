#include "../vmath/unit_test.h"
#include <stdlib.h>
#include <string.h>

using namespace cog;

typedef basic_frustum<float> frustum;

int main()
{
  mat4 m1 = make_perspective(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 10.0f);
  mat4 m2 = make_orthographic(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 10.0f);
  
  // Test: Constructor
  {
    frustum f1(m1);
    frustum f2(m2);
    
    frustum f0 = f1;
    if(memcmp(&f0, &f1, sizeof(frustum)))
      return 1;
    
    f0 = f2;
    if(memcmp(&f0, &f2, sizeof(frustum)))
      return 1;
  }
  
  // Test: 
  
  return 0;
}

