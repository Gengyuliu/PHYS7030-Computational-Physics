/**********
* eps_dbl *   To determine machine precision (double precision)
**********/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main()
{
  int    i,N=100;
  double x,eps=1.0;

  for(i=1;i<N;i++) {
    eps = eps/2.0;
    x = 1 + eps;    
    printf("i = %d  x = %25.20e  eps =%25.20e \n",i,x,eps);
    if(x==1.0) exit(0);
  }
}  
