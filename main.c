#include <stdio.h>
#include <stdlib.h>


#include "struct.h"

int main(void) {
  // Allocate memory for the chess table
  piece ***table = calloc(8, sizeof(piece **));
  for (int i = 0; i < 8; i++) {
    table[i] = calloc(8, sizeof(piece *));

    if (i == 0 || i == 1 || i == 6 || i == 7)
      for (int j = 0; j < 8; j++) table[i][j] = calloc(1, sizeof(piece));
  }
  // d4-e4
  // 8
  // 7
  // 6
  // 5
  // 4
  // 3
  // 2
  // 1 a b c d e f g h
  printf("qweiqwjeioquoiqweoquqw1\n");
  printf("qweiqwjeioquoiqweoquqw2\n");
  printf("qweiqwjeioquoiqweoquqw3\n");
  printf("qweiqwjeioquoiqweoquqw4\n");
  printf("qweiqwjeioquoiqweoquqw5\n");
  printf("qweiqwjeioquoiqweoquqw6\n");
  printf("qweiqwjeioquoiqweoquqw7\n");
  printf("qweiqwjeioquoiqweoquqw8\n");
  printf("qweiqwjeioquoiqweoquqw9\n");
  printf("qweiqwjeioquoiqweoquqw10\n");
  printf("qweiqwjeioquoiqweoquqw11\n");
  printf("qweiqwjeioquoiqweoquqw12\n");
  printf("qweiqwjeioquoiqweoquqw13\n");
  printf("qweiqwjeioquoiqweoquqw14\n");
  printf("qweiqwjeioquoiqweoquqw15\n");
  printf("qweiqwjeioquoiqweoquqw16\n");
  printf("qweiqwjeioquoiqweoquqw17\n");
  printf("qweiqwjeioquoiqweoquqw18\n");
  printf("qweiqwjeioquoiqweoquqw19\n");
  printf("qweiqwjeioquoiqweoquqw20\n");
  printf("qweiqwjeioquoiqweoquqw21\n");
  int d;
  scanf("%d", &d);
  if (d == 1) printf("\033[10;H\033[J");
  return 0;
}