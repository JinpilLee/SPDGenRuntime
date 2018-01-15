#include "header.h"

void calc(void) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      float temp_a = a[i][j];
      float temp_b = b[i][j];
      float sub = (temp_a - temp_b);
      temp_a = temp_a - sub;
      temp_b = temp_b - sub;
      c[i][j] = sub;
      d[i][j] = (temp_a * temp_a) + (temp_b * temp_b);
    }
  }
}
