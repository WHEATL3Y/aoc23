// Advent of Code - Day 2
//
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>

size_t checkValid(char *);

size_t answer1 = 0;
size_t answer2 = 0;

size_t gameValid = 0;

enum colorThresholds {
    red = 12,
    green = 13,
    blue = 14
};

size_t checkValid(char *string) {

    // Returns 0 if the game would be possible
    // Returns non 0 if the game would not be
    //
    // Params:
    //  char *string: Game Data to check
    //
    // Returns:
    //  0: Game would be possible
    //  != 0: Game would not be possible
   
    size_t i = 0;   // Current index of string    
    char c;         // Character being compared
    char num[4];    // Storage for color counters
    size_t intNum;  // Int version of string num
    size_t nc = 0;  // Num counter

    // Skip past Game x: 
    while ((c = string[i++]) != ':');

    // Gather numbers and colors for round
    while ((c = string[i]) != '\n') {
        // Skip to next number
        while (c <= '0' && c >= '9') {
            continue;
        }

        // Gather number
        while ((c = string[i++]) >= '0' && c <= '9') {
            num[nc++] = c; 
        }
        num[nc] = '\0';
        intNum = atoi(num);
        nc = 0;

        // Get color and compare to game thresholds
        c = string[i];
        if (c == 'r' && intNum > red) {
            return 1;
        }
        else if (c == 'g' && intNum > green) {
            return 1;
        }
        else if (c == 'b' && intNum > blue) {
            return 1;
        }
    }  
    
    return 0;

}

size_t getGamePower(char *string) {
   
    // Multiplies the largest number for each color
    //
    // Params:
    //  char *string: The game string
    //
    // Returns:
    //  size_t: Product of max values for each color

    size_t i = 0;   // Current index of string    
    char c;         // Character being compared
    char num[4];    // Storage for color counters
    size_t intNum;  // Int version of string num
    size_t nc = 0;  // Num counter

    size_t maxRed = 0;
    size_t maxGreen = 0;
    size_t maxBlue = 0;

    // Skip past Game x: 
    while ((c = string[i++]) != ':');

    // Gather numbers and colors for round
    while ((c = string[i]) != '\n') {
        // Skip to next number
        while (c <= '0' && c >= '9') {
            continue;
        }

        // Gather number
        while ((c = string[i++]) >= '0' && c <= '9') {
            num[nc++] = c; 
        }
        num[nc] = '\0';
        intNum = atoi(num);
        nc = 0;

        // Get color and compare to game thresholds
        c = string[i];
        if (c == 'r' && intNum > maxRed) {
            maxRed = intNum;
        }
        else if (c == 'g' && intNum > maxGreen) {
            maxGreen = intNum;
        }
        else if (c == 'b' && intNum > maxBlue) {
            maxBlue = intNum;
        }
    }  
    
    return maxRed * maxBlue * maxGreen;

}


int main(void) {

    FILE *f = fopen("../../inputs/day2/input.txt", "r");

    size_t cc;          // Character Count
    size_t gc = 0;      // Game Counter
    char *lineBuf;
    size_t bufSize = 1000;

    lineBuf = (char *)malloc(1000 * sizeof(char));

    while ((cc = getline(&lineBuf, &bufSize, f)) != -1) {
        ++gc;
        if (!checkValid(lineBuf)) {
            answer1 += gc;
        }

        answer2 += getGamePower(lineBuf);

    }

    printf("%zu\n", answer1);
    printf("%zu\n", answer2);

    return EXIT_SUCCESS;
}
