#include <stdio.h>
#include<malloc.h>

void printarray(double **A, int n );

void main(){
double **A;
int n = 3;
int row,col;
double *b;

A = (double **) malloc(n * sizeof(double**));

for (row = 0; row < n; row++) {
    A[row] = (double *) malloc(n * sizeof(double));
    }

// Initialize each element.
for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++) {
        printf("&A[%d][%d]= %p \t",row,col,&A[row][col]);
        scanf("%lf",&A[row][col]);  // or whatever value you want
    }
}

//print A
printf("\n...........array in main.................\n");
for (row = 0; row < n; row++) {
    for (col = 0; col < n; col++) {
        printf("A[%d][%d]=%p \t %lf",row,col,&A[row][col],A[row][col]);
        printf("\n");
    }
}

b = (double *) malloc(n * sizeof(double));

printf("\n enter the elemet of b \n"); // Initialize each element.
for (row = 0; row < n; row++){
    printf("address=%p \t",&b[row]);
    printf("b[%d]=",row);
    scanf("%lf",&b[row]);
    printf("\n");
}




printarray((double **)A, n );
free(A);
}// Print it

void printarray(double **A, int n ){
    int i;
    int j;
    printf("\n.....print A.............\n");
    for( j = 0; j < n; j++ ){
        for( i = 0; i < n; i ++){
            //printf("&A[%d][%d]= %p \t",j,i,&A[j][i]);
            printf( "%lf ", A[j][i] );
        }
        printf( "\n" );
    }
}
