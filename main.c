#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

int main(void)
{
    // Allocate memory for the chess table
    piece ***table = calloc(8, sizeof(piece **));
    for (int i = 0; i < 8 ; i++) {
        table[i] = calloc(8, sizeof(piece *));

        if (i == 0 || i == 1 || i == 6 || i == 7)
            for (int j = 0; j < 8; j++)
                table[i][j] = calloc(1 , sizeof(piece));
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

    return 0;
}