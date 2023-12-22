// Advent of Code - Day 3
//
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

size_t static xMax;
size_t static yMax;

size_t answer1 = 0;
size_t answer2 = 0;

typedef struct {
    int x;
    int y;
} point;

void getMapSize(size_t *, size_t *, FILE *);
int getNextGearInLine(char *, size_t);
int getWholeNumber(point, char **);
size_t digitLength(size_t);
point scanPoint(point, char **, size_t);
size_t isSymbol(char);
size_t isDigit(char);

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

int getNextSymbolInLine(char *line, size_t current) {

    // Scans through line starting at current,
    // returns x index where symbol was found
    //
    // Params:
    //  char *line: Array of characters
    //  size_t current: Position in line to start search
    //
    // Returns:
    //  int: index of returned, -1 for no result

    int i;

    for (i = current; i < xMax; i++) {
        if (isSymbol(line[i])) {
            return i;
        }
    }

    return -1;

}

point scanPoint(point p, char **map, size_t reverse) {

    // Looks at every value surrounding p in map
    // to to see if they meet the criteria of sFunc 
    //
    // Params:
    //  point p: x, y coords to scan around in map
    //  char *map: map of characters to search
    //  size_t reverse: Flag, 0 = look clockwise, 1 = counter
    //  int (*sFunc)(char): Search function
    //
    // Returns:
    //  fm - Point at which a match was found

    point fm;       // Found Match, store it here, this gets returned
    int i;


    for (i = (reverse ? 7 : 0); (reverse ? i >= 0 : i <= 7); (reverse ? i-- : i++)) {
        switch (i) {
            case 0:
                fm.x = p.x - 1;
                fm.y = p.y - 1;
                break;
            case 1:
                fm.x = p.x;
                fm.y = p.y - 1;
                break;
            case 2:
                fm.x = p.x + 1;
                fm.y = p.y - 1;
                break;
            case 3:
                fm.x = p.x + 1;
                fm.y = p.y;
                break;
            case 4:
                fm.x = p.x + 1;
                fm.y = p.y + 1;
                break;
            case 5:
                fm.x = p.x;
                fm.y = p.y + 1;
                break;
            case 6:
                fm.x = p.x - 1;
                fm.y = p.y + 1;
                break;
            case 7:
                fm.x = p.x - 1;
                fm.y = p.y;
                break;
        }

        if (fm.x < 0 || fm.y < 0 || fm.x > xMax - 1 || fm.y > yMax - 1) {
           continue; 
        }
        if (isDigit(map[fm.y][fm.x])) {
            return fm;
        }
    }
    
    fm.x = -1;
    fm.y = -1;
    return fm;
}

size_t isSymbol(char c) {
    
    // Checks whether c is a symbol (not 0-9 or .)
    // 
    // Params:
    //  char c: Character to check
    //
    // Returns:
    //  1 if c is not 0-9 or .
    //  0 if c is 0-9 or .
    
    return ((c < '0') || (c > '9')) && c != '.';

}

size_t isDigit(char c) {

    // Checks whether c is a digit
    //
    // Params:
    //  char c: Character to check
    //
    // Returns:
    //  1 if c is a digit (0-9)
    //  0 if ci is not a digit

    return (c >= '0' && c <= '9');

}

int getWholeNumber(point p, char **map) {

    // Takes a single point that contains a digit
    // and finds the entire number that digit is part of
    //
    // Params:
    //  point p: Point at which to start search
    //  char **map: Map to search in
    //  size_t *pp: current index of *points
    //
    // Returns:
    //  Whole Number found

    char c;
    char numString[4];
    size_t nsp = 0;     // numString pointer
    size_t x = p.x;
    size_t y = p.y;

    // Check that there is a digit at p
    if (!isDigit(map[y][x])) {
        printf("ERROR: no digit at %zu, %zu\n", x, y);
        return -1;
    }

    // Seek to first digit in number
    if (x == 0) {
        ;
    }
    else {
        for (; isDigit(c = map[y][x]); x--) {
            ;
        }

        // Reset x back to first digit
        x++;
    }

    // Write each digit into numString
    for (; isDigit(c = map[y][x]); x++) {
        numString[nsp++] = c; 
    }

    numString[nsp] = '\0';

    return atoi(numString);

}

int main(void) {

    FILE *f = fopen("../../inputs/day3/input.txt", "r");
    size_t xi;              // x index for map array
    size_t yi;              // y index for map array
    char **map;             // Array to represent map
    char* lineBuf;          // Buffer for map lines
    size_t lSize;           // Length of lineBuf (x + 1)
    size_t chars;           // Return value of getline
    point currentSym;       // Curent symbol being analyzed
    point currentNum;       // Curent number being analyzed
    point currentNum1;      // Storage for a stupid comparison later
    size_t sForwardNum;     // Result of forward scan
    size_t sBackwardNum;    // Result of backward scan

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

    // Answer 1 loop
    yi = 0;
    while (yi < yMax) {
        xi = 0;

        while ((xi = getNextSymbolInLine(map[yi], xi)) != -1) {
            sForwardNum = 0;
            sBackwardNum = 0;
            currentSym.x = xi;
            currentSym.y = yi;

            // Scan around current symbol in both directions
            if ((currentNum = scanPoint(currentSym, map, 0)).x != -1) {
                sForwardNum = getWholeNumber(currentNum, map);
                answer1 += sForwardNum;
            }

            // Check for second adjacent number
            currentNum1 = currentNum;
            if ((currentNum = scanPoint(currentSym, map, 1)).x != -1) {
                sBackwardNum = getWholeNumber(currentNum, map);

            }

            // If number matches first scan, it's already been added
            // ... Unless it's not, also check if y coord is different
            // between the two they snuck a couple of those in there
            if ((sBackwardNum == sForwardNum) && currentNum.y == currentNum1.y) {
                xi++;
                continue;
            }

            answer1 += sBackwardNum;
            xi++;

        }

        yi++;

    } 

    // Answer 2 Loop
    yi = 0;
    while (yi < yMax) {
        xi = 0;
        while ((xi = getNextSymbolInLine(map[yi], xi)) != -1) {
            sForwardNum = 0;
            sBackwardNum = 0;
            currentSym.x = xi;
            currentSym.y = yi;

            if (map[yi][xi] != '*') {
                xi++;
                continue;
            }

            if ((currentNum = scanPoint(currentSym, map, 0)).x != -1) {
                sForwardNum = getWholeNumber(currentNum, map);
            }

            currentNum1 = currentNum;
            if ((currentNum = scanPoint(currentSym, map, 1)).x != -1) {
                sBackwardNum = getWholeNumber(currentNum, map);
            }

            if ((sBackwardNum == sForwardNum) && currentNum.y == currentNum1.y) {
                xi++;
                continue;
            }

            answer2 += (sBackwardNum * sForwardNum);
            xi++;

        }
        
        yi++;
    
    }
    
    printf("%zu\n", answer1);
    printf("%zu\n", answer2);

    return EXIT_SUCCESS;
}
