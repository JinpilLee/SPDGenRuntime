#include <stdio.h>
#include "header.h"

float a[M][N];
float b[M][N];
float c[M][N];
float d[M][N];

int main(void) {
  float fM = (float)M;
  float fN = (float)N;
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      float fi = (float)i;
      float fj = (float)j;
      a[i][j] = (fj + fN * fi) * 100.0;
      b[i][j] = (float)99.0;
      c[i][j] = fi;
      d[i][j] = fj;
    }
  }

  calc();

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      printf("[%d][%d] %4.4f\t%4.4f\t%4.4f\t%4.4f\n", i, j, a[i][j], b[i][j], c[i][j], d[i][j]);
    }
  }

  return 0;
}
