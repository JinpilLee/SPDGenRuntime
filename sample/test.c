#include "header.h"

void calc(void) {
/*
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      float ta = a[i][j];
      float tb = b[i][j];
      c[i][j] = ta + tb;
      d[i][j] = c[i][j] * c[i][j];
    }
  }
*/

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      float tc = c[i][j];
//      float td = d[i][j];
      a[i][j] = tc;
    }
  }
}
