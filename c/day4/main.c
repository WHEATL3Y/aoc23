// Advent of Code - Day 4
//
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>

static size_t answer1;
static size_t answer2;
static size_t pNumLength;     // Number of your numbers per card
static size_t wNumLength;     // Number of winning numbes per card

size_t getNums(FILE *, size_t *, size_t * );

size_t getNums(FILE *file, size_t *pNums, size_t *wNums) {
   
    // TODO: re-write after some sleep
    // Get number from scratch cards, this
    // fucntion will get your numbers and winning nubmers
    // depending on where in the stream you are when called
    //
    // Params:
    //  FILE *file: File stream to read nubmers from
    //  size_t *pNums: Player numbers
    //  sizt_t *wNums: Winning numbers
    //
    // Returns:
    //  The length of numbers

    size_t i = 0;
    int c;
    char num[3];
    size_t np;      // num pointer
    
    pNumLength = 0;
    wNumLength = 0;

    // Skip to player numbers
    while ((c = getc(file)) != ':') {
        ;
    }

    // Gather player numbers
    while ((c = getc(file)) != '|') {
        np = 0;
        while ((c = getc(file)) >= '0' && c <= '9') {
            num[np++] = c;
        }
        num[np] = '\0';
        pNums[i++] = atoi(num);
    }

    pNumLength = i;
    i = 0;

    // Gather winning numbers
    while ((c = getc(file))) {
        np = 0;
        while ((c = getc(file)) >= '0' && c <= '9') {
            num[np++] = c;
        }
        num[np] = '\0';
        wNums[i++] = atoi(num);
        if (c == '\n' || c == EOF) { break; }
    }

    wNumLength = i;

    if (c == EOF) {
        return 0;
    }
    else {
        return 1;
    }
}

int main(void) {

    FILE *f = fopen("../../inputs/day4/sample.txt", "r");
    size_t myNumbers[100];
    size_t winningNumbers[100];

    while(getNums(f, myNumbers, winningNumbers)) {
        printf("Player: %zu, Winning %zu\n", myNumbers[0], winningNumbers[0]);
    }

    return EXIT_SUCCESS;
}
