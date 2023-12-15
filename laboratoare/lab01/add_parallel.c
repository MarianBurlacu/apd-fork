#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    schelet pentru exercitiul 5
*/

int *arr;
int array_size;
int num_threads;

int min(int x, int y) {
  if (x < y) {
    return x;
  }

  return y;
}

void *add(void *arg) {
  int id = *(int *)arg;

  int start = id * (double)array_size / num_threads;
  int end = min((id + 1) * (double)array_size / num_threads, array_size);

  for (int i = start; i < end; i++) {
    for (int j = 0; j < 100000; j++) {
      arr[i] += 1;
    }
  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Specificati dimensiunea array-ului si numarul de thread-uri\n");
    exit(-1);
  }

  array_size = atoi(argv[1]);
  num_threads = atoi(argv[2]);

  arr = malloc(array_size * sizeof(int));
  for (int i = 0; i < array_size; i++) {
    arr[i] = i;
  }

  // for (int i = 0; i < array_size; i++) {
  //   printf("%d", arr[i]);
  //   if (i != array_size - 1) {
  //     printf(" ");
  //   } else {
  //     printf("\n");
  //   }
  // }

  // TODO: aceasta operatie va fi paralelizata cu num_threads fire de executie
  // for (int i = 0; i < array_size; i++) {
  //   arr[i] += 100;
  // }
  pthread_t threads[num_threads];
  int ids[num_threads];

  for (int i = 0; i < num_threads; i++) {
    ids[i] = i;

    int r = pthread_create(&threads[i], NULL, add, &ids[i]);
    if (r) {
      printf("Eroare la creare thread-ului %d!\n", i);
      exit(-1);
    }
  }

  for (int i = 0; i < num_threads; i++) {
    int r = pthread_join(threads[i], NULL);
    if (r) {
      printf("Eroare la asteptarea thread-ului %d!\n", i);
      exit(-1);
    }
  }

  for (int i = 0; i < array_size; i++) {
    printf("%d", arr[i]);
    if (i != array_size - 1) {
      printf(" ");
    } else {
      printf("\n");
    }
  }

  return 0;
}
