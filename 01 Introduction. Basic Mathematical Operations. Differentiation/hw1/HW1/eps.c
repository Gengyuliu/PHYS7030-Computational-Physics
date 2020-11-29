/**********
* eps *     To determine machine precision (single/double precision)    
**********/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main()
{
  int   i, N=100;
  float x, eps_sgl = 1.0;
  printf("single precision\n");
  for(i=1; i<N; i++) {
    eps_sgl = eps_sgl/2.0;
    x = 1 + eps_sgl;    
    printf("i = %d  x = %25.20e  eps_sgl = %25.20e \n",i,x,eps_sgl);
    if(x==1.0) break;
  }

  double y,eps_dbl = 1.0;
  int j;
  printf("double precision\n");
  for (j = 1; j < N; ++j) {
      eps_dbl /=2.0;
      y = 1.0 + eps_dbl;
      printf("j = %d, y = %25.20e eps_dbl = %25.20e\n",j,y,eps_dbl);
      if(y == 1.0) exit(0);
  }
  

}  
