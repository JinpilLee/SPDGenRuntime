#include "internal.h"

void __spd_pack_contiguous(float *dst, int offset, int diff,
                           float *src, ull_t size) {
  dst += offset;
  for (ull_t i = 0; i < size; i++) {
    *dst = src[i];
    dst += diff;
  }
}

void __spd_unpack_contiguous(float *dst, ull_t size,
                             float *src, int offset, int diff) {
  src += offset;
  for (ull_t i = 0; i < size; i++) {
    dst[i] = *src;
    src += diff;
  }
}
