#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define LETTERS 26

const int LINE_SIZE = 256;

int countWordsInLine(char *str);
int countCharsInLine(char *str);
void countFrequencyInLine(char *str, int charFrequencies[LETTERS]);


int main(int argc, char *argv[]) {

    
    if (argc < 2) {
        printf("Usage: <fileName1> <fileName2> <fileName3>...\n");
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen("result.txt", "a");
    if (!outputFile) {
        perror("Can't open file");
        exit(EXIT_FAILURE);
    }


    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");

        if (!fp) {
            perror("Can't open file");
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
            printf("File %s closed successfully\n", argv[1]);
        } else {
            printf("Can't close file %s\n", argv[1]);
        }

        fprintf(outputFile, "There is %d lines and %d words %d chars in the %s file\n", linesCount, wordsCount, charsCount, argv[i]);
        fprintf(outputFile, "letters frequency: \n");

        for (int i = 0; i < LETTERS; i++) {
            fprintf(outputFile, "%3c", 'a' + i);
        }
        fprintf(outputFile, "\n");

        for (int i = 0; i < LETTERS; i++) {
            fprintf(outputFile, "%3d", charFrequencies[i]);
        }
        
        fprintf(outputFile, "\n");

    }
    
    if(!fclose(outputFile)) {
        printf("File %s closed succesffuly\n", "result.txt");
    } else {
        printf("Can't close file %s\n", "result.txt");
    }

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