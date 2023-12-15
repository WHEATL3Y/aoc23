// Advent of Code - Day 3
//
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>

void getMapSize(size_t *, size_t *, FILE *);

void getMapSize(size_t *x, size_t *y, FILE *map) {

    // Gets the x and y length of the input string
    //
    // Params:
    //  size_t *x: Width value
    //  size_t *y: Height value
    //  char *map: Input map
    //
    // Returns:
    //  None
    //  Values to be stored in x, y

    *x = 0;
    *y = 1;

    char c;

    // Get x (width)
    while ((c = getc(map)) != '\n') {
        *x += 1;
    }

    // Get y (height)
    while ((c= getc(map)) != EOF) {
        if (c == '\n') {
            *y += 1;
        }
    }

    // Return file position to beginning
    fseek(map, 0, SEEK_SET);
}

int main(void) {

    FILE *f = fopen("../../inputs/day3/sample.txt", "r");
    size_t x;
    size_t y;

    getMapSize(&x, &y, f);
    printf("%zu, %zu\n", x, y);

    return EXIT_SUCCESS;
}
