#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    // Create and write random numbers to file
    FILE* outFile;
    outFile = fopen("numbers.txt", "w");
    
    // Read and sum numbers from previously made file
    FILE* inFile;
    inFile = fopen("numbers.txt", "r");
    int total = 0;
    if (inFile != 0) {
        int curr;
        // Sum numbers
        while (fscanf(inFile, "%d", &curr) != EOF) {
            total += curr;
        }
        // Show total and close file
        printf("%d", total);
        fclose(inFile);
    }


    return 0;
}
