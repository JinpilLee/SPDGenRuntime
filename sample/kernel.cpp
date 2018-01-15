// XXX FPGA class should be included

#include <unistd.h>
#include <iostream>
#include "../internal.h"

#define __SPD_ADDR_SRC (0x00000000)
#define __SPD_ADDR_DST (0x80000000)

extern "C" {
void __spd_run_kernel(float *to_fpga_addr, ull_t to_size,
                      float *from_fpga_addr, ull_t from_size);
}

// FIXME temporary
// - requires kernel identifier
// - fpga device initialization/finalization should be done separately
// - precise synchonization required
#if 1
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

  usleep(100000); // 0.1 sec
  FPGADev.stream_data_dma_waitFin(250000000); // 1 sec on 250MHz?

  FPGADev.pci_dma_fromFPGA_single(__SPD_ADDR_DST, (ui_t *)from_fpga_addr, from_size);
  FPGADev.pci_dma_fromFPGA_single_waitFin();

  FPGADevices.close(0);
}
#else
void __spd_run_kernel(float *to_fpga_addr, ull_t to_size,
                      float *from_fpga_addr, ull_t from_size) {
  for (ull_t i = 0; i < (to_size / 2); i++) {
    float a = to_fpga_addr[2*i];
    float b = to_fpga_addr[2*i+1];

    float sub = a - b;
    a = a - sub;
    b = b - sub;

    from_fpga_addr[2*i] = sub;
    from_fpga_addr[2*i+1] = (a * a) + (b * b);
  }
}
#endif
