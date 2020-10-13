#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void do_loop(int *a, int *b, int seed, int num_items)
{
  for (int i=0; i < num_items; i++) {
    b[i] = a[i] + seed;
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
