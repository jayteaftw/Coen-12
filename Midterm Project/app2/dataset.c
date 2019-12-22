/*
 * File:        huffman.c
 *
 * Author:      JT Vinolus
 * 
 * Date:        June 7 2019
 *
 * Mehtod: Array where ID Matches index.
 * 
 * Description: This file contains the needed generic interface functions 
 *              for midterm prj's application 2.  
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
};

SET *createDataSet(int maxElts)// Big O: O(maxElts)
{
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->age = malloc(sizeof(int)*maxElts);
    for(int i = 0; i < maxElts; i++)
    {
        sp->age[i] = -1;
    }
    return sp;
}


void destroyDataSet(SET *sp)// Big O: O(1)
{
    assert(sp != NULL);
    free(sp->age);
    free(sp);
    return;
}

int searchID(SET *sp, int id) // Big O: O(1)
{
    assert(sp != NULL);
    if(sp->age[id - 1] != -1)
    {
        printf("ID: %d was Found. Age: %d \n", id, sp->age[id - 1]);
        return id;
        
    }
    
    printf("ID %d was not Found.\n", id);
    return -1;
}


void insert(SET *sp, int age, int id)// Big O: O(1)
{
    assert(id >= 1 && sp != NULL);
    sp->age[id - 1] = age;
    printf("ID %d has been added. Age: %d\n", id, age);
    return;
}

void deletion(SET *sp, int id)// Big O: O(1)
{
    assert(id > 1 && sp != NULL);
    if(sp->age[id - 1] != -1)
    { 
        sp->age[id - 1] = -1;
        printf("ID %d has been deleted.\n", id);
        return;
    }
    printf("ID %d was not deleted\n", id);
    return;
}
