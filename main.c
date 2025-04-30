#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define LETTERS 26

const int LINE_SIZE = 256;

int countWordsInLine(char *str);
int countCharsInLine(char *str);
void countFrequencyInLine(char *str, int charFrequencies[LETTERS]);


int main() {

    FILE *fp = fopen("text.txt", "r");

    if (!fp) {
        fprintf(stderr, "Can't open file text.txt\n");
        exit(EXIT_FAILURE);
    }


    printf("Reading file text.txt\n");

    char line[LINE_SIZE];
    int linesCount = 0;
    int wordsCount = 0;
    int charsCount = 0;
    int charFrequencies[LETTERS] = {0};


    while (fgets(line, sizeof(line), fp)) {
        linesCount++;
        
        wordsCount += countWordsInLine(line);
        charsCount += countCharsInLine(line);
        countFrequencyInLine(line, charFrequencies);
        
    }

    if (!fclose(fp)) {
        printf("File text.txt closed successfully\n");
    } else {
        printf("Can't close file text.txt\n");
    }


    printf("There is %d lines and %d words %d chars in the text.txt file\n", linesCount, wordsCount, charsCount);
    printf("letters frequency: \n");

    for (int i = 0; i < LETTERS; i++) {
        printf("%3c", 'a' + i);
    }
    printf("\n");

    for (int i = 0; i < LETTERS; i++) {
        printf("%3d", charFrequencies[i]);
    }
    
    printf("\n");
    

    return 0;
}

void countFrequencyInLine(char *str, int charFrequencies[LETTERS]) {

    while (*str) {
        if (isalpha(*str)) {
            char lower = tolower(*str);
            int index = lower - 'a';
            charFrequencies[index]++;
        }

        str++;
    }
}

int countCharsInLine(char *str) {
    int charsCount = 0;

    while (*str) {

        if (isalpha(*str)) {
            charsCount++;
        }

        str++;
    }

    return charsCount;
}

int countWordsInLine(char *str) {
    int wordsCount = 0;
    bool isInWord = false;


    while (*str) {
        
        if (!isInWord && isalpha(*str)) {
            isInWord = true;
        } else if (isInWord && !isalpha(*str)) {
            isInWord = false;
            wordsCount++;
        }

        str++;
    }

    //Catch the last word if the line ends inside a word
    if (isInWord) {
        wordsCount++;
    }

    return wordsCount;
}