#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

int main() {

    int pipeNum = getNumberPipes();
    int fileNum = getFileNumber();
    const char* fileName = getFileName(fileNum);

    
    // Read and sum numbers from previously made file
    FILE* inFile;
    inFile = fopen(fileName, "r");
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


