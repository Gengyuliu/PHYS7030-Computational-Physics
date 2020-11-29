/********
* hello *                 
********/

#include <stdio.h>

void main()
{
  char name[100];
  double  y;

  printf("Hello, please enter your name\n"); 
                                          
/*  scanf("%s",&name);  */  /* scanf only reads characters without space */
  gets(name);               /* get a string of characters */   
start:
  printf("%s, please enter a double precision real number\n",name);
  scanf("%lf",&y);
  printf("The number you have entered is %40.20e\n",y);
  goto start;
}


