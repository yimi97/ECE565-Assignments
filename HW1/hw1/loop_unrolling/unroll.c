#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void do_loop(int *a, int *b, int seed, int num_items)
{
  for (int i=0; i < num_items; i=i+8) { //Assume num_items multiple of 8
    b[i] = a[i] + seed;
    b[i+1] = a[i+1] + seed;
    b[i+2] = a[i+2] + seed;
    b[i+3] = a[i+3] + seed;
    b[i+4] = a[i+4] + seed;
    b[i+5] = a[i+5] + seed;
    b[i+6] = a[i+6] + seed;
    b[i+7] = a[i+7] + seed;
  }
}

int main(int argc, char *argv[])
{
  if (argc < 3) {
    printf("Usage: ./loop <seed> <num_items>\n");
    return -1;
  }

  int seed      = atoi(argv[1]);
  int num_items = atoi(argv[2]);
  struct timeval start, end;

  int *a = (int*)malloc(num_items * sizeof(int));
  int *b = (int*)malloc(num_items * sizeof(int));
  for (int i=0; i < num_items; i++) {
    b[i] = 0;
    a[i] = i;
  }


  gettimeofday(&start, NULL);
  do_loop(a, b, seed, num_items);
  gettimeofday(&end, NULL);
  double elapsed = (double)((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));

  int result = 0;
  for (int i=0; i < num_items; i++) {
    result += b[i];
  }

  printf("result = %d\n", result);
  printf("time = %lf microseconds\n", elapsed);

  return 0;
}
