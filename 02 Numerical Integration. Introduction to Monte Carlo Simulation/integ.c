/***********************************************************************
*                                                                      *
*  integ.c:  Integration using trapezoidal, Simpson and Gauss rules    * 
*                                                                      *
***********************************************************************/

#include <stdio.h>
#include <math.h>
 
#define max_in  501                     /* max number of intervals */
#define vmin    0.0                     /* ranges of integration */
#define vmax    1.0			
#define ME      2.7182818284590452354E0      /* Euler's number */

/**************************************************************
*  gauss.c: Points and weights for Gaussian quadrature        *
**************************************************************/

void gauss(int npts, int job, double a, double b, double x[], double w[])
{    

/*     npts     number of points                                       */
/*     job = 0  rescaling uniformly between (a,b)                      */
/*           1  for integral (0,b) with 50% points inside (0, ab/(a+b))*/
/*           2  for integral (a,inf) with 50% inside (a,b+2a)          */
/*     x, w     output grid points and weights.                        */ 

      int     m, i, j; 
      double  t, t1, pp, p1, p2, p3;
      double  pi = 3.1415926535897932385E0;
      double  eps = 3.e-10;			/* limit for accuracy */
      
      m = (npts+1)/2;
      for(i=1; i<=m; i++)
      {  
         t  = cos(pi*(i-0.25)/(npts+0.5));
         t1 = 1;
         while((fabs(t-t1))>=eps)
         { 
            p1 = 1.0;
            p2 = 0.0;
            for(j=1; j<=npts; j++)
            {
               p3 = p2;
               p2 = p1;
               p1 = ((2*j-1)*t*p2-(j-1)*p3)/j;
	    }
            pp = npts*(t*p1-p2)/(t*t-1);
            t1 = t;
            t  = t1 - p1/pp;
         }   
         x[i-1] = -t;
         x[npts-i] = t;
         w[i-1]    = 2.0/((1-t*t)*pp*pp);
         w[npts-i] = w[i-1];
      } 

      if(job==0) 
      {
         for(i=0; i<npts ; i++)
         {
            x[i] = x[i]*(b-a)/2.0+(b+a)/2.0;
            w[i] = w[i]*(b-a)/2.0;
         }
      }
      if(job==1) 
      {
         for(i=0; i<npts; i++)
         {
            x[i] = a*b*(1+x[i]) / (b+a-(b-a)*x[i]);
            w[i] = w[i]*2*a*b*b /((b+a-(b-a)*x[i])*(b+a-(b-a)*x[i]));
         }
      }
      if(job==2) 
      {
         for(i=0; i<npts; i++)
         {
            x[i] = (b*x[i]+b+a+a) / (1-x[i]);
            w[i] =  w[i]*2*(a+b)  /((1-x[i])*(1-x[i]));
         }
      }
}


void main()
{
   int i;			 
   float result;
   float f(float);		        /* subroutine containing */   
                             		/* function to integrate */
   float trapez  (int no, float min, float max);    /* trapezoid rule */
   float simpson (int no, float min, float max);    /* Simpson's rule */
   float gaussint(int no, float min, float max);    /* Gauss' rule */
   
   FILE *output;		        /* save data in integ.dat */
   output = fopen("integ.dat","w");

   fprintf(output, "N       trapezoid \t");
   fprintf(output, "Simpson   \t");
   fprintf(output, "Guass     \n\n");

   for (i=3; i<=max_in; i+=2)	    	/* Simpson's rule requires */
   { 					/* odd number of intervals */
      result = trapez(i, vmin, vmax);
      fprintf(output, "%i\t%e\t", i, fabs(result-1+1/ME));
      
      result = simpson(i, vmin, vmax);
      fprintf(output, "%e\t", fabs(result-1+1/ME));
      
      result = gaussint(i, vmin, vmax);
      fprintf(output, "%e\n", fabs(result-1+1/ME));
   }
   printf("data stored in integ.dat\n");
   fclose(output);
}
/*------------------------end of main program-------------------------*/

/* the function we want to integrate */

float f (float x)
{ 
   return (exp(-x));               
}

/* Integration using trapezoid rule */

float trapez (int no, float min, float max)
{
   int n;				
   float interval, sum=0., x;		 

   interval = ((max-min) / (no-1));
   for (n=2; n<no; n++)           	/* sum the midpoints */
   {
      x    = interval * (n-1);      
      sum += f(x)*interval;
   }
   sum += 0.5 *(f(min) + f(max)) * interval;	/* add the endpoints */

   return (sum);
}      

/* Integration using Simpson's rule */ 

float simpson (int no, float min, float max)
{  
   int n;				 
   float interval, sum=0., x;
   interval = ((max -min) /(no-1));
   
   for (n=2; n<no; n+=2)                /* loop for odd points  */
   {
       x = interval * (n-1);
       sum += 4 * f(x);
   }
   for (n=3; n<no; n+=2)                /* loop for even points  */
   {
      x = interval * (n-1);
      sum += 2 * f(x);
   }   
   sum +=  f(min) + f(max);	 	/* add first and last value */          
   sum *= interval/3.;        		/* then multilpy by interval*/
   
   return (sum);
}  

/* Integration using Gauss' rule */ 

float gaussint (int no, float min, float max)
{
   int n; 			 
   float quadra = 0.;
   double w[1000], x[1000];             /* for points and weights */
   
   gauss(no, 0, min, max, x, w);        /* returns Legendre */
   					/* points and weights */
   for (n=0; n< no; n++)
   {                               
      quadra += f(x[n])*w[n];           /* calculating the integral */
   }   
   return (quadra);                  
}
