#include "internal.h"

// kernel.c
extern void
__spd_run_kernel(int kernel_num);

// pack.c
extern void
__spd_pack_contiguous(float *dst, int offset, int diff,
                      float *src, ull_t size);
extern void
__spd_unpack_contiguous(float *dst, ull_t size,
                        float *src, int offset, int diff);

// stream.c
extern float *
__spd_alloc_stream(ull_t size);
extern void
__spd_free_stream(float *ptr);
