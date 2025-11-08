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
  double *intVal; // This pointer will let the thread write its result
                  // directly into integ_s1, integ_s2, etc.
} tIArgs_type;

/* * Auxiliary function, to handle time and fill the array
 */

static inline uint64_t ts_to_ns(const struct timespec *t) {
    return (uint64_t)t->tv_sec * 1000000000ull + (uint64_t)t->tv_nsec;
}

static inline double ns_to_s(uint64_t ns) {
    return (double)ns / 1e9;
}

/* * Function to integrate: 1 / (1 + x^2)
 */

static inline double func(double x) {    
    return 1.0 / (1.0 + pow(x,2.0));
}

/*
 * Computes the integral of func on [lower, upper] with nsteps trapezoids
 * */

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

// -------------------------------------------------------------------
// --- NEW THREAD WORKER FUNCTION ---
// -------------------------------------------------------------------

/**
 * @brief A "wrapper" function that is compatible with pthread_create.
 * It will unpack the void* argument and call the real integrate function.
 */
void* integration_worker(void* arg) {
    tIArgs_type* thread_args = (tIArgs_type*)arg;

    // 2. Extract the arguments
    double lower = thread_args->lower;
    double upper = thread_args->upper;
    long long nsteps = thread_args->nsteps;
    double *intVal = thread_args->intVal;

    // 3. Call the *real* integration function to do the work
    int res = numIntegrate(lower, upper, nsteps, intVal);
    
    if (res != EXIT_SUCCESS) {
        printf("Thread calculation failed!\n");
    }

    // 4. Exit the thread
    pthread_exit(NULL);
}


/*
 * main()
 */

int main() {
    double a = 0.0, b = 10.0;       // Integration limits
    double sa, sb, segsize = 0, stepSize; // Variables for segments
    long long np = 1000000000, snp = 0;   // Number of poinst - total and segment
    int nseg = 0;             // Total segmnets
    double integral=0,integ_s1=0, integ_s2=0, 
    integ_s3=0, integ_s4=0;       // Integral results
    int res;                // Function return code
    struct timespec t0, t1;         // For measuring computation time
    uint64_t total_ns;

    
    
    /* Compute the integral - single thread */
    printf("--- Running Single-Threaded Version ---\n");
    clock_gettime(CLOCK_MONOTONIC, &t0);
    res=numIntegrate(a, b, np, &integral);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    total_ns = (ts_to_ns(&t1) - ts_to_ns(&t0));
    
    if(res == EXIT_SUCCESS) {
        printf("Integral on [%.6f, %.6f] with n=%lld = %.12f\n", a, b, np, integral);
        printf("Took %.6f seconds to complete\n", ns_to_s(total_ns));
    } else {
        printf("Integral computation failed \n");
        exit(EXIT_FAILURE);
    }
    
    // -------------------------------------------------------------------
    // --- MODIFIED 4-SEGMENT VERSION (following your logic) ---
    // -------------------------------------------------------------------
    
    printf("\n--- Running 4-Thread Parallel Version ---\n");
    clock_gettime(CLOCK_MONOTONIC, &t0);
    nseg=4;         // Number of segments
    snp = np/nseg;      // Number of points in each segment
    segsize = (b-a) / (double) nseg;  // The segment range
    res = 0;
    
    // --- Declare thread IDs and argument structs ---
    pthread_t t1_id, t2_id, t3_id, t4_id;
    tIArgs_type t1_args, t2_args, t3_args, t4_args;

    // --- FORK PHASE (Create 4 threads) ---
  
    // --- Segment 1 ---
    sa = a;
    sb = sa + segsize; // Fixed the bug from the original code
    t1_args = (tIArgs_type){.lower=sa, .upper=sb, .nsteps=snp, .intVal=&integ_s1};
    res = pthread_create(&t1_id, NULL, integration_worker, &t1_args);
    if(res != 0) {   
        printf("Thread creation failed - segment 1\n");
        exit(EXIT_FAILURE);
    }
        
    // --- Segment 2 ---
    sa = a + segsize;
    sb = sa + segsize; // Fixed the bug from the original code
    t2_args = (tIArgs_type){.lower=sa, .upper=sb, .nsteps=snp, .intVal=&integ_s2};
    res = pthread_create(&t2_id, NULL, integration_worker, &t2_args);
    if(res != 0) {   
        printf("Thread creation failed - segment 2\n");
        exit(EXIT_FAILURE);
    }
        
    // --- Segment 3 ---
    sa = a + 2*segsize;
    sb = sa + segsize; // Fixed the bug from the original code
    t3_args = (tIArgs_type){.lower=sa, .upper=sb, .nsteps=snp, .intVal=&integ_s3};
    res = pthread_create(&t3_id, NULL, integration_worker, &t3_args);
    if(res != 0) {   
        printf("Thread creation failed - segment 3\n");
        exit(EXIT_FAILURE);
    }
    
    // --- Segment 4 ---
    sa = a + 3*segsize;
    sb = b; // Use 'b' for the final boundary to avoid floating point errors
    t4_args = (tIArgs_type){.lower=sa, .upper=sb, .nsteps=snp, .intVal=&integ_s4};
    res = pthread_create(&t4_id, NULL, integration_worker, &t4_args);
    if(res != 0) {   
        printf("Thread creation failed - segment 4\n");
        exit(EXIT_FAILURE);
    }

    // --- JOIN PHASE (Wait for all threads to finish) ---
    printf("Main thread waiting for all 4 threads to join...\n");
    pthread_join(t1_id, NULL);
    pthread_join(t2_id, NULL);
    pthread_join(t3_id, NULL);
    pthread_join(t4_id, NULL);
    printf("All threads have joined.\n");

    // --- AGGREGATE PHASE (Sum the results) ---
    // This code is now safe to run because we know all threads are done.
    integral = integ_s1 + integ_s2 + integ_s3 + integ_s4;
    
    clock_gettime(CLOCK_MONOTONIC, &t1);
    total_ns = (ts_to_ns(&t1) - ts_to_ns(&t0));
    
    printf("Integral on [%.6f, %.6f] with n=%lld = %.12f - 4-thread version \n", a, b, np, integral);
    printf("Took %.6f seconds to complete\n", ns_to_s(total_ns));
    
    
    // Done!
    return 0;
}