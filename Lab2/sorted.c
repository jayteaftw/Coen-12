/*
 * File:        Unsorted.c
 *
 * Author:      JT Vinolus
 * 
 * Date:        April 18 2019
 *
 * Description: This file contains the needed interface functions 
 *              for unique.c and parity.c with the sorted case.
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

static int search(SET *sp, char *elt, bool *found)//Private Search Function that looks for an element sequantially in a given SET *sp. Big O: O(log(n)
{
    assert(sp != NULL);
    int lo = 0;
    int hi = sp->count - 1;
    int mid;
    int x;
    while( lo <= hi)
    {   
        mid = (lo + hi)/2;
        x = strcmp(elt, sp->data[mid]);
       
        if(x < 0)
            hi = mid - 1;
        else if(x > 0)
            lo = mid + 1;
        else
        {
            *found = true;
            return mid;
        }
        
    }
    *found = false;
    return lo;
    
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
{   
    assert(sp != NULL);
    int i;
    for(i =0; i < sp->count; i++)
        free(sp->data[i]);
    free(sp->data);
    free(sp);
}

int numElements(SET *sp)//Returns the sp->count. Big O: O(1)
{
    assert(sp != NULL);
    return sp->count;
}

void addElement(SET *sp, char *elt)// Asks if element is in the sp->data, and adds it if the element is not there.  Big O: O(n)
{
    assert(sp != NULL);
    bool found;
    int idx = 0;
    
    idx = search(sp, elt, &found);
    if(found == false)
    {
        for( int i = sp->count; i > idx; i--)
        {
            sp->data[i] = sp->data[i-1];
        }
        sp->data[idx] = strdup(elt);
        sp->count +=  1;
    }
    
}

void removeElement(SET *sp, char *elt)// Asks if element is in the sp->data, and deletes it if it is.  Big O: O(n)
{
    assert(sp != NULL);
    bool found;
    int idx = search(sp, elt, &found);
    if(found == true)
    {   
        free(sp->data[idx]);
        for(int i = idx + 1; i < sp->count; i++)
        {
            sp->data[i-1] = sp->data[i];
        }
        sp->count -= 1;
    }
    
}

char *findElement(SET *sp, char *elt)//Finds an Element in Set *sp, and returns the element if it is found or false if it is not found.  Big O: O(n)
{  
    assert(sp != NULL);
    bool found;
    int idx;
    idx = search(sp, elt, &found);
    if(found == false)
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

