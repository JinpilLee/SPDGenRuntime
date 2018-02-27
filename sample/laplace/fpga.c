#include "spd_pragma.h"
#include "header.h"
#define VL 1
#define UC 1

extern float src[M][N];
extern float dst[M][N];

inline static
void laplace_fpga(void) {
  for (int i = 1; i < M-1; i++) {
    __spd_loop(0, VL, UC, true);
    for (int j = 1; j < N-1; j++) {
      dst[i][j]
        = (src[i][j-1]
        +  src[i][j+1]
        +  src[i-1][j]
        +  src[i+1][j]) * 0.25;
    }
  }
}

void calc_on_fpga(void) {
  __spd_begin(0);
  for (int t = 0; t < (ITER/UC); t++) {
    laplace_fpga();
  }
  __spd_end(0);
}
