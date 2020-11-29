#include <stdio.h>

int main(){
    float b[4]={2,4,5,6}, *bb;
    bb = b + 3;
    printf("*bb = %f\n", *bb);
    for (int i=0; i <= 4; i++)
        printf("bb[%d] = %f\n",i,bb[i]);
    for (int i=0; i <= 4; i++)
        printf("b[%d] = %f\n",i,b[i]);
    return 0;
}
