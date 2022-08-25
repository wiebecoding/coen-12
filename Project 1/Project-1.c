/*
Brian Wiebe
1/4/22
COEN 13L - Intro to Adv. Data Structures
Lab 1 - Number of Words in a TXT File
Dr. Li
*/

//importing library
#include <stdio.h>
#include <stdlib.h>

//constants for program
#define MAX_WORD_LENGTH 30

//inital funciton declaration
int analyzeFile(char *filename);

int main(int argc, char *argv[]){
    if (argc == 1){ 
        printf("The name of the file is missing!\n"); 
        return 0; 
    }
    int res = analyzeFile(argv[1]);
    printf("%i Total Words", res);
}

int analyzeFile(char *filename){
    FILE *inputFile = fopen(filename, "r");
    if(inputFile == NULL){
        printf("There is no text file with that name. Please try again.");
        exit(0);
    }
    char current[MAX_WORD_LENGTH];
    int wordCount = 0;
    //scaning words and adding them up
    while(fscanf(inputFile, "%s", current) != EOF){
        wordCount += 1;
    }
    fclose(inputFile);
    return wordCount;
}