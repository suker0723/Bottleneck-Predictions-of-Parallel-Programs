// load imbalance
// this script tests the effect of load imbalance on the performance of parallel programs
// dummy function takes time propotional to the input n
// one can try different scheduling to see the effect
// idealy, (static 1) should be the best, (dynamic 1) slightly worse due to 
// the overhead of dynamic scheduling, (static) is the worst
// --------------------
// synchronization
// One can also add directive `nowait` to the first for loop 
// to see the time cost of synchronization
#include <stdio.h>
#include <math.h>
#include <omp.h>

void dummyfunc(int n, int scale){
    // run time proportional to n
    double x = 0;
    int N = n*scale;
    for(int i=0; i<N; i++){
        x += sin(i);
    }
}

int main(int argc, char** argv) {
    int p = atoi(argv[1]); //2
    int n = 100000; //atoi(argv[2]);
    int scale = 100;
    printf("number of threads: %d, n: %d, scale: %d\n", p, n, scale);
    double tstart, tend;
    tstart = omp_get_wtime();
    #pragma omp parallel num_threads(p)
    {
        // int p = omp_get_num_threads();
        // printf("number of threads: %d, n: %d, scale: %d\n", p, n, scale);
        // #pragma omp for schedule(static, 1)
        // #pragma omp for schedule(dynamic, 1)
        #pragma omp for schedule(static)
        for(int i=1; i<n; i++){
            dummyfunc(i, scale);
        }
        // #pragma omp for schedule(static, 1)
        // #pragma omp for schedule(dynamic, 1)
        #pragma omp for schedule(static)
        for(int i=1; i<n; i++){
            dummyfunc(n-i, scale);
        }
    }
    double tend = omp_get_wtime();
    printf("time: %f\n", tend-tstart);
    return 0;
}