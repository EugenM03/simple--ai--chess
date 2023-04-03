# PCLP3 - Chess AI (Wannabe) Project

## Introduction

## Implementation

```C
typedef struct piece {
  char color;  // piece's color
  char type;   // piece's type

  // Pointer to a function that checks if the piece can move to the given
  // position and returns TRUE if it can as well as moving the piece to that
  // position. Otherwise, returns FALSE
  bool (*move)(piece ***, uint8_t[2], uint8_t[2]);
} piece;
```

## Alpha-Beta Prunning
