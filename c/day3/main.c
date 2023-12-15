// Advent of Code - Day 3
//
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t x;
    size_t y;
} point;

void getMapSize(size_t *, size_t *, FILE *);
int getNextNumInLine(char *, size_t, size_t, size_t *);
size_t digitLength(size_t);

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

int getNextNumInLine(char *line, size_t current, size_t length, size_t *num) {
    
    // Scans through line starting at current, returns pos of
    // next number
    //
    // Params:
    //  char *line: Array of characters
    //  size_t current: Position in line to start search
    //  size_t length: Length of line
    //  size_t *num: Value of number found
    //
    // Returns:
    //  int: index of returned, -1 for no result

    size_t i = current;
    char c;                 // Single char for comparisions
    char numStr[4];         // Storage for found num values
    size_t nsp = 0;         // numStr pointer

    // Skip non-numbers
    while ((c = line[i++]) < '0' || c > '9' && i < length) {
        ;
    }

    if (c >= '0' && c <= '9') {
        numStr[nsp++] = c;
        while ((c = line[i++]) >= '0' && c <= '9') {
            numStr[nsp++] = c;
        }
        numStr[nsp] = '\0';
    }
    else {
        return -1;
    }

    *num = atoi(numStr);

    return i;

}

size_t digitLength(size_t num) {

    // Returns the number of digits in num
    //
    // Params:
    //  size_t num: Number to get length of
    //
    // Returns:
    //  size_t: Number of digits in num
   
    if (num == 0) {
        return 1;
    }

    size_t l = 1;   // Counter for length of num
    size_t n = num;       // to mutate num

    while ((n = (n / 10)) > 0) {
        l++;
    }

    return l;

}

int main(void) {

    FILE *f = fopen("../../inputs/day3/sample.txt", "r");
    size_t x;           // Width of map
    size_t xi;          // x index for map array
    size_t y;           // Height of map (should match width);
    size_t yi;          // y index for map array
    char **map;         // Array to represent map
    char* lineBuf;      // Buffer for map lines
    size_t lSize;       // Length of lineBuf (x + 1)
    size_t chars;       // Return value of getline
    size_t nextNum;     // To store num values from map
    point currentPoint; // Current point being worked

    getMapSize(&x, &y, f);

    // Allocate rows
    map = (char**)malloc(y * sizeof(char*));
    // Allocate cells in each row
    for (int i = 0; i < x; i++) {
        map[i] = (char*)malloc(x * sizeof(char*));
    }

    // Setup for getline
    lSize = x + 1;    
    lineBuf = (char *)malloc(sizeof(char) * lSize);

    // Load map
    while ((chars = getline(&lineBuf, &lSize, f)) != -1) {
        xi = 0;
        while (lineBuf[xi] != '\0') {
            map[yi][xi] = lineBuf[xi];
            xi++;
        } 
        yi++;
    }    
    
    free(lineBuf);

    yi = 0;
    while (yi < y) {
        xi = 0;
        
        while ((xi = getNextNumInLine(map[yi], xi, x, &nextNum)) != -1) {
            currentPoint.x = xi - 2;
            currentPoint.y = yi;

            printf("(%zu, %zu): %zu, %zu\n", currentPoint.x, currentPoint.y, nextNum, digitLength(nextNum)); 
        }

        yi++;

    } 

    return EXIT_SUCCESS;
}
