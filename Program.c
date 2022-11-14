#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Get file name based on user entered file number
char * getFileName(int fileNum){
    if(fileNum == 1){
        return "file1.dat";
    }
    else if(fileNum == 2){
        return "file2.dat";
    }
    else if(fileNum == 3){
        return "file3.dat";
    }
}

// Get user entry for number of child processes to use
int getNumberChild(){
    int pipeNum = -1;
    do{
        printf("Enter how many children processes to use (1,2, or 4): ");
        scanf("%d", &pipeNum);
    } while(pipeNum != 1 && pipeNum != 2 && pipeNum != 4);
    return pipeNum;
}

// Get user entry for which file to use
int getFileNumber(){
    int fileNum = -1;
    do{
        printf("Enter file number to use (1 ,2, or 3), (1000, 10000, or 100000 numbers respectively): ");
        scanf("%d", &fileNum);
    } while(fileNum != 1 && fileNum != 2 && fileNum != 3);
    return fileNum;
}

// Number of lines in the file is a power of 10
// Use method to calculate number of lines in file
int getPower(int base, int exponent){
    int total = 1;
    for(int i = 0; i < exponent; i++){
        total *= base;
    }
    return total;
}

int main() {
    int childNum = getNumberChild();
    int fileNum = getFileNumber();
    const char* fileName = getFileName(fileNum);

    // Start timer AFTER user input
    clock_t start = clock();

    // Create pipe
    int fds[2];
    pipe(fds);
    // Determine how many numbers each child should read in
    int increment = getPower(10, (fileNum + 2)) / childNum;
    for(int i = 0; i < childNum; i++){
        // Create child process
        if(fork() == 0){
            FILE* inFile;
            inFile = fopen(fileName, "r");
            // Set line to start reading at in the file
            fseek(inFile, (i * increment * 5), SEEK_SET);
            // Sum lines in file that child is responsible for
            int childTotal = 0;
            for(int k = 0; k < increment; k++){
                int lineNum = 0;
                fscanf(inFile, "%d\n", &lineNum);
                childTotal += lineNum;
            }
            printf("Total for child %d: %d\n", i + 1, childTotal);
            write(fds[1], &childTotal, sizeof(int));
            exit(0);
        }
    }
    // Sum child processes
    int finalTotal = 0;
    for(int i = 0; i < childNum; i++){
        int childTotal = 0;
        read(fds[0], &childTotal, sizeof(int));
        finalTotal += childTotal;
    }
    // Print end results
    printf("The final total of the file is: %d\n", finalTotal);
    clock_t endTime = clock() - start;
    double totalTime = ((double)endTime) / CLOCKS_PER_SEC;
    printf("With %d child processes and file #%d  selected, the program took %f seconds to run: \n\n", childNum, fileNum, totalTime);

    return 0;
}


