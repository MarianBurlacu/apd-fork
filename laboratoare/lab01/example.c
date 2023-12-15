#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2

void *f0(void *arg) {
  long id = *(long *)arg;
  printf("Hello World din thread-ul %ld!\n", id);
  pthread_exit(NULL);
}

void *f1(void *arg) {
  long id = *(long *)arg;
  printf("Bye World din thread-ul %ld!\n", id);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS];
  int r;
  long id;
  void *status;
  long ids[NUM_THREADS];

  void *(*function)();

  for (long id = 0; id < NUM_THREADS; id++) {
    if (id == 0) {
      function = &f0;
    } else {
      function = &f1;
    }

    ids[id] = id;

    r = pthread_create(&threads[id], NULL, function, &ids[id]);
    if (r) {
      printf("Eroare la crearea thread-ului %ld.\n", ids[id]);
      exit(-1);
    }
  }

  for (id = 0; id < NUM_THREADS; id++) {
    r = pthread_join(threads[id], &status);

    if (r) {
      printf("Eroare la asteptarea thread-ului %ld\n", id);
      exit(-1);
    }
  }

  return 0;
}
