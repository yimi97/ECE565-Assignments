#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#define CACHE_SIZE 32768
// #define CACHE_SIZE 32768/2 almost the same b/w
#define TRAVERSALS 10000
int *array;

double calc_time(struct timespec start, struct timespec end) {
  double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec;
  double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec;

  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
}

void init_array(size_t array_size) {
    int i;
    for (i=0; i<array_size; i++){
        array[i] = i;
    }
}

int main(int argc, char *argv[]) {
    int i;
    int temp;
    int temp2;
    struct timespec start_time, end_time;
    double elapsed_ns;
    size_t array_size = CACHE_SIZE / sizeof(int);
    array = (int*)malloc(CACHE_SIZE);
    init_array(array_size);
    printf("===== Only supplied by L1 cache =====\n");
    //
    printf("Write traffic only\n");
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (i = 0; i< array_size*TRAVERSALS; i++) {
        array[i%array_size] = i+1;
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    elapsed_ns = calc_time(start_time, end_time);
    printf("Time = %f ns\n", elapsed_ns);
    printf("Bandwidth = %f GB/s\n", ((double)CACHE_SIZE*TRAVERSALS / elapsed_ns));

    //
    printf("1:1 read-to-write ratio\n");
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (i = 0; i< array_size*TRAVERSALS; i++) {
        // array[i%array_size] += 1;
        // array[i%array_size] = array[array_size - i%array_size - 1];
        temp = array[array_size - i%array_size - 1];
        array[i%array_size] = i + 1;
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    elapsed_ns = calc_time(start_time, end_time);
    printf("Time = %f ns\n", elapsed_ns);
    printf("Bandwidth = %f GB/s\n", ((double)CACHE_SIZE*TRAVERSALS*2 / elapsed_ns));
    
    //
    printf("2:1 read-to-write ratio\n");
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (i = 0; i< array_size*TRAVERSALS; i++) {
        // array[i%array_size] += array[array_size - i%array_size - 1];
        temp = array[i%array_size] + array[array_size - i%array_size - 1];
        array[i%array_size] = i + 1;
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    elapsed_ns = calc_time(start_time, end_time);
    printf("Time = %f ns\n", elapsed_ns);
    printf("Bandwidth = %f GB/s\n", ((double)CACHE_SIZE*TRAVERSALS*3 / elapsed_ns));
}