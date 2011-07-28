#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  const int n = 16;
  
  int x[2][n];
  memset(x, 0, sizeof(int)*n*2);
  x[0][0] = 1;
  x[1][0] = 1;
  
  int c = 1;
  for(int i=0;i<n;i++){
    for(int j=1;j<=i;j++)
      x[c][j] = x[(c+1)%2][j-1] + x[(c+1)%2][j];
    
    printf("{ %d", x[c][0]);
    
    for(int j=1;j<=i;j++)
      printf(", %d", x[c][j]);
    
    for(int j=i+1; j<n; j++)
      printf(", 0");
    
    printf(" }, \n");
    
    c = (c+1)%2;
  }
  
  return 0;
}
