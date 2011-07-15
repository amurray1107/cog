#include <stdio.h>

int main(void)
{
#if defined(__i386__)||defined(__i486__)||defined(__i586__) \
    ||defined(__i686__)||defined(__x86__)||defined(_M_IX86)
  printf("x86");
  return 0;
  
#elif defined(__x86_64__)||defined(__amd64__) \
    ||defined(_M_AMD64)||defined(_M_X64)
  printf("x86_64");
  return 0;
  
#elif defined(__arm__)
  printf("arm");
  return 0;

#endif
  
  return 1;
}

