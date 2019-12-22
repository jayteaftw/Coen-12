/*
 * File:        set.c
 *
 * Author:      JT Vinolus
 * 
 * Date:        May 16 2019
 *
 * Description: This file contains the needed generic interface functions 
 *              for prj 4's unique and prarity case.
 *
 *              
 */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "list.h"
# include "set.h"
# define average 20

typedef struct set{
    int count;
    int length;
    LIST **lists;
    int(*compare)();
    unsigned (*hash)();
}SET;

int search(SET *sp, bool *found, void *elt)//Uses hash function to return index of an element.Big O: O(n)
{
    assert(sp != NULL && elt != NULL);
    int i = (*sp->hash)(elt) % sp->length; 
    if(findItem(sp->lists[i], elt) != NULL)
    {
        *found = true;
        return i;
    }
    *found = false;
    return i;
}
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())//Initializes List. Big O: O(n)
{
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->compare = compare;
    sp->count = 0;
    sp->hash = hash;
    sp->length = maxElts / average;
    sp->lists = malloc(sizeof(LIST*)*sp->length);
    for(int i = 0; i < sp->length; i++)
        sp->lists[i] = createList(sp->compare);
    return sp;
}

void destroySet(SET *sp)//Destroys Set sp. Big O: O(1)
{
    free(sp->lists);
    free(sp);
}

int numElements(SET *sp)//Returns Number of Elements in Set. Big O: O(1)
{
    assert(sp != NULL);
    return sp->count;
}

void addElement(SET *sp, void *elt)//Adds element to Set sp. Big O: O(n)
{   
    assert(sp != NULL && elt != NULL);
    bool found;
    int index = search(sp, &found, elt);
    if(found == false)
    {
        addFirst(sp->lists[index], elt);
        sp->count++;
    }
}

void removeElement(SET *sp, void *elt)//Removes Element from Set sp. Big O: O(n)
{
    assert(sp != NULL && elt != NULL);
    bool found;
    int index = search(sp, &found, elt);
    if(found == true)
    {
        removeItem(sp->lists[index], elt);
        sp->count--;
    }
}

void *findElement(SET *sp, void *elt)//Finds index of Elt. Big O: O(n)
{
    bool found;
    int index = search(sp, &found, elt);
    return findItem(sp->lists[index], elt);
}

void *getElements(SET *sp)//Returns an array of data from Set sp. Big O: O(n)
{
    assert(sp != NULL);
    int k = 0;
    void **data = malloc(sizeof(void *)*(sp->count));
    
    for(int i = 0; i < sp->length; i++)
    {
        void **items = getItems(sp->lists[i]);
        for(int j = 0; j < numItems(sp->lists[i]); j++)
        {
           data[k] = items[j];
           k++;
        }
        
    }
    
    return data;
}