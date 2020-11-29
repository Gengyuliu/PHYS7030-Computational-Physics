/********
* hello *                
********/

#include <stdio.h>

void main()
{
  char name[100];
  float  x;

  printf("Hello, please enter your name\n"); 
                                          
/*  scanf("%s",&name);  */  /* scanf only reads characters without space */
  gets(name);               /* get a string of characters */   
start:
  printf("%s, please enter a real number\n",name);
  scanf("%e",&x);
  printf("The real number you have entered is %40.20e\n",x);
  goto start;
}


