#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    // Create and write random numbers to file
    FILE* outFile;
    outFile = fopen("/CSCI474_Proj1/number.txt", "w");

    if (outFile != 0) {
        // Time since Jan 1, 1970 to make sure random numbers are not the same
        srand(time(NULL));
        for (int i = 0; i < 100; i++) {
            // Do 100 numbers to write
            fprintf(outFile, "%d", rand());
            fprintf(outFile, "\n");

        }
        fclose(outFile);
    }
    
    // Read and sum numbers from previously made file
    FILE* inFile;
    inFile = fopen("/CSCI474_Proj1/number.txt", "r");
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
