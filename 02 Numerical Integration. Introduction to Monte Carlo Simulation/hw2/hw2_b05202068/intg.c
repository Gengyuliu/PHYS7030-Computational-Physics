/*	Numerical Integration with Trapezoidal, Simpson, and 5-point formulas	*/
#include <stdio.h>  
#include <math.h>


#define upper_bound M_PI 
#define low_bound  0



void main()
{
    
    int no = 4; /*	# of intervals	*/
    float result;
    float f(float);
    
    float Trapezoid(int N, float lwr_bnd, float upr_bnd);
    float Simpson(int N, float lwr_bnd, float upr_bnd);
    float Boole(int N, float lwr_bnd, float upr_bnd);

    FILE *output1, *output2, *output3, *output4;
    output1 = fopen("intg.dat","w"); /*	save data in integ.dat	*/
    output2 = fopen("intg_accuracy_Trap.dat","w");
    output3 = fopen("intg_accuracy_Simp.dat","w");
    output4 = fopen("intg_accuracy_Bool.dat","w");


    fprintf(output1, "N      Trapezoid \t\t");
    fprintf(output1, "Simpson    \t\t");
    fprintf(output1, "Boole      \n\n");


    for (int i = 0; i < 9; ++i){
        fprintf(output1, "%i\t", no);
        
        result = Trapezoid(no, low_bound, upper_bound);
        fprintf(output1, "%.10f\t\t", result);
        fprintf(output2, "%i %.10f\t\n", no, fabs(result - 2));

        result = Simpson(no, low_bound, upper_bound);
        fprintf(output1, "%.10f\t\t", result);
        fprintf(output3, "%i %.10f\t\n", no, fabs(result - 2));

        result = Boole(no, low_bound, upper_bound);
        fprintf(output1, "%.10f\n", result);
        fprintf(output4, "%i %.10f\n", no, fabs(result - 2));

        no *= 2;
    }
    printf("data stored in integ.dat and integ_accuracy.dat\n");
    fclose(output1);
    fclose(output2);
    fclose(output3);
    fclose(output4);
    return ;
}

/*	The function we want to integrate	*/
float f( float x ){
    return sin(x);
}

/*	2-point formula	*/
/*	Integration using trapezoid rule	*/
/*	N = number of intervals	*/
float Trapezoid(int N, float lwr_bnd, float upr_bnd){
    int n;
    float h, sum = 0., x = lwr_bnd;
    
    h = (upr_bnd - lwr_bnd)/N;
    for (n = 1; n < N; ++n) {
        x += h;
        sum  += h*f(x);
    }
    sum += 0.5*h*(f(lwr_bnd) + f(upr_bnd));
    return sum;
}

/*	3-point formula	*/
/*	Integration using Simpson's rule	*/
/*	# of intervals N must be even	*/
float Simpson(int N, float lwr_bnd, float upr_bnd){
    int n;
    float h, sum = 0., x = lwr_bnd;
    h = (upr_bnd - lwr_bnd)/N;

    for (n = 1; n < N; ++n){
        x += h;
        if (n % 2 == 1)
            sum += 4*f(x);
        else
            sum += 2*f(x);
    }
    sum += f(lwr_bnd) + f(upr_bnd);
    sum *= h/3;
    return sum;
}


/*	5-point formula	*/
/*	Integration using Boole's rule	*/
/*	# of intervals N must be the multiple of 4	*/
float Boole(int N, float lwr_bnd, float upr_bnd){
    int n;
    float h, sum = 0., x = lwr_bnd;
    h = (upr_bnd - lwr_bnd)/N;

    for (n = 1; n < N; ++n){
        x += h;
        if (n % 2 == 1)
            sum += 32*f(x);
        else{
            if(n % 4 ==2)
                sum += 12*f(x);
            else 
                sum += 14*f(x);
        }
    }
    sum += 7*(f(lwr_bnd) + f(upr_bnd));
    sum *= 2*h/45;
    return sum;
}
