// Advent of Code 2023
// Day 1
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char numMap[10][6] = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

size_t getCalibrationValue(char *, size_t);
size_t getCalibrationValue(char *, size_t);
size_t searchNumericValue(char *, size_t, size_t *);
size_t sum(size_t *, size_t);

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

size_t getCalibrationValue1(char *string, size_t n) {

    char calibrationString[3];
    size_t results[10];
    size_t numResults;

    size_t maxVal = 0;
    size_t minVal = 10;
    size_t maxI = 0;
    size_t minI = 999;
    size_t resultCounter = 0;

    for (size_t i = 1; i <= 9; i++) {
        numResults = searchNumericValue(string, i, results);
        
        for (size_t j = 0; j < numResults; j++) {
            /* printf("%zu:%zu", results[j], i); */
            resultCounter++;
            if (results[j] > maxI) {
                maxVal = i;
                maxI = results[j];
            }
            if (results[j] < minI) {
                minVal = i;
                minI = results[j];
            }
        }
        /* printf("\n"); */
    }

    if (resultCounter == 0) {
        return 0;
    }
    calibrationString[0] = minVal + '0';
    calibrationString[1] = '\0';
    if (resultCounter > 1) {
        calibrationString[1] = maxVal + '0';
        calibrationString[2] = '\0';
    }
    printf("%s\n", calibrationString);
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
        /* printf("%zu\n", values[i]); */
        sum += values[i++];
    }

    return sum;

}

size_t searchNumericValue(char *string, size_t findNumber, size_t *indexes) {

    // Searches for string of numbers (one, two, etc) or
    // (1, 2, etc)
    // 
    // The reason to insert instead of replace is that some
    // values overlap (twone), and the end result won't be
    // different weather or not the original string is still
    // present
    char findString[6];
    size_t numIndexes[10];
    char sc;                        // string char
    char fc;                        // find char
    size_t sp;                      // string pointer
    size_t fp;                      // from pointer
    size_t np = 0;                  // numIndexes pointer
    u_short ff;                     // found flag

    strcpy(findString, numMap[findNumber]);

    // Search for string indexes
    for (sp = 0; (sc = string[sp]) != '\0'; sp++) {
        ff = 1;
        for (fp = 0; (fc = findString[fp]) != '\0'; fp++) {
            if (sc == fc) {
                sc = string[++sp];
            }
            else {
                ff = 0;
                break;
            }
        }
        if (ff) {
            numIndexes[np++] = sp;
        }
    }

    for (sp = 0; (sc = string[sp]) != '\0'; sp++) {
        if (sc == findNumber + '0') {
            numIndexes[np++] = sp + 1;
        }
    }

    for (size_t i = 0; i < np; i++) {
        indexes[i] = numIndexes[i];
    }

    return np;

}

int main(void) {

    size_t answer1Values[1000];
    size_t answer2Values[1000];
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
        /* answer1Values[lc] = getCalibrationValue(lineBuf, strlen(lineBuf)); */
        printf("%s", lineBuf);
        answer2Values[lc++] = getCalibrationValue1(lineBuf, strlen(lineBuf));
    }

    /* answer1 = sum(answer1Values, lc); */
    answer2 = sum(answer2Values, lc);

    /* printf("%zu\n", answer1); */
    printf("%zu\n", answer2);

    return EXIT_SUCCESS;

}
