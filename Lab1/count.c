/*
JT Vinolus
Coen 12
April 4 2019
Lab 1: Program will count number of words in a text file that is inputed.
Compile Command: gcc -o count count.c
Run Command: ./count (text file)
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_WORD_LENGTH 30

int main(int argc, char *argv[])
{
    if(argc == 1)//Checks to see if there is a text file inputed.
    {
        printf("The name of the file is missing from argument.\n");
        return 0;
    }
    FILE *fp;
    fp = fopen(argv[1], "r");
    if(fp == NULL)//Checks to see if the text file inputed is there.
    {
        printf("The file was not found.\n");
        fclose(fp);
        return 0;
    }
    int count = 0;
    char name[MAX_WORD_LENGTH];
     while(fscanf(fp, "%s", name) == 1)//Loops through each word in the text file.
    {
        count++; //For everyone 1 word, the count increases by 1.
    }
    printf("%d total words\n", count);//Prints total count.
    fclose(fp);
    return 0;
}