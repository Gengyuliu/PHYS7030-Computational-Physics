/********
* hello *                 
********/

#include <stdio.h>

void main()
{
  char name[100];
  int   ia; 

  printf("Hello, please enter your name\n"); 
                                          
/*  scanf("%s",&name);  */  /* scanf only reads characters without space */
  gets(name);               /* get a string of characters */   
start:
  printf("%s, please enter an integer\n",name);
  scanf("%d",&ia);
  printf("The integer you have entered is %20d\n",ia);
  goto start;
}


