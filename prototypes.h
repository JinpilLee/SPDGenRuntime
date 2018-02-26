// this file is not used in the runtime library
// just for documentation

#include "internal.h"

// runtime.cpp
extern void
__spd_initialize(void);
extern void
__spd_finalize(void);

// stream.c
extern float *
__spd_alloc_stream(ull_t size);
extern void
__spd_free_stream(float *ptr);

// pack.c
extern void
__spd_pack_contiguous(float *dst, int offset, int diff,
                      float *src, ull_t size);
extern void
__spd_unpack_contiguous(float *dst, ull_t size,
                        float *src, int offset, int diff);

// domain.c
extern void
__spd_create_domain_1(float *stream, int diff,
                      ull_t dim0_lower, ull_t dim0_upper, ull_t dim0_size);
extern void
__spd_create_domain_2(float *stream, int diff,
                      ull_t dim0_lower, ull_t dim0_upper, ull_t dim0_size,
                      ull_t dim1_lower, ull_t dim1_upper, ull_t dim1_size);

// pci_dma.cpp
extern void
__spd_pci_dma_to_FPGA(float *to_fpga_addr, ull_t to_size);

extern void
__spd_pci_dma_from_FPGA(float *from_fpga_addr, ull_t from_size, int switch_inout);

// kernel.cpp
extern void
__spd_run_kernel(ull_t dma_size, int switch_inout);
