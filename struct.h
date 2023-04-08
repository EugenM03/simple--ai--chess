#pragma once

#include <stdbool.h>
#include <inttypes.h>

typedef struct piece {
  char color;  // piece's color
  char type;   // piece's type

  // Pointer to a function that checks if the piece can move to the given
  // position and returns TRUE if it can. Otherwise, returns FALSE
  bool (*move)(struct piece ***, uint8_t[2], uint8_t[2]);
} piece;
