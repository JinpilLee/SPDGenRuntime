// XXX FPGA class should be included

#include "internal.h"

#ifdef DEBUG_ON_CPU
#include <string.h>
#else
extern fpga_DE5NET *FPGADev;
#endif

extern "C" {
void __spd_pci_dma_to_FPGA(float *to_fpga_addr, ull_t to_size);
void __spd_pci_dma_from_FPGA(float *from_fpga_addr, ull_t from_size, ui_t switch_inout);
}

void __spd_pci_dma_to_FPGA(float *to_fpga_addr, ull_t to_size) {
#ifdef DEBUG_ON_CPU
  memcpy((void *)fpga_src_addr, (void *)to_fpga_addr, sizeof(float) * to_size);
#else
  FPGADev->pci_dma__to_FPGA_single(fpga_src_addr, (ui_t *)to_fpga_addr, to_size);
  FPGADev->pci_dma__to_FPGA_single_waitFin();
#endif

  return;
}

void __spd_pci_dma_from_FPGA(float *from_fpga_addr, ull_t from_size, ui_t switch_inout) {
  addr_t addr;
  if (switch_inout == 1) {
    addr = fpga_src_addr;
  }
  else {
    addr = fpga_dst_addr;
  }

#ifdef DEBUG_ON_CPU
  memcpy((void *)from_fpga_addr, (void *)addr, sizeof(float) * from_size);
#else
  FPGADev->pci_dma_fromFPGA_single(addr, (ui_t *)from_fpga_addr, from_size);
  FPGADev->pci_dma_fromFPGA_single_waitFin();
#endif
}
