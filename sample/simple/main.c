#include <stdio.h>
#include "header.h"

// input
float a[M][N];
float b[M][N];

// output for FPGA
float c[M][N];
float d[M][N];

// output for CPU
float c_cpu[M][N];
float d_cpu[M][N];

int main(void) {
// init
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      float fi = (float)i;
      float fj = (float)j;
      a[i][j] = fj + (float)N * fi;
      b[i][j] = fi * fj;
      c[i][j] = 0.0;
      d[i][j] = 0.0;
    }
  }

// calc on FPGA: c[], d[]
  calc();

// calc on CPU: c_cpu[], d_cpu[]
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      float temp_a = a[i][j];
      float temp_b = b[i][j];
      float sub = (temp_a - temp_b);
      temp_a = temp_a - sub;
      temp_b = temp_b - sub;
      c_cpu[i][j] = sub;
      d_cpu[i][j] = (temp_a * temp_a) + (temp_b * temp_b);
    }
  }

// verification
  float c_sum = 0.0;
  float d_sum = 0.0;
  float c_diff_max = 0.0;
  float d_diff_max = 0.0;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      float c_diff = c[i][j] - c_cpu[i][j];
      if (c_diff > c_diff_max) c_diff_max = c_diff;
      c_sum += c_diff;

      float d_diff = d_sum += d[i][j] - d_cpu[i][j];
      if (d_diff > d_diff_max) d_diff_max = d_diff;
      d_sum += d_diff;
    }
  }

  printf("c_sum = %f | c_diff_max = %f\n", c_sum, c_diff_max);
  printf("d_sum = %f | d_diff_max = %f\n", d_sum, d_diff_max);

  return 0;
}
