/****************************************************************************
*  second_diff.c: Second differentiation of the certain funtion at x = 2 with
*  *              Richarsion extrapolation difference method  *
*****************************************************************************/

#include <stdio.h>
#include <math.h>

void main()
{
    double h = 0.4; /*	the initial step	*/
    double x =  2;  /*	evaluate the function at x = 2	*/
    double f(double);
    double f_dprime(double);
    int c = 10;      /*	iteration step	*/
    double D[c][c];     /*	Richardson extrapolation at each h (i) and step (j)	*/


    FILE *output;    /*	save data in second_diff.data	*/
    output = fopen("second_diff.dat","w");
    
    fprintf(output, "   h          \t");
    fprintf(output, "   D_1        \t");
    fprintf(output, "   D_2        \t");
    fprintf(output, "   D_3        \t");
    fprintf(output, "   D_4        \t");
    fprintf(output, "   D_5        \n\n");


    FILE *fp7;
    fp7 = fopen("Step_7.txt","w");
    FILE *fp8;
    fp8 = fopen("Step_8.txt","w");
    FILE *fp9;
    fp9 = fopen("Step_9.txt","w");
    FILE *fp10;
    fp10 = fopen("Step_10.txt","w");



    for (int i = 0;i < c; ++i) {
        D[i][0] = (f(x+h) - 2*f(x) + f(x-h))/(h*h); /*	D_{1}(h/2^i)	*/
        fprintf(output, "%f      \t",h);
        for (int j = 0; j <= i; ++j) {
            if (j == 0){
                if (i == 0)
                    fprintf(output, "%.15f      \n",D[i][j]);
                else
                    fprintf(output, "%.15f      \t", D[i][j]);
            }
            else{                
                if (j != i){ 
                    D[i][j] = (pow(4,j)*D[i][j-1] - D[i-1][j-1])/(pow(4,j) - 1);
                    //printf("D[%d][%d] = %f\n",i,j,D[i][j]);
                    fprintf(output, "%.15f     \t", D[i][j]);
                }
                else{
                    D[i][j] = (pow(4,j)*D[i][j-1] - D[i-1][j-1])/(pow(4,j) - 1);
                    //printf("D[%d][%d] = %f\n",i,j,D[i][j]);
                    fprintf(output, "%.15f     \n\n", D[i][j]);
                }
            }
        }
        h /= 2;
    }




    fprintf(output, "%.15f\n",f_dprime(2));
    printf("data stored in second_diff.dat\n");
    fclose(output);

/*	different iteration steps plot	*/
    for (int i = 0; i < 7; ++i)
        fprintf(fp7, "%d\t %.15f\n",i+1,D[6][i]);
    for (int i = 0; i < 8; ++i)
        fprintf(fp8, "%d\t %.15f\n",i+1,D[7][i]);

    for (int i = 0; i < 9; ++i)
        fprintf(fp9, "%d\t %.15f\n",i+1,D[8][i]);

for (int i = 0; i < 10; ++i)
        fprintf(fp10, "%d\t %.15f\n",i+1,D[9][i]);

    fclose(fp7);
    fclose(fp8);
    fclose(fp9);
    fclose(fp10);

/*	same iteration step ->plot D as function of hh	*/

    FILE *it_1;
    it_1 = fopen("D_1-h.txt","w");
    double hh = 0.4;
    double exact_sol = f_dprime(2);
    for (int j = 0; j < 10; ++j){
        fprintf(it_1,"%.15f\t %.15f\n",hh,D[j][0] - exact_sol);
        hh /= 2;
    }
    fclose(it_1);
    
    FILE *it_2;
    it_2 = fopen("D_2-h.txt","w");
    hh = 0.4;
    for (int j = 1; j <= 9;  ++j){
        fprintf(it_2, "%.15f\t %.15f\n", hh, D[j][1] - exact_sol);
        hh /= 2;
    }
    fclose(it_2);
}

/*	function	*/

double f(double x)
{
    return x*exp(x);
}

double f_dprime(double x)
{
    return (x+2)*exp(x);
}

