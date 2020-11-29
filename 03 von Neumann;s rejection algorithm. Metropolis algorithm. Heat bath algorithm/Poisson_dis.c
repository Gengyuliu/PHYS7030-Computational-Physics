#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int main(void){

    const gsl_rng_type *T;
    gsl_rng *r;

    int i, n = 100;
    double mu = 1.0, kk = -5, dk = 0.1;

    /*	create a generator chosen by the environment variable 	GSL_RNG_TYPE*/

    gsl_rng_env_setup();

    T = gsl_rng_default;
    r = gsl_rng_alloc(T);   /*	generator	*/
    
    FILE *fp;
    fp = fopen("Gaussian.txt","w");
    /*	print n random variates chosen from the Poisson distribution with mean parameter mu	*/
    for (i = 0; i < n; ++i) {
        unsigned int k = gsl_ran_poisson(r, mu);
        double f = gsl_ran_gaussian_pdf(kk, mu);
        fprintf(fp, "%f\t %f\n",kk,f);
        printf("%u p(%d) = %f\n", k, k, f);
        kk += dk;
    }
    fclose(fp);
    gsl_rng_free(r);
    return 0;
}
