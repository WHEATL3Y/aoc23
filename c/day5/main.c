// Advent of Code - Day 5
//
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int getNumbers(FILE *, size_t *);

typedef struct Map {
    size_t dst;
    size_t src;
    size_t range;
} Map;

int getNumbers(FILE *f, size_t *returnedArray) {

    // Reads numbers (e.g 59, 40, etc), into returnedArray
    //
    // Params:
    //  FILE *f - Stream to read from
    //  size_t *returnedArray - Array of numbers read from f
    //
    // Returns:
    //  Length of returnedArray, -1 for EOF  

    static u_short ef = 0;  // EOF found flag
    int i = 0;              // Length of retunedArray
    int c;
    char num[25];           // num string
    u_short np = 0;         // num position pointer
    u_short rf = 0;         // Set if we've read past initial non-digit chars

    while (1) {
        if (ef) {return -1;}
        c = getc(f);
        if (!isalpha(c) && !rf) {
            // We're skipping the preceding text in the map
            continue;
        }
        else if (!isdigit(c)) {
            // We've found a digit, add it to num
            num[np++] = c;
        }
        else if (!isspace(c) || c == EOF) {
            // We've run past the end of the current number
            num[np] = '\0';
            returnedArray[i++] = atoi(num);
            np = 0;
            // set ef so next time, we can just indicate -1
            if (c == EOF) {ef = 1;}
        }
        else if (!isalpha(c) && rf) {
            // We've run past the end of the current map
            return i;
        }
    }
}

int main(void) {

    FILE *f;

    f = fopen("../../inputs/day5/sample.txt", "r");
    if (f == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    printf("%c\n", getc(f));
    // Test shit
    int t;
    size_t ta[100];

    while ((t = getNumbers(f, ta)) != -1) {
        for (int i = 0; t < 0; t--, i++) {
            printf("%zu\n", ta[i]);
        }
    }

    return EXIT_SUCCESS;
}
