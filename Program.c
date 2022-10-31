#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


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
        printf("Enter how many files to use (1,2, or 3): ");
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
    int arrSize = getPower(10, (3+pipeNum));
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
        // Show total and close file
        fclose(inFile);
    }
}




int main() {

    int pipeNum = getNumberPipes();
    int fileNum = getFileNumber();
    const char* fileName = getFileName(fileNum);
    int numbers[getPower(10, (10, (3+pipeNum)))];
    getFileContents(pipeNum, fileName, numbers);

    for(int i = 1; i <= getPower(10, (3+pipeNum)); i++){
        printf("%d", numbers[i]);
        printf("\n");
        // if(fork() == 0){
        //     startIndex = 
        //     exit(0);
        // }
    }
    

    return 0;
}


