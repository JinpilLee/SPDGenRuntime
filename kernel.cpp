#include <iostream>
#include "internal.h"

#define __SPD_ADDR_SRC 
#define __SPD_ADDR_DST 

extern "C" {
void __spd_run_kernel(float *to_fpga_addr, ull_t to_size,
                      float *from_fpga_addr, ull_t from_size);
}

// FIXME temporary
// - requires kernel identifier
// - fpga device initialization/finalization should be done separately
// - precise synchonization required
void __spd_run_kernel(float *to_fpga_addr, ull_t to_size,
                      float *from_fpga_addr, ull_t from_size) {
  fpgas_t<fpga_DE5NET> FPGADevices(1);
  FPGADevices.setBoardsInfo(0, 1);
  FPGADevices.open(0);
  fpga_DE5NET FPGADev = FPGADevices[0];

  FPGADev.pci_dma__to_FPGA_single(__SPD_ADDR_SRC, (ui_t *)to_fpga_addr, to_size);
  FPGADev.pci_dma__to_FPGA_single_waitFin();

// FIXME assumes that to_size == from_size
  if (!fpga.stream_dma(__SPD_ADDR_SRC, __SPD_ADDR_DST, to_size)) {
    std::cerr << "stream_dma() failed\n";
  }

  usleep(???); // wait usec
  FPGADev.stream_data_dma_waitFin(???); // abortCycle

  FPGADev.pci_dma_fromFPGA_single(__SPD_ADDR_DST, (ui_t *)from_fpga_addr, from_size);
  FPGADev.pci_dma_fromFPGA_single_waitFin();

  FPGADevices.close(0);
}
