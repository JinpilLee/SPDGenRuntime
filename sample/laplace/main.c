#include <stdio.h>
#include <math.h>
#include "header.h"

float src[M][N];
float dst[M][N];

float src_cpu[M][N];
float dst_cpu[M][N];

extern void init_data(void);
extern void laplace_cpu(void);
extern void verify_result(void);

int main(void) {
  init_data();
  calc_on_fpga();
  verify_result();

  return 0;
}

void init_data(void) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      src[i][j] = sinf(i * N + j);
      dst[i][j] = 0.0;

      src_cpu[i][j] = src[i][j];
      dst_cpu[i][j] = dst[i][j];
    }
  }
}

void laplace_cpu(void) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (i == 0 || i == M-1 || j == 0 || j == N-1) {
        dst_cpu[i][j] = src_cpu[i][j];
      }
      else {
        dst_cpu[i][j]
          = (src_cpu[i][j-1]
          +  src_cpu[i][j+1]
          +  src_cpu[i-1][j]
          +  src_cpu[i+1][j]) * 0.25;
      }
    }
  }

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      src_cpu[i][j] = dst_cpu[i][j];
    }
  }
}

void verify_result(void) {
  for (int t = 0; t < ITER; t++) {
    laplace_cpu();
  }

// XXX SPD returns data to dst
  float error = 0.0;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (src_cpu[i][j] != dst[i][j]) {
        printf("[%d][%d] %f | %f\n", i, j, src_cpu[i][j], dst[i][j]);
        error += fabsf(src_cpu[i][j] - dst[i][j]);
      }
    }
  }

  printf("error sum = %f\n", error);
}
