/*
 * File:        Unsorted.c
 *
 * Author:      JT Vinolus
 * 
 * Date:        April 11 2019
 *
 * Description: This file contains the needed interface functions 
 *              for unique.c and parity.c with the unsorted case.
 *
 *              
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "set.h"

typedef struct set{
    int count;
    int length;
    char **data;

} SET;

static int search(SET *sp, char *elt)//Private Search Function that looks for an element sequantially in a given SET *sp.  Big O: O(n)
{
    assert(sp != NULL);
    for(int i = 0; i < sp->count; i++)
    {
        if(strcmp(elt, sp->data[i]) == 0)
        {
            return i;
        }
     }
    return -1;
}

SET *createSet(int maxElts)// Creates a structure set called sp with a variable length, variable count, and an array data.  Big O: O(1)
{
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(char *)*maxElts);
    return sp;

}

void destroySet(SET *sp)//Destroys the set starting at the strings in data, to deleting sp->data, and freeing, finally, ending with the SET sp.  Big O: O(n)
{   int i;
    assert(sp != NULL);
    for(i =0; i < sp->count; i++)
        free(sp->data[i]);
    free(sp->data);
    free(sp);
}

int numElements(SET *sp)//Returns the sp->count.  Big O: O(1)
{
    assert(sp != NULL);
    return sp->count;
}

void addElement(SET *sp, char *elt)// Asks if element is in the sp->data, and adds it if the element is not there.  Big O: O(n)
{
    assert(sp != NULL);
    if(search(sp, elt) == -1)
    {
        sp->data[sp->count] = strdup(elt);
        sp->count +=  1;
    }
}

void removeElement(SET *sp, char *elt)// Asks if element is in the sp->data, and deletes it if it is.  Big O: O(n)
{
    assert(sp != NULL);
    int idx = search(sp, elt);
    if(idx != -1)
    {   
        free(sp->data[idx]);
        sp->data[idx] = sp->data[sp->count - 1];
        sp->count -= 1;
    }
}

char *findElement(SET *sp, char *elt)//Finds an Element in Set *sp, and returns the element if it is found or false if it is not found.  Big O: O(n)
{   int idx;
    assert(sp != NULL);
    idx = search(sp, elt);
    if(idx == -1)
        return NULL;
    return sp->data[idx];
}

char **getElements(SET *sp)//Copies the Sets Data to new char **data and returns char **data.  Big O: O(n)
{
    int i;
    assert(sp != NULL);
    char **data = malloc(sizeof(char *)*(sp->count));
    for(i = 0; i <= sp->count; i++)
    {
        data[i] = sp->data[i];
    }
    return data;

}

