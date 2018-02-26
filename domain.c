#include "internal.h"

// XXX assumptions
// attr is always the last element in the stream
// stride is 1

// XXX assumption: dim0_size == number of attrs in stream
void __spd_create_domain_1(float *stream, int diff,
                           ull_t dim0_lower, ull_t dim0_upper, ull_t dim0_size) {
  int *attr = (int *)stream;
  attr += (diff - 1);
  for (ull_t i = 0; i < dim0_size; i++) {
    if ((i >= dim0_lower) && (i <= dim0_upper)) {
      *attr = 1;
    }
    else {
      *attr = 0;
    }

    attr += diff;
  }
}

// XXX assumption: dim0_size * dim1_size == number of attrs in stream
void __spd_create_domain_2(float *stream, int diff,
                           ull_t dim0_lower, ull_t dim0_upper, ull_t dim0_size,
                           ull_t dim1_lower, ull_t dim1_upper, ull_t dim1_size) {
  int *attr = (int *)stream;
  attr += (diff - 1);
  for (ull_t j = 0; j < dim1_size; j++) {
    for (ull_t i = 0; i < dim0_size; i++) {
      if ((j >= dim1_lower) && (j <= dim1_upper) &&
          (i >= dim0_lower) && (i <= dim0_upper)) {
        *attr = 1;
      }
      else {
        *attr = 0;
      }

      attr += diff;
    }
  }
}
