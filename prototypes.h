#include "internal.h"

extern void
__spd_pack_contiguous(float *dst, int offset, int diff,
                      float *src, ull_t size);
extern void
__spd_unpack_contiguous(float *dst, ull_t size,
                        float *src, int offset, int diff);
