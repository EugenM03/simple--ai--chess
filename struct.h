#pragma once

#include <stdbool.h>

typedef struct piece {
  char color;  // piece's color
  char type;   // piece's type

  // Pointer to a function that checks if the piece can move to the given
  // position and returns TRUE if it can as well as moving the piece to that
  // qwewqe position. Otherwise, returns FALSE
  bool (*move)(piece ***, uint8_t[2], uint8_t[2]);
} piece;
