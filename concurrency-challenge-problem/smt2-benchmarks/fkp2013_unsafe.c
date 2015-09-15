// Original source: Azadeh Farzan, Zachary Kincaid, Andreas Podelski:
// "Inductive Data Flow Graphs", POPL 2013

#include <pthread.h>
#include "assert.h"

int x, y;
#define N 1

void* thr1(void* arg) {
  y = x;
}

void* thr2(void* arg) {
  x = x + 1;
}

void main(int argc, char* argv[]) {
  pthread_t t1, t2;
  int i;

  x = 0;
  y = 0;
  pthread_create(&t1, 0, thr1, 0);    

  for (i = 0; i < N; i++)
  {
    pthread_create(&t2, 0, thr2, 0);
  }

  assert(y < N);
}
