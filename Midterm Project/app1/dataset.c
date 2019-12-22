/*
 * File:        huffman.c
 *
 * Author:      JT Vinolus
 * 
 * Date:        June 7 2019
 *
 * Mehtod: Sorted Array by Age.
 * 
 * Description: This file contains the needed generic interface functions 
 *              for midterm prj's application 1.  
 *
 *              
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "dataset.h"

typedef struct set SET;
struct set{
    int *age;
    int *id;
    int count;
    int length;
};

void printingList(SET *sp)//
{   
    for(int x = 0; x < sp->count; x++)
        printf("ID %d. Age: %d.\n", sp->id[x], sp->age[x]);
}

SET *createDataSet(int maxElts)//Creates the Data set. Sets all ages and id to initally 0. Big O: O(maxElts)
{
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->age = malloc(sizeof(int)*maxElts);
    sp->id = malloc(sizeof(int)*maxElts);
    for(int i = 0; i < maxElts; i++)
    {
        sp->age[i] = 0;
        sp->id[i] = 0;
    }
    return sp;
}


void destroyDataSet(SET *sp)//Destroys the data set. Big O: O(1)
{
    assert(sp != NULL);
    free(sp->age);
    free(sp->id);
    free(sp);
    return;
}

int binarySearchAge(SET *sp, int age, bool *found)// Using binary seaching to find give age. Big O: log(n)
{
    assert(sp != NULL && age > 17 && age < 31);
    int lo = 0;
    int hi = sp->count - 1;
    int mid;
    while(lo <= hi)
    {
        mid = (lo + hi)/2;
        if(age < sp->age[mid])
            hi = mid - 1;
        else if(age > sp->age[mid])
            lo = mid + 1;
        else
        {
            *found = true;
            printf("ID: %d was found with Age: %d \n", sp->id[mid], sp->age[mid]);
            return mid;
        }
    }
    printf(" No ID was found with the age %d.\n", age);
    *found = false;
    return lo;
}

void insert(SET *sp, int age, int id)//Inserts given age and ID in ascending order. Big O: O(n)
{
    bool found;
    int idx = 0;
    idx = binarySearchAge(sp, age, &found);
    for( int i = sp->count; i > idx; i--)
    {
        sp->age[i] = sp->age[i-1];
        sp->id[i]   = sp->id[i-1];
    }
    sp->age[idx] = age;
    sp->id[idx] = id;
    sp->count++;

    

    printf("ID %d has been added. Age: %d\n", id, age);
    return;
}

void deletion(SET *sp, int idx, int age)// Deletes the given ages by first finding one and traversing up down, deleting each node until it reaches a different age. Big O: O(n).
{
    assert(sp != NULL);
    int bot;
    int i;
    int top;
     printf("Deleting ID(s) with Age %d:  IDs are ", age);
    for(i = idx; sp->age[i] == age; i++)
    {
        printf("%d, ", sp->id[i]);
        sp->age[i] = 0;
    }
    bot = i - 1;
    if(idx != 0)
    {  
        for(i = idx - 1; sp->age[i] == age; i--)
        {
            printf("%d, ", sp->id[i]);
            sp->age[i] = 0;
        }
    }
    else
    {
        i = 0;
    }
    top = i + 1;
    int originalCount = sp->count;
    for(int i = bot + 1; sp->count !=  originalCount - (bot - top) - 1; i--)
    {
        for(int j = i; j != sp->count; j++)
        {
            sp->age[j - 1] = sp->age[j];
            sp->id[j - 1] = sp->id[j];     
        }
        sp->count -= 1;
    }
    printf("\n");
}

int maxAgeGap(SET *sp)//Gives the range of the ages. Big O: O(1)
{
    int max = sp->age[sp->count -1];
    int min = sp->age[0];
    return max - min;
    
}