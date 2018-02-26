#include <stdio.h>

#define M 32
#define N 16

#include "spd_pragma.h"
#define VL 5
#define UC 1

float src[M][N];
float dst[M][N];

float src_cpu[M][N];
float dst_cpu[M][N];

inline
void calc_on_fpga(void) {
  for (int i = 1; i < M-1; i++) {
    __spd_loop(0, VL, UC, true);
    for (int j = 1; j < N-1; j++) {
      dst[i][j] = src[i][j] * 0.5;
    }
  }
}

void calc_on_cpu(void) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (i == 0 || i == M-1 || j == 0 || j == N-1) {
        dst_cpu[i][j] = src_cpu[i][j];
      }
      else {
        dst_cpu[i][j] = src_cpu[i][j] * 0.99;
      }
    }
  }

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      src_cpu[i][j] = dst_cpu[i][j];
    }
  }
}

int main(void) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      src[i][j] = (i * N + j) + 0.128;
      dst[i][j] = 0.0;
      src_cpu[i][j] = src[i][j];
      dst_cpu[i][j] = dst[i][j] = 0.0;
    }
  }

  __spd_begin(0);
  for (int t = 0; t < (30/UC); t++) {
    calc_on_fpga();
    calc_on_cpu();
  }
  __spd_end(0);

// XXX SPD returns data to dst
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (src_cpu[i][j] == dst[i][j]) {
        printf("O ");
      }
      else {
        printf("X ");
      }
    }
    printf("\n");
  }

  return 0;
}

