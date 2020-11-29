#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int main(void){
    int i;
    double x = 0, y = 0, dx, dy;

    const gsl_rng_type *T;
    gsl_rng *r;

    gsl_rng_env_setup();
    T = gsl_rng_default;
    r =  gsl_rng_alloc(T);

    printf("%g %g\n",x,y);
    FILE *fp;
    fp = fopen("random_walk.dat","w");


    for (i = 0; i < 100; ++i) {
        gsl_ran_dir_2d(r,&dx,&dy);
        x += dx; y += dy;
        printf("%g %g\n",x, y);     
        fprintf(fp,"%g \t %g\n", x, y);
    }
    fclose(fp);
    gsl_rng_free(r);
    return 0;

}
