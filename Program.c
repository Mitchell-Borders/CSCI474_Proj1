#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


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

int getNumberPipes(){
    int pipeNum = -1;
    do{
        printf("Enter how many pipes to use (1,2, or 4): ");
        scanf("%d", &pipeNum);
    } while(pipeNum != 1 && pipeNum != 2 && pipeNum != 4);
    return pipeNum;
}

int getFileNumber(){
    int fileNum = -1;
    do{
        printf("Enter file number to use (1 ,2, or 3), (1000, 10000, or 100000 numbers respectively): ");
        scanf("%d", &fileNum);
    } while(fileNum != 1 && fileNum != 2 && fileNum != 3);
    return fileNum;
}

int getPower(int base, int exponent){
    int total = 1;
    for(int i = 0; i < exponent; i++){
        total *= base;
    }
    return total;
}

void getFileContents(int pipeNum, const char* fileName, int numbers[]){
    int arrSize = getPower(10, (2+pipeNum));
    numbers[arrSize];
        // Read and sum numbers from previously made file
    FILE* inFile;
    inFile = fopen(fileName, "r");
    if (inFile != 0) {
        int curr;
        int i = 0;
        // Sum numbers
        while (fscanf(inFile, "%d", &curr) != EOF) {
            numbers[i++] = curr;
        }
        // close file
        fclose(inFile);
    }
}


int main() {
    clock_t start = clock();

    int fds[2]; // Pipe
    pipe(fds);

    int pipeNum = getNumberPipes();
    int fileNum = getFileNumber();
    const char* fileName = getFileName(fileNum);
    int rowsInFile = getPower(10, (2 + fileNum));
    // Create array containing all numbers in the list
    int numbers[rowsInFile];
    getFileContents(pipeNum, fileName, numbers);

    // Create forks and sum file values
    int incrementes = rowsInFile / pipeNum;
    int currStart = 0;
    int currEnd = incrementes;
    for(int i = 1; i <= pipeNum; i++){
        int start = currStart;
        int end = currEnd;
        currStart += incrementes;
        currEnd += incrementes;
        if(fork() == 0){
            int total = 0;
            for(int i = start; i < end; i++){
                total += numbers[i];
            }
            write(fds[1], &total, sizeof(total));
            exit(0);
        }
    }

    // Recieve totals from child processes
    int finalTotal = 0;
    for(int i = 1; i <= pipeNum; i++){
        int readTotal = 0;
        read(fds[0], &readTotal, sizeof(readTotal));
        printf("Total for child %d : %d\n", i, readTotal);
        finalTotal += readTotal;
    }
    printf("The final total of the file is: %d\n", finalTotal);

    clock_t endTime = clock() - start;
    double totalTime = ((double)endTime) / CLOCKS_PER_SEC;

    printf("With %d pipes and %d file # selected, the program took %f seconds to run: \n\n\n\n", pipeNum, fileNum, totalTime);
    return 0;
}


