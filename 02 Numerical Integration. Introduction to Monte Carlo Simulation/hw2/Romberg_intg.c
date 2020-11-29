/*	Romberg Integration	*/

/*	use Romberg integration to calculate the Fresnel integrals	*/

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#define pi M_PI
#define max_itstep 5   /*	max iteration steps	*/
#define nu_max 10       /*	the max value of nu	*/

void main()
{
    FILE *output1, *output2, *output3, *output4;
    output1 = fopen("S_nu.dat","w");
    output2 = fopen("C_nu.dat","w");
    output3 = fopen("I_I0.dat","w");
    output4 = fopen("check_R.dat","w");
    
    
    float **Rom;
    Rom = (float **) malloc(max_itstep* sizeof(float**));
    for (int i = 0; i < max_itstep; ++i)
        Rom[i] =(float*) malloc(max_itstep * sizeof(float));
    
    float *Rom_check;
    Rom_check = (float *) malloc(max_itstep * sizeof(float*));
 
    
    float accuracy = 1e-8;
    float f(float), g(float), Romberg(float**,float (*f)(float),float,float,size_t,float, float*);


    /*	discretize the range of nu	*/
    float delta_nu = 0.01;
    int times = (int) nu_max/delta_nu;
    /*	store the Fresnel integral as function of nu	*/
    float nu[times];
    float S[times], C[times], I_I0[times];
    for (int t = 0; t < times; ++t){ /*	evaluate at each x	*/
        nu[t] = t* delta_nu;
        S[t] = Romberg(Rom, f, 0, nu[t], max_itstep, accuracy,Rom_check);
        fprintf(output1, "%lf \t %.10f\n", nu[t], S[t]);
       
        fprintf(output4, "nu[%d] = %f\n",t,nu[t]); 
        for(int i = 1; i < max_itstep - 1; ++i){
            fprintf(output4, "%d\t %lf \n", i+1, Rom_check[i]);
        }



        C[t] = Romberg(Rom, g, 0, nu[t], max_itstep, accuracy, Rom_check);
        fprintf(output2, "%lf \t %.10f\n", nu[t], C[t]);

        I_I0[t] = 0.5*((C[t]+0.5)*(C[t]+0.5) + (S[t]+0.5)*(S[t]+0.5));
        fprintf(output3, "%lf \t %.10f\n", nu[t], I_I0[t]);
    }
    
    printf("data stored\n");
    fclose(output1);
    fclose(output2);
    fclose(output3);
    fclose(output4);

    return;
}

float f(float w){
    return sin(pi*w*w/2);
}
float g(float w){
    return cos(pi*w*w/2);
}

/*	Integration using trapezoid rule	*/
float Trapezoid(float (*f)(float), int N, float lwr_bound, float upr_bound){
    int n;
    float sum = 0.;
    float h, x = lwr_bound;
    h = (upr_bound - lwr_bound)/N;
    for (n = 1; n < N; ++n){
        x += h;
        sum += (*f)(x);
    }
    sum += 0.5*((*f)(lwr_bound) + (*f)(upr_bound));
    sum *= h;
    return sum;
}
/*	Romberg integration :
 *	integrate function f from a to b with max iteration steps max_steps	*/
float Romberg(float **R, float (*f)(float),float a,float b,size_t max_steps,float acc, float *R_check){
    int N = 1<<5;
    for (size_t i = 0; i < max_steps; ++i){
        R[i][0] = Trapezoid((*f), N, a, b);
        
        for (size_t j = 1; j <= i; ++j){
            R[i][j] = (pow(4,j)*R[i][j-1] - R[i-1][j-1])/(pow(4,j) - 1);
        }
        
        if (i > 0 && fabs(R[i][i] - R[i-1][i-1]) < acc)
            return R[i][i];
        N *= 2;
    }
    
    for(size_t i = 1; i < max_steps - 1; ++i){
        R_check[i] = (R[i-1][0] - R[i][0])/(R[i][0] - R[i+1][0]);
    }
    R_check[0] = 0;
    R_check[max_itstep - 1] = 0;


    return R[max_steps-1][max_steps-1];
}

