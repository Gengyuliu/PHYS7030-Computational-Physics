/*	Romberg Integration	*/

/*	use Romberg integration to calculate the Fresnel integrals	*/



#include <stdio.h>
#include <math.h>
#include <malloc.h>
#define pi M_PI
#define max_itstep 10   /*	max iteration steps	*/
#define nu_max 5       /*	the max value of nu	*/
#define nu_min 0
void main()
{
    FILE *output1;
    output1 = fopen("intg_of_f.dat","w");
    
    
    float **Rom;
    Rom = (float **) malloc(max_itstep* sizeof(float**));
    for (int i = 0; i < max_itstep; ++i)
        Rom[i] =(float*) malloc(max_itstep * sizeof(float**));
    
    
    float accuracy = 1e-8;
    float f(float), g(float), Romberg(float**,float (*f)(float),float,float,size_t,float);


    /*	discretize the range of nu	*/
    float delta_nu = 0.01;
    int times = (int) (nu_max - nu_min)/delta_nu;
    /*	store the Fresnel integral as function of nu	*/
    float nu[times];
    float intg_of_f[times];
    for (int t = 0; t < times; ++t){
        nu[t] = nu_min + t* delta_nu;
        intg_of_f[t] = Romberg(Rom, f, nu_min, nu[t], max_itstep, accuracy);
        fprintf(output1, "%lf \t %.10f\n", nu[t],intg_of_f[t]);
    }
    
    printf("data stored\n");
    fclose(output1);
    return;
}



float f(float w){
    return sin(exp(-w));
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
float Romberg(float **R, float (*f)(float),float a,float b,size_t max_steps,float acc){
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
    return R[max_steps-1][max_steps-1];
}

