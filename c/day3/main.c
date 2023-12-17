// Advent of Code - Day 3
//
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>

size_t static xMax;
size_t static yMax;

size_t answer1 = 0;
size_t answer2 = 0;

typedef struct {
    size_t x;
    size_t y;
} point;

void getMapSize(size_t *, size_t *, FILE *);
int getNextNumInLine(char *, size_t, size_t, size_t *);
size_t digitLength(size_t);
size_t scanPoint(point, char **);
size_t isSymbol(char);

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
    u_short ff = 0;         // Found Flag

    for (i = current; i < length; i++) {
        // Skip non-numbers
        c = line[i];
        if (c < '0' || c > '9') {
            if (ff) {
                break;
            }
            continue;
        }

        if (c >= '0' && c <= '9') {
            ff = 1;
            numStr[nsp++] = c;
        }
    }

    if (ff) {
        numStr[nsp] = '\0';
        *num = atoi(numStr);
        return i + 1;
    }
    else {
        return -1;
    }
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

size_t scanPoint(point p, char **map) {

    // Looks at every values surrounding p in map
    // to determine if it's adjacent to a symbol
    //
    // Params:
    //  char *map: map of characters to search
    //  point p: x, y coords to scan around in map
    //
    // Returns:
    //  0 - p is not adjacent to a symbol
    //  1 - p is adjacent to a symbol
   
    return (
            (p.x != 0 && isSymbol(map[p.y][p.x - 1]))
         || (p.x != xMax - 1 && isSymbol(map[p.y][p.x + 1]))
         || (p.y != 0 && isSymbol(map[p.y - 1][p.x]))
         || (p.y != yMax - 1 && isSymbol(map[p.y + 1][p.x]))
         || (p.y != 0 && p.x != 0 && isSymbol(map[p.y - 1][p.x - 1]))
         || (p.y != 0 && p.x != xMax - 1 && isSymbol(map[p.y - 1][p.x + 1]))
         || (p.y != yMax - 1 && p.x != 0 && isSymbol(map[p.y + 1][p.x - 1]))
         || (p.y != yMax - 1 && p.x != xMax - 1 && isSymbol(map[p.y + 1][p.x + 1]))
       );
}

size_t isSymbol(char c) {
    
    // Checks whether c is a symobol (not 0-9 or .)
    // 
    // Params:
    //  char c: Character to check
    //
    // Returns:
    //  1 if c is not 0-9 or .
    //  0 if c is 0-9 or .
    
    return ((c < '0') || (c > '9')) && c != '.';

}

int main(void) {

    FILE *f = fopen("../../inputs/day3/input.txt", "r");
    size_t xi;          // x index for map array
    size_t yi;          // y index for map array
    char **map;         // Array to represent map
    char* lineBuf;      // Buffer for map lines
    size_t lSize;       // Length of lineBuf (x + 1)
    size_t chars;       // Return value of getline
    size_t nextNum;     // To store num values from map
    point currentStart; // First digit of current number
    point currentEnd;   // Last digit of current number

    getMapSize(&xMax, &yMax, f);

    // Allocate rows
    map = (char**)malloc(yMax * sizeof(char*));
    // Allocate cells in each row
    for (int i = 0; i < xMax; i++) {
        map[i] = (char*)malloc(xMax * sizeof(char*));
    }

    // Setup for getline
    lSize = xMax + 1;    
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
    while (yi < yMax) {
        xi = 0;
        
        while ((xi = getNextNumInLine(map[yi], xi, xMax, &nextNum)) != -1) {
            currentEnd.x = xi - 2;
            currentEnd.y = yi;
            currentStart.x = currentEnd.x - (digitLength(nextNum) - 1);
            currentStart.y = yi;
          
            if (scanPoint(currentStart, map) || scanPoint(currentEnd, map)) {
                printf("%zu\n", nextNum);
                printf("%zu, %zu\n", currentEnd.x, currentEnd.y);
                answer1 += nextNum; 
                continue;
            }

            /* printf("(%zu, %zu, %zu): %zu, %zu\n", */
            /*         currentEnd.y, */
            /*         currentStart.x, */
            /*         currentEnd.x, */
            /*         nextNum, */
            /*         digitLength(nextNum) */
            /* );  */
        }

        yi++;

    } 

    printf("%zu\n", answer1);

    return EXIT_SUCCESS;
}
