// Advent of Code 2023
// Day 1
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t getCalibraionValue(char*, size_t);
void replaceWordNumbers(char*, size_t);
size_t sum(size_t*, size_t);

size_t getCalibrationValue(char* string, size_t n) {

    // string:  String that contains calibraion digits
    // n        Length of the string
    //
    // Returns:
    // Calibration value: size_t
    char calibrationString[3];
    char c;
    size_t si;      // String Index

    for (si = 0; si < n; si++) {
        if ((c = string[si]) >= '0' && c <= '9') {
            calibrationString[0] = c;
            break;
        }
    }

    for (si = n - 2; si >= 0; si--) {
        if ((c = string[si]) >= '0' && c <= '9') {
            calibrationString[1] = c;
            break;
        }
    }

    calibrationString[2] = '\0';
    
    return atoi(calibrationString);

}

size_t sum(size_t *values, size_t n) {

    // values:  Array of values to add
    // n        Length of the array
    //
    // Returns:
    // Sum of all values: size_t
    
    size_t sum = 0;
    size_t i = 0;
   
    while (i < n) {
        printf("%zu\n", values[i]);
        sum += values[i++];
    }

    return sum;

}

/* void replaceWordNumbers(char *string, size_t n) { */
/*  */
/*     // Replace written words (one, two, three, etc.) with the */
/*     // number value (1, 2, 3, etc.) */
/*      */
/*     enum numbers {} */
/* } */

char *searchNumericValue(char *string, char *findString) {

    // Searches for string of numbers (one, two, etc) or
    // (1, 2, etc)
    // 
    // The reason to insert instead of replace is that some
    // values overlap (twone), and the end result won't be
    // different weather or not the original string is still
    // present
    

    char sc;                        // string char
    char fc;                        // find char
    size_t sp;                      // string pointer
    size_t fp;                      // from pointer
    size_t cp = 0;                  // charBuf pointer
    size_t np = 0;                  // newString pointer
    u_short ff;                     // found flag

    for (sp = 0; (sc = string[sp]) != '\0'; sp++) {
        ff = 1;
        for (fp = 0; (fc = findString[fp]) != '\0'; fp++) {
            if (sc == fc) {
                sc = string[sp++];
                continue;
            }
            else {
                charBuf[cp++] = sc;
                for (size_t i = 0; i < cp;) {
                    newString[np++] = charBuf[i++];
                }
                ff = 0;
                break;
            }
        }
        if (ff) {
            newString[np++] = add;
            for (size_t i = 0; i < cp;) {
                newString[np++] = charBuf[i++];
            }
        }
        cp = 0;
    }

    newString[np] = '\0';
    return newString;

}
int main(void) {

    size_t answer1Values[1000];
    size_t answer1;
    size_t answer2;

    FILE *f = fopen("../../inputs/day1/input.txt", "r");
    char *lineBuf;
    size_t lc;      // Line Index
    size_t bufSize = 100;
    size_t chars;

    lineBuf = (char *)malloc(bufSize * sizeof(char));
    lc = 0;

    while ((chars = getline(&lineBuf, &bufSize, f) > 0)) {
        answer1Values[lc++] = getCalibrationValue(lineBuf, strlen(lineBuf));
    }

    answer1 = sum(answer1Values, lc);

    printf("%zu\n", answer1);

    char string1[25] = "jjd74twonepvj";
    char stringFrom[10] = "two";
    printf("%s\n", addNumericValue(string1, stringFrom, '2'));

    return EXIT_SUCCESS;
}
