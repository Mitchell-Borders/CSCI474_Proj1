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

int getNumberChild(){
    int pipeNum = -1;
    do{
        printf("Enter how many children processes to use (1,2, or 4): ");
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

int main() {
    clock_t start = clock();

    int childNum = getNumberChild();
    int fileNum = getFileNumber();
    const char* fileName = getFileName(fileNum);

    int fds[2];
    pipe(fds);
    
                  // num lines file
    int increment = getPower(10, (fileNum + 2)) / childNum;
    for(int i = 0; i < childNum; i++){
        
        if(fork() == 0){
            FILE* inFile;
            inFile = fopen(fileName, "r");
            fseek(inFile, (i * increment * 4), SEEK_CUR);
            int childTotal = 0;
            
            for(int k = 0; k < increment; k++){
                int lineNum = 0;
                fscanf(inFile, "%d\n", &lineNum);
                childTotal += lineNum;
            }
            write(fds[1], &childTotal, sizeof(childTotal));
            exit(0);
        }
    }
    int finalTotal = 0;

    for(int i = 0; i < childNum; i++){
        int childTotal;
        read(fds[0], &childTotal, sizeof(childTotal));
        printf("Total for child %d: %d\n", i + 1, childTotal);
        finalTotal += childTotal;
    }

    printf("The final total of the file is: %d\n", finalTotal);

    clock_t endTime = clock() - start;
    double totalTime = ((double)endTime) / CLOCKS_PER_SEC;

    printf("With %d pipes and %d file # selected, the program took %f seconds to run: \n\n", childNum, fileNum, totalTime);






















    // int fds[2]; // Pipe
    // pipe(fds);

    // int childNum = getNumberChild();
    // int fileNum = getFileNumber();
    // const char* fileName = getFileName(fileNum);
    // int rowsInFile = getPower(10, (2 + fileNum));
    // // Create array containing all numbers in the list
    // // int numbers[rowsInFile];
    // // getFileContents(childNum, fileName, numbers);

    // // Create forks and sum file values
    // int start = 0;
    // for(int i = 1; i <= childNum; i++){
    //     fpeek()
    //     if(fork() == 0){
    //         int total = 0;
    //         for(int i = currStart; i < currEnd; i++){
                
    //         }
    //         write(fds[1], &total, sizeof(total));
    //         exit(0);
    //     }
    // }

    // // Recieve totals from child processes
    // int finalTotal = 0;
    // for(int i = 1; i <= childNum; i++){
    //     int readTotal = 0;
    //     read(fds[0], &readTotal, sizeof(readTotal));
    //     printf("Total for child %d : %d\n", i, readTotal);
    //     finalTotal += readTotal;
    // }
    // printf("The final total of the file is: %d\n", finalTotal);

    // clock_t endTime = clock() - start;
    // double totalTime = ((double)endTime) / CLOCKS_PER_SEC;

    // printf("With %d pipes and %d file # selected, the program took %f seconds to run: \n\n\n\n", childNum, fileNum, totalTime);
    return 0;
}


