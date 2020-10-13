#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

#define N 1024
struct timespec start_time, end_time;
double A[N][N];
double B[N][N];
double C[N][N];

double calc_time(struct timespec start, struct timespec end) {
    double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec;
    double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec;

    if (end_sec < start_sec) {
        return 0;
    } else {
        return end_sec - start_sec;
    }
}

int main(int argc, char * argv[]) {

    time_t t;
    srand((unsigned) time(&t));
    int i, j, k;
    double elapsed_ns;
    double sum;
    double tmp;
    int nest = atoi(argv[1]);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = rand()%10;
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            B[i][j] = rand()%10;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    if (nest == 1) {
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++) {
                sum = 0;
                for (k=0; k<N; k++) {
                    sum += A[i][k] * B[k][j];
                }
                C[i][j] = sum;
            }
        } 
    } else if (nest==2) {
        for (j=0; j<N; j++) {
            for (k=0; k<N; k++) {
                tmp = B[k][j];
                for (i=0; i<N; i++) {
                    C[i][j] += tmp * A[i][k];
                }
            }
        } 
    } else if (nest==3){
        for (i=0; i<N; i++) {
            for (k=0; k<N; k++) {
                tmp = A[i][k];
                for (j=0; j<N; j++) {
                    C[i][j] += tmp * B[k][j];
                }
            }
        } 
    } 
    else {
        exit(EXIT_FAILURE);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    elapsed_ns = calc_time(start_time, end_time);
    printf("Time = %f s\n", elapsed_ns/1000000000);

    return 0;
}

