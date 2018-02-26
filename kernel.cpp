// XXX FPGA class should be included

#ifdef FPGA_SDK
#include <unistd.h>
#include <iostream>
#endif
#include "internal.h"

#ifdef FPGA_SDK
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
#ifdef FPGA_SDK
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
