#include <stdlib.h>
#include "internal.h"

float *__spd_alloc_stream(ull_t size) {
  return (float *)malloc(size * sizeof(float));
}

void __spd_free_stream(float *ptr) {
  free((void *)ptr);
}
