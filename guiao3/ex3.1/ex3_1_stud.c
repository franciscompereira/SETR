// EX3_1 - explore the advantages of paralellizing computations via threads 
// Students version

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h> // Timers
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <math.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
	double lower;
	double upper;
	long long nsteps;
	double *intVal;
} tIArgs_type;

/* 
 * Auxiliary function, to handle time and fill the array
 * 
 */

static inline uint64_t ts_to_ns(const struct timespec *t) {
    return (uint64_t)t->tv_sec * 1000000000ull + (uint64_t)t->tv_nsec;
}

static inline double ns_to_s(uint64_t ns) {
    return (double)ns / 1e9;
}

/* 
 * Function to integrate: 1 / (1 + x^2)
 */

static inline double func(double x) {    
    return 1.0 / (1.0 + pow(x,2.0));
}

/*
 *  Computes the integral of func on [lower, upper] with nsteps trapezoids
 * 
 */

int numIntegrate(double lower, double upper, long long nsteps, double *intVal)
{
    double stepSize, integration, k;
    long long i;
        
    // Check args
    if (nsteps <= 0) 
		return EXIT_FAILURE;

    stepSize = (upper - lower) / (double)nsteps;

    // Trapezoidal rule: h * [ (f(a)+f(b))/2 + sum_{i=1..n-1} f(a + i h) ]
    integration = 0.5 * (func(lower) + func(upper));

    for (i = 1; i <= nsteps - 1; ++i) {
        k = lower + i * stepSize;
        integration += func(k);
    }

    integration *= stepSize;
    
    *intVal = integration;
    return EXIT_SUCCESS;
}

/*
 * main()
 */

int main() {
    double a = 0.0, b = 10.0;				// Integration limits
    double sa, sb, segsize = 0, stepSize;	// Variables for segments
    long long np = 1000000000, snp = 0; 	// Number of poinst - total and segment
    int nseg = 0;							// Total segmnets
    double integral=0,integ_s1=0, integ_s2=0, 
		integ_s3=0, integ_s4=0;				// Integral results
    int res;								// Function return code
    struct timespec t0, t1;					// For measuring computation time
    uint64_t total_ns;

    
    
    /* Compute the integral - single thread */
    clock_gettime(CLOCK_MONOTONIC, &t0);
    res=numIntegrate(a, b, np, &integral);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    total_ns = (ts_to_ns(&t1) - ts_to_ns(&t0));
    
    if(res == EXIT_SUCCESS) {
		printf("Integral on [%.6f, %.6f] with n=%lld = %.12f\n", a, b, np, integral);
		printf("Took %ld to complete\n", total_ns);
	} else {
		printf("Integral computation failed \n");
		exit(EXIT_FAILURE);
    }
    
    /* Compute the integral - 4 segments */
    clock_gettime(CLOCK_MONOTONIC, &t0);
    nseg=4;					// Number of segments
    snp = np/nseg;			// Number of points in each segment
    segsize = (b-a) / (double) nseg;	// The segment range
    stepSize = (b - a) / (double)np;
    res = 0;

	
	sa=a;
    sb=sa+segsize-stepSize;
    res=numIntegrate(sa, sb, snp, &integ_s1);
    if(res != EXIT_SUCCESS) {		
		printf("Integral computation failed - segment 1\n");
		exit(EXIT_FAILURE);
	}
        
    sa=a+segsize;
    sb=sa+segsize-stepSize;
    res=numIntegrate(sa, sb, snp, &integ_s2);
    if(res != EXIT_SUCCESS) {		
		printf("Integral computation failed - segment 1\n");
		exit(EXIT_FAILURE);
	}
        
    sa=a+2*segsize;
    sb=sa+segsize-stepSize;
    res=numIntegrate(sa, sb, snp, &integ_s3);
    if(res != EXIT_SUCCESS) {		
		printf("Integral computation failed - segment 1\n");
		exit(EXIT_FAILURE);
	}
    
    sa=a+3*segsize;
    sb=sa+segsize;
    res=numIntegrate(sa, sb, snp, &integ_s4);
    if(res != EXIT_SUCCESS) {		
		printf("Integral computation failed - segment 1\n");
		exit(EXIT_FAILURE);
	}
	       
    integral = integ_s1 + integ_s2 + integ_s3 + integ_s4;
    
    clock_gettime(CLOCK_MONOTONIC, &t1);
    total_ns = (ts_to_ns(&t1) - ts_to_ns(&t0));
    
    printf("Integral on [%.6f, %.6f] with n=%lld = %.12f - segmented version \n", a, b, np, integral);
	printf("Took %ld to complete\n", total_ns);
    
    
    // Done!
    return 0;
}

