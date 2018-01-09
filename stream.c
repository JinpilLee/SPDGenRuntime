#include <stdlib.h>
#include "internal.h"

float *__spd_alloc_stream(ull_t size) {
  float *ret = (float *)malloc(size * sizeof(float));

// FIXME for test
  for (ull_t i = 0; i < size; i++) {
    ret[i] = (float)i;
  }

  return ret;
}

void __spd_free_stream(float *ptr) {
  free((void *)ptr);
}
