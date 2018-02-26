// XXX FPGA class should be included

#include "internal.h"

#ifdef FPGA_SDK
extern fpga_DE5NET *FPGADev;
#endif

extern "C" {
void __spd_pci_dma_to_FPGA(float *to_fpga_addr, ull_t to_size);
void __spd_pci_dma_from_FPGA(float *from_fpga_addr, ull_t from_size, int switch_inout);
}

void __spd_pci_dma_to_FPGA(float *to_fpga_addr, ull_t to_size) {
#ifdef FPGA_SDK
  FPGADev->pci_dma__to_FPGA_single(fpga_src_addr, (ui_t *)to_fpga_addr, to_size);
  FPGADev->pci_dma__to_FPGA_single_waitFin();
#endif
  return;
}

void __spd_pci_dma_from_FPGA(float *from_fpga_addr, ull_t from_size, int switch_inout) {
  addr_t addr;
  if (switch_inout == 1) {
    addr = fpga_src_addr;
  }
  else {
    addr = fpga_dst_addr;
  }

#ifdef FPGA_SDK
  FPGADev->pci_dma_fromFPGA_single(addr, (ui_t *)from_fpga_addr, from_size);
  FPGADev->pci_dma_fromFPGA_single_waitFin();
#endif
}
