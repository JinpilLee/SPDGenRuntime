// XXX FPGA class should be included

#include "internal.h"

ui_t fpga_src_addr;
ui_t fpga_dst_addr;

#ifdef FPGA_SDK
static fpgas_t<fpga_DE5NET> *FPGADevices;
fpga_DE5NET *FPGADev;
#endif

extern "C" {
void __spd_initialize(void);
void __spd_finalize(void);
}

void __spd_initialize(void) {
#ifdef FPGA_SDK
  FPGADevices = new fpgas_t<fpga_DE5NET>(1);
  FPGADevices->setBoardsInfo(0, 1);
  FPGADevices->open(0);
  FPGADev = &((*FPGADevices)[0]);
#endif

  fpga_src_addr = __SPD_SRC_ADDR;
  fpga_dst_addr = __SPD_DST_ADDR;
}

void __spd_finalize(void) {
#ifdef FPGA_SDK
  FPGADevices->close(0);
#endif
  return;
}
