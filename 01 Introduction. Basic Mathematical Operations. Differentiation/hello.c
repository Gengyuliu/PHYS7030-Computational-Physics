/********
* hello *                 
********/

#include <stdio.h>

void main()
{
  char name[100];

  printf("Hello, please enter your name\n"); 
                                          
/*  scanf("%s",&name);  */  /* scanf only reads characters without space */
  gets(name);   
  printf("%s, you have a good day !\n",name);
}
