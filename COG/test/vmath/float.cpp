#include "unit_test.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[])
{
  const float PI = 3.141592653589793f;
  
  // Test: abs
  for(float x=0.0f; x<100.0f; x+=0.01f){
    if(!cog::_test(cog::abs(x), ::fabsf(x)))
      return 1;
    if(!cog::_test(cog::abs(-x), ::fabsf(-x)))
      return 1;
  }
  
#if false
  
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
  
#endif
  
  // Test: rsqrt
  for(float x=0.001f; x<100.0f; x+=0.01f){
    if(!cog::_test(cog::rsqrt(x), 1.0f / ::sqrtf(x)))
      return 1;
  }
  
  // Test: sqrt
  for(float x=0.0f; x<100.0f; x+=0.01f){
    if(!cog::_test(cog::sqrt(x), ::sqrtf(x)))
      return 1;
  }
  
  // Test: floor
  for(float x=0.0f; x<100.0f; x+=0.01f){
    if(!cog::_test(cog::floor(x), ::floorf(x)))
      return 1;
    if(!cog::_test(cog::floor(-x), ::floorf(-x)))
      return 1;
  }
  
  // Test: acos
  for(float x=-1.0f; x<=1.0f; x+=0.01f){
    if(!cog::_test(cog::acos(x), ::acosf(x)))
      return 1;
  }
  
  // Test: sin
  for(float x=-0.5f*PI; x<=0.5f*PI; x+=0.01f*PI){
    if(!cog::_test(cog::sin(x), ::sinf(x)))
      return 1;
  }
  
  // Test: cos
  for(float x=0.0f; x<=PI; x+=0.01f*PI){
    if(!cog::_test(cog::cos(x), ::cosf(x)))
      return 1;
  }
  
  // Test: tan
  for(float x=-0.49f*PI; x<=0.49f*PI; x+=0.01f*PI){
    if(!cog::_test(cog::tan(x), ::tanf(x)))
      return 1;
  }
  
  // Test: copysign
  for(float x=0.0f; x<10.0f; x+=0.01f){
    for(float y=0.01f; y<10.0f; y+=0.1f){
      if(!cog::_test(cog::copysign(x, y), ::copysignf(x, y)))
        return 1;
      if(!cog::_test(cog::copysign(-x, y), ::copysignf(-x, y)))
        return 1;
      if(!cog::_test(cog::copysign(x, -y), ::copysignf(x, -y)))
        return 1;
      if(!cog::_test(cog::copysign(-x, -y), ::copysignf(-x, -y)))
        return 1;
    }
  }
  
  return 0;
}
