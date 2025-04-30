#include <stdio.h>
#include <stdlib.h>

int main() {

    FILE *fp = fopen("text.txt", "r");

    if (!fp) {
        fprintf(stderr, "Can't open file text.txt\n");
        exit(EXIT_FAILURE);
    }


    printf("Reading file text.txt\n");


    


    if (!fclose(fp)) {
        printf("File text.txt closed successfully\n");
    } else {
        printf("Can't close file text.txt\n");
    }
    

    return 0;
}