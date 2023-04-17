// parallel scan
// finish in one combined parallel region
// bottleneck can be the explicit barrier for thread synchronization
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <omp.h>

// Scan A array and write result into prefix_sum array;
// use long data type to avoid overflow
void scan_seq(long* prefix_sum, const long* A, long n) {
  if (n == 0) return;
  prefix_sum[0] = A[0];
  for (long i = 1; i < n; i++) {
    prefix_sum[i] = prefix_sum[i-1] + A[i];
  }
}

void scan_omp(long* prefix_sum, const long* A, long n, int num_threads){
  int p = num_threads; // predefined omp threads number
  // int t = omp_get_thread_num();
  // Fill out parallel scan: One way to do this is array into p chunks
  // Do a scan in parallel on each chunk, then share/compute the offset
  // through a shared vector and update each chunk by adding the offset
  // in parallel
  long* offset = (long*) malloc(p * sizeof(long));
  offset[0] = 0;
  #pragma omp parallel shared(offset) num_threads(p)
  {
    int t = omp_get_thread_num();
    long start = t * n / p;
    long end = (t+1) * n / p;
    // long partialsum = A[start];
    prefix_sum[start] = A[start];
    for(long i = start+1; i<end; i++){
      prefix_sum[i] = prefix_sum[i-1] + A[i];
    }
    offset[t] = prefix_sum[end-1];
    #pragma omp barrier
    // get correction in serial
    // #pragma omp single
    // {
    //   for(int j=1; j<p; j++){
    //     offset[j] = offset[j] + offset[j-1];
    //   }
    // }
    // correct the partial sum in parallel again
    // pay attention to the mismatch
    // #pragma omp parallel num_threads(p)
    // int t = omp_get_thread_num();
    // long start = t * n / p;
    // long end = (t+1) * n / p;
    long correction = 0;
    for(int ti=0; ti<t; ti++){
      correction += offset[ti];
    }
    for(long i=start; i<end; i++){
        prefix_sum[i] += correction;
    }
  }
  free(offset);
}

int main(int argc, char** argv) {
  long N = 100000000;
  int num_threads = atoi(argv[1]);
  long* A = (long*) malloc(N * sizeof(long));
  long* B0 = (long*) malloc(N * sizeof(long));
  long* B1 = (long*) malloc(N * sizeof(long));
  for (long i = 0; i < N; i++) A[i] = rand();
  for (long i = 0; i < N; i++) B1[i] = 0;
  
//   double tt = omp_get_wtime();
//   scan_seq(B0, A, N);
//   printf("sequential-scan = %fs\n", omp_get_wtime() - tt);

  // better report for different number of threads
//   int max_num_threads = 16;
//   for (int i=1; i<=max_num_threads; i = i*2){
//     tt = omp_get_wtime();
//     scan_omp(B1, A, N, i);
//     printf("run with %d threads\t", i);
//     printf("parallel-scan   = %fs\t", omp_get_wtime() - tt);
//     long err = 0;
//     for (long i = 0; i < N; i++) err = std::max(err, std::abs(B0[i] - B1[i]));
//     printf("error = %ld\n", err);
//   }
  double tt = omp_get_wtime();
  scan_omp(B1, A, N, num_threads);
  printf("parallel-scan   = %fs\n", omp_get_wtime() - tt);

  // long err = 0;
  // for (long i = 0; i < N; i++) err = std::max(err, std::abs(B0[i] - B1[i]));
  // printf("error = %ld\n", err);

  free(A);
  free(B0);
  free(B1);
  return 0;
}
