// XXX FPGA class should be included

#include "internal.h"

addr_t fpga_src_addr;
addr_t fpga_dst_addr;

#ifdef DEBUG_ON_CPU
#include <iostream>
#include <stdlib.h>
#else
static fpgas_t<fpga_DE5NET> *FPGADevices;
fpga_DE5NET *FPGADev;
#endif

extern "C" {
void __spd_initialize(void);
void __spd_finalize(void);
}

void __spd_initialize(void) {
#ifdef DEBUG_ON_CPU
  std::cout << "[DBG] SPD runtime initialized\n";
#else
  FPGADevices = new fpgas_t<fpga_DE5NET>(1);
  FPGADevices->setBoardsInfo(0, 1);
  FPGADevices->open(0);
  FPGADev = &((*FPGADevices)[0]);
#endif

#ifdef DEBUG_ON_CPU
  fpga_src_addr = (float *)malloc(sizeof(float) * 1024 * 1024);
  fpga_dst_addr = (float *)malloc(sizeof(float) * 1024 * 1024);
#else
  fpga_src_addr = __SPD_SRC_ADDR;
  fpga_dst_addr = __SPD_DST_ADDR;
#endif
}

void __spd_finalize(void) {
#ifdef DEBUG_ON_CPU
  free((void *)fpga_src_addr);
  free((void *)fpga_dst_addr);
  std::cout << "[DBG] SPD runtime finalized\n";
#else
  FPGADevices->close(0);
#endif
}
