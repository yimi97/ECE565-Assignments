#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#define CACHE_SIZE 51904512
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
    struct timespec start_time, end_time;
    size_t array_size = CACHE_SIZE / sizeof(int);
    array = (int*)malloc(CACHE_SIZE);
    init_array(array_size);
    printf("===== Large size array =====\n");
    //
    printf("write traffic only\n");
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (i = 0; i< array_size; i++) {
        array[i%array_size] = i+1;
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_ns = calc_time(start_time, end_time);
    printf("Time = %f\n", elapsed_ns);
    printf("Bandwidth = %f GB/s \n", (CACHE_SIZE / elapsed_ns));

    //
    printf("1:1 read-to-write ratio\n");
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (i = 0; i< array_size; i++) {
        // array[i%array_size] = array[array_size - i%array_size - 1];
        temp = array[array_size - i%array_size - 1];
        array[i%array_size] = i + 1;
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    elapsed_ns = calc_time(start_time, end_time);
    printf("Time = %f\n", elapsed_ns);
    printf("Bandwidth = %f GB/s \n", (CACHE_SIZE / elapsed_ns));
    
    //
    printf("2:1 read-to-write ratio\n");
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (i = 0; i< array_size; i++) {
        // array[i%array_size] = array[i%array_size] + array[array_size - i%array_size - 1];
        temp = array[i%array_size] + array[array_size - i%array_size - 1];
        array[i%array_size] = i + 1;
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    elapsed_ns = calc_time(start_time, end_time);
    printf("Time = %f ns\n", elapsed_ns);
    printf("Bandwidth = %f GB/s \n", (CACHE_SIZE / elapsed_ns));

}