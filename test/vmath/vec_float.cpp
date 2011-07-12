#include "unit_test.h"
#include <stdio.h>

using namespace cog;

#define TEST1(f,x) \
  do{if(!_test(x,f,f)){fprintf(stderr,#f" failed\n");return 1;}}while(0)

#define TEST2(f,x,y) \
  do{if(!_test(x,y,f,f)){fprintf(stderr,#f" failed\n");return 1;}}while(0)

#define TEST3(f,x,y,z) \
  do{if(!_test(x,y,z,f,f)){fprintf(stderr,#f" failed\n");return 1;}}while(0)

#define SPLATS(x) splats(x)

int main(int argc, char* argv[])
{
  const float PI = 3.141592653589793f;
  
  // Test: abs
  for(float x=0.0f; x<100.0f; x+=0.01f){
    TEST1(abs, SPLATS( x));
    TEST1(abs, SPLATS(-x));
  }
  
  // Test: negate
  for(float x=0.0f; x<100.0f; x+=0.01f){
    TEST1(negate, SPLATS( x));
    TEST1(negate, SPLATS(-x));
  }
  
  // Test: add
  for(float x=0.0f; x<10.0f; x+=0.01f){
    for(float y=0.0f; y<10.0f; y+=0.1f){
      TEST2(add, SPLATS( x), SPLATS( y));
      TEST2(add, SPLATS( x), SPLATS(-y));
      TEST2(add, SPLATS(-x), SPLATS( y));
      TEST2(add, SPLATS(-x), SPLATS(-y));
    }
  }
  
  // Test: sub
  for(float x=0.0f; x<10.0f; x+=0.01f){
    for(float y=0.0f; y<10.0f; y+=0.1f){
      TEST2(sub, SPLATS( x), SPLATS( y));
      TEST2(sub, SPLATS( x), SPLATS(-y));
      TEST2(sub, SPLATS(-x), SPLATS( y));
      TEST2(sub, SPLATS(-x), SPLATS(-y));
    }
  }
  
  // Test: mul
  for(float x=0.0f; x<10.0f; x+=0.01f){
    for(float y=0.0f; y<10.0f; y+=0.1f){
      TEST2(mul, SPLATS( x), SPLATS( y));
      TEST2(mul, SPLATS( x), SPLATS(-y));
      TEST2(mul, SPLATS(-x), SPLATS( y));
      TEST2(mul, SPLATS(-x), SPLATS(-y));
    }
  }
  
  // Test: madd
  for(float x=0.0f; x<10.0f; x+=1.0f){
    for(float y=0.0f; y<10.0f; y+=1.0f){
      for(float z=0.0f; z<10.0f; z+=0.1f){
        TEST3(madd, SPLATS( x), SPLATS( y), SPLATS( z));
        TEST3(madd, SPLATS( x), SPLATS( y), SPLATS(-z));
      }
    }
  }
  
  // Test: nmsub
  for(float x=0.0f; x<10.0f; x+=1.0f){
    for(float y=0.0f; y<10.0f; y+=1.0f){
      for(float z=0.0f; z<10.0f; z+=0.1f){
        TEST3(nmsub, SPLATS( x), SPLATS( y), SPLATS( z));
        TEST3(nmsub, SPLATS( x), SPLATS( y), SPLATS(-z));
      }
    }
  }
  
  // Test: min
  for(float x=0.0f; x<10.0f; x+=0.01f){
    for(float y=0.0f; y<10.0f; y+=0.1f){
      TEST2(min, SPLATS( x), SPLATS( y));
      TEST2(min, SPLATS( x), SPLATS(-y));
      TEST2(min, SPLATS(-x), SPLATS( y));
      TEST2(min, SPLATS(-x), SPLATS(-y));
    }
  }
  
  // Test: max
  for(float x=0.0f; x<10.0f; x+=0.01f){
    for(float y=0.0f; y<10.0f; y+=0.1f){
      TEST2(max, SPLATS( x), SPLATS( y));
      TEST2(max, SPLATS( x), SPLATS(-y));
      TEST2(max, SPLATS(-x), SPLATS( y));
      TEST2(max, SPLATS(-x), SPLATS(-y));
    }
  }
  
  // Test: recip
  for(float x=0.001f; x<100.0f; x+=0.01f){
    TEST1(recip, SPLATS( x));
    TEST1(recip, SPLATS(-x));
  }
  
  // Test: div
  for(float x=0.0f; x<10.0f; x+=0.01f){
    for(float y=0.01f; y<10.0f; y+=0.1f){
      TEST2(div, SPLATS( x), SPLATS( y));
      TEST2(div, SPLATS( x), SPLATS(-y));
      TEST2(div, SPLATS(-x), SPLATS( y));
      TEST2(div, SPLATS(-x), SPLATS(-y));
    }
  }
  
  // Test: rsqrt
  for(float x=0.001f; x<100.0f; x+=0.01f){
    TEST1(rsqrt, SPLATS( x));
  }
  
  // Test: sqrt
  for(float x=0.0f; x<100.0f; x+=0.01f){
    TEST1(sqrt, SPLATS( x));
  }
  
  // Test: floor
  for(float x=0.0f; x<100.0f; x+=0.01f){
    TEST1(floor, SPLATS( x));
    TEST1(floor, SPLATS(-x));
  }
  
  // Test: acos
  for(float x=-1.0f; x<=1.0f; x+=0.01f){
    TEST1(acos, SPLATS( x));
  }
  
  // Test: sin
  for(float x=-0.5f*PI; x<=0.5f*PI; x+=0.01f*PI){
    TEST1(sin, SPLATS(x));
  }
  
  // Test: cos
  for(float x=0.0f; x<=PI; x+=0.01f*PI){
    TEST1(cos, SPLATS(x));
  }
  
  // Test: tan
  for(float x=-0.49f*PI; x<=0.49f*PI; x+=0.01f*PI){
    TEST1(tan, SPLATS( x));
  }
  
  // Test: mod
  for(float x=0.0f; x<10.0f; x+=0.01f){
    for(float y=0.01f; y<10.0f; y+=0.1f){
      TEST2(mod, SPLATS( x), SPLATS( y));
      TEST2(mod, SPLATS(-x), SPLATS( y));
      TEST2(mod, SPLATS( x), SPLATS(-y));
      TEST2(mod, SPLATS(-x), SPLATS(-y));
    }
  }
  
  // Test: copysign
  for(float x=0.0f; x<10.0f; x+=0.01f){
    for(float y=0.01f; y<10.0f; y+=0.1f){
      TEST2(copysign, SPLATS( x), SPLATS( y));
      TEST2(copysign, SPLATS(-x), SPLATS( y));
      TEST2(copysign, SPLATS( x), SPLATS(-y));
      TEST2(copysign, SPLATS(-x), SPLATS(-y));
    }
  }
  
  return 0;
}
