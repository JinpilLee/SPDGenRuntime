#ifndef __SPD_GEN_RUNTIME__
#define __SPD_GEN_RUNTIME__

//#define DEBUG_ON_CPU

typedef unsigned int ui_t;
typedef unsigned long long ull_t;

#ifdef DEBUG_ON_CPU
typedef float * addr_t;
#else
typedef unsigned int addr_t;
#endif

extern addr_t fpga_src_addr;
extern addr_t fpga_dst_addr;

#define __SPD_SRC_ADDR (0x00000000)
#define __SPD_DST_ADDR (0x80000000)

#endif // __SPD_GEN_RUNTIME__
