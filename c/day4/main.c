// Advent of Code - Day 4
//
// Author: Jacob Christensen

#include <stdio.h>
#include <stdlib.h>

static size_t answer1;
static size_t answer2;
static size_t pNumLength = 0;     // Number of your numbers per card
static size_t wNumLength = 0;     // Number of winning numbes per card
static size_t totalGames = 0;

size_t getNums(FILE *, size_t ***, size_t);
size_t getCardWinningNums(size_t *, size_t *);
size_t getCardValue(size_t);
size_t getTotalCards(size_t***, size_t);

size_t getNums(FILE *file, size_t ***nums, size_t gameNum) {
   
    // Get number from scratch cards, this
    // fucntion will get your numbers and winning nubmers
    // depending on where in the stream you are when called
    //
    // Params:
    //  FILE *file: File stream to read nubmers from
    //  size_t *nums: Player and Winning numbers
    //  size_t *gameNum: Game Number 
    //
    // Returns:
    //  The length of numbers

    size_t i = 0;
    int c;
    char num[3];
    size_t np = 0;  // num pointer
    size_t wf = 0;  // winning flag (set when looking at winning numbers)
    
    // Skip to player numbers
    while ((c = getc(file)) != ':' && c != EOF) {
        ;
    }
    if (c == EOF) { return 0; }

    // Gather player numbers
    do {
        c = getc(file);
        if (c >= '0' && c <= '9') {
            num[np++] = c;
            continue;
        }
        if (c == '|') {
            pNumLength = pNumLength ? pNumLength : i;
            i = 0;
            wf = 1;
            np = 0;
            continue;
        }
        if (c == ' ' || c == '\n') {
            if (np == 0) {
                continue;
            }
            num[np] = '\0';
            if (wf) {
                nums[gameNum][1][i++] = atoi(num);   
            }
            else {
                nums[gameNum][0][i++] = atoi(num);
            }
            np = 0;
        }
    }
    while (c != '\n' && c != EOF);
    
    wNumLength = wNumLength ? wNumLength : i;

    if (c == EOF) {
        return 0;
    }
    else {
        return 1;
    }

}

size_t getCardWinningNums(size_t *playerNums, size_t *winningNums) {

    size_t p;
    size_t w;
    size_t matches = 0;

    for (p = 0; p < pNumLength; p++) {
        for (w = 0; w < wNumLength; w++) {
            if (playerNums[p] == winningNums[w]) {
                matches++;
            }
        }
    }

    return matches;

}

size_t getCardValue(size_t n) {
    
    // Calculates the card value based on the amount
    // of winning numbers
    //
    // Params:
    //  size_t n: Number of matching winning numbers on a card
    //
    // Returns:
    //  Value of card

    size_t value = 0;

    for (; n > 0; n--) {
        value *= 2;
        value = value ? value : 1;
    }

    return value;

}

size_t getTotalCards(size_t*** cards, size_t gameNum) {
    
    // Recursively finds the number of cards won a game
    //
    // Params:
    //  size_t*** cards: All cards
    //  size_t gameNum: Current game
    //
    // Returns:
    //  The number of cards won

    size_t cardsWon;
    size_t totalCards;
    size_t i;

    cardsWon = getCardWinningNums(cards[gameNum][0], cards[gameNum][1]);
    totalCards = cardsWon;

    for (i = 1; i <= cardsWon && i + gameNum <= totalGames; i++) {
        totalCards += getTotalCards(cards, gameNum + i);
    }

    return totalCards;

}

int main(void) {

    FILE *f = fopen("../../inputs/day4/input.txt", "r");
    size_t ***allNums;
    size_t gameNum;
    size_t cardValue;
    size_t i;

    // Allocate 30 (card numbers), 2 (player and winning), 300 (number of cards)
    // Equivalent to size_t allNums[300][2][30]
    allNums = (size_t ***) malloc(300 * sizeof(size_t ***));
    for (i = 0; i < 300; i++) {
        allNums[i] = (size_t **) malloc(2 * sizeof(size_t **));
        allNums[i][0] = (size_t *) malloc(30 * sizeof(size_t *));
        allNums[i][1] = (size_t *) malloc(30 * sizeof(size_t *));
    }

    // Answer 1
    answer1 = 0;
    for (i = 1; getNums(f, allNums, i); i++) {
        totalGames++;
        cardValue = getCardValue(getCardWinningNums(allNums[i][0], allNums[i][1]));
        answer1 += cardValue;
    }

    //Answer 2
    answer2 = 0;
    for (i = 1; i <= totalGames; i++) {
        answer2 += 1;
        answer2 += getTotalCards(allNums, i);
    } 

    printf("%zu\n", answer1);
    printf("%zu\n", answer2);

    return EXIT_SUCCESS;
}
