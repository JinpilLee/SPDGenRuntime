// XXX FPGA class should be included

#ifndef DEBUG_ON_CPU
#include <unistd.h>
#include <iostream>
#endif

#include "internal.h"

#ifndef DEBUG_ON_CPU
extern fpga_DE5NET *FPGADev;
#endif

extern "C" {
void __spd_run_kernel(ull_t dma_size, ui_t switch_inout);
}

// FIXME temporary
// - requires kernel identifier
// - fpga device initialization/finalization should be done separately
// - precise synchonization required
void __spd_run_kernel(ull_t dma_size, ui_t switch_inout) {
#ifdef DEBUG_ON_CPU
  float *out = fpga_dst_addr;
  float *in = fpga_src_addr;
  for (ull_t i = 0; i < dma_size; i+=2) {
// XXX cala on FPGA
    int mask = *((int *)(in + i + 1));
    if (mask == 0) {
      out[i] = in[i];
    }
    else {
      out[i] = in[i] * 0.99;
    }
    out[i+1] = in[i+1];
  }
#else
  if (!fpga.stream_dma(fpga_src_addr, fpga_dst_addr, dma_size)) {
    std::cerr << "stream_dma() failed\n";
  }

// FIXME wait time should be changed manually
  usleep(100000); // 0.1 sec
  FPGADev->stream_data_dma_waitFin(250000000); // 1 sec on 250MHz?
#endif

  if (switch_inout == 1) {
    addr_t temp = fpga_src_addr;
    fpga_src_addr = fpga_dst_addr;
    fpga_dst_addr = temp;
  }
}
