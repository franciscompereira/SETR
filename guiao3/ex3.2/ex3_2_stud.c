// EX3_2 - explore the advantages of paralellizing compuations via threads 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <time.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

#define NBINS	100	// Number of bins for histogram
#define RANGE   100		// Range for random numbers (-RANGE to +RANGE)

// Struct for storing the results - single threaded
typedef struct {
    double * sortArr;		// For array sorting function 
    double * matTransf;		// For mathematical transformation 
    int * hist;				// For histogram computation
} Stats_t;

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

static double rand_uniform_range(int range) {
    // drand48() returns [0.0, 1.0); scale to [-range, +range]
    return (drand48() * (double)2*range) - (double)range;    
}

static void fill_random(double *a, int n,int range) {
	int i;
	
    for (i = 0; i < n; ++i) {
		a[i] = rand_uniform_range(range);
	}
	return;
}

/* 
 * Compare function for qsort 
 */
int compare_doubles(const void *a, const void *b)
{
    double da = *(const double *)a;
    double db = *(const double *)b;

    if (da < db)
		return -1;
    if (da > db)
		return 1;
    return 0;
}

/*
 * Approach A - one thread computes all values
 */
void compute_all_one_thread(const double *a, int n, Stats_t *s) {
    int i, bin;
     
	// QuickSort operation
	memcpy(s->sortArr,a,n*sizeof(double));
	qsort(s->sortArr, n, sizeof(double), compare_doubles);

    // Generic matTransf computation
	memcpy(s->matTransf,a,n*sizeof(double));
	for (i = 0; i < n; ++i) {
		s->matTransf[i] = sin(s->matTransf[i]) + sqrt(fabs(s->matTransf[i])) * exp(-s->matTransf[i] * s->matTransf[i]);
	}
	
    // Histogram computation
    for (i = 0; i < NBINS; i++) {
		s->hist[i] = 0;
	}
    for (i = 0; i < n; i++) {
		bin = (int)((a[i] + 100.0) / 2.0);  // Map [-100,100] → 100 bins
		if (bin >= 0 && bin < 100)
			s->hist[bin]++;
	}
   
    return;
}


/* 
 * The main() function
 */
int main() {
    int N = 100000;     	// default array size
    long seed = 0;          // default seed; 0 means use time(NULL)
	double *arr;			// Pointer to array
	struct timespec t0, t1;	// For measuring computation time
	Stats_t s1T;			// Computation results for single thread version
	
	uint64_t totalA_ns;		// Time taken
    
    // Init seed with a fixed value to make it repeatible
    srand48(seed);

    // Allocate memory for the array
    arr = (double*)malloc(N * sizeof(double));
    if (!arr) {
        fprintf(stderr, "Allocation failed for N=%u\n", N);
        return 1;
    }

    // Fill once; we’ll reuse the same data for fairness between approaches
    fill_random(arr, N, RANGE);
    
    // Prepare input/output args
    s1T.sortArr = (double *)malloc(N * sizeof(double));
    s1T.matTransf = (double *)malloc(N * sizeof(double));
    s1T.hist = (int *)malloc(NBINS * sizeof(int));
    	
	// Execute processing - one thread
	clock_gettime(CLOCK_MONOTONIC, &t0);
    compute_all_one_thread(arr, N, &s1T);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    totalA_ns = (ts_to_ns(&t1) - ts_to_ns(&t0));
	
    // After all timing is complete, we can safely print without affecting measured times
    printf("Single thread:\n");
    printf("Time taken was: %ld\n",totalA_ns);


	// Done! Release resources and finish
    free(arr);
    free(s1T.sortArr);
    free(s1T.matTransf);
    free(s1T.hist);
    return 0;
}
