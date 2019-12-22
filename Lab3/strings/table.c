 /*
 * File:        table.c
 *
 * Author:      JT Vinolus
 * 
 * Date:        May 1 2019
 *
 * Description: This file contains the needed interface functions 
 *              for prj 3's string case.
 *
 *              
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "set.h"

#define FILLED 2 
#define DELETED 1
#define EMPTY 0 

typedef struct set{
    int count;
    int length;
    char **data;
    char *flag;

} SET;

unsigned strhash(char *s) 
{
    unsigned hash = 0;
    while (*s != '\0')
        hash = 31 * hash + *s ++;
    return hash;
}

int search(SET *sp, char *elt, bool *found)//Function retrieves an element and searches for the elements in sp->data. If the element doesn't exist, the function returns the proper index and that found is false. Else, the fuction returns found is true and the index of the element. Big O: O(m)
{
    assert(elt != NULL && sp != NULL);
    int idx, start;
    int a = 0;
    int Bmark = 0;
    int flag = 0;
    idx =  strhash(elt)%(sp->length);
    start = idx;
    idx++;
    idx = idx % sp->length;
    while(idx != start)
    {
        if(sp->flag[idx] == 0 )
        {
            if(flag == 0)
            {
                *found = false;
                return idx;
            }
            break;
        }
        else if(sp->flag[idx] == 2)
        {
            if(strcmp(elt, sp->data[idx]) == 0)
            {
                *found = true;
                return idx;
            } 
        }
        else //sp->flag[i] == 1
        {
            if(flag == 0)
            {
                flag = 1;
                Bmark = idx;
            }
        } 
        idx++;
        idx = idx % sp->length;//index circles backs to the beginning.  
    }
    *found = false;
    return Bmark;
}

SET *createSet(int maxElts)// Creates a structure set called sp with a variable length, variable count, and an array data.  Big O: O(1)
{   int i;
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(char *)*maxElts);
    sp->flag = malloc(sizeof(char )*maxElts);
    for(i = 0; i < maxElts; i++)
    {
        sp->flag[i] = 0;
    }
    return sp;
}

void destroySet(SET *sp)//Frees all pointers in SET. Big O: O(m)
{
    assert(sp != NULL);
    int i;
    for(i =0; i < sp->length; i++)
    {  
        if(sp->flag[i] == 2)
        {
            free(sp->data[i]);  
        }
    }
    free(sp->flag);
    free(sp->data);
    free(sp);
}

int numElements(SET *sp)// Returns number of elements. Big O: O(1)
{
    assert(sp != NULL);
    return sp->count;

}

void addElement(SET *sp, char *elt)// Adds an element to sp->data if element is not found. Big O: O(m)
{
    assert(sp != NULL);
    bool found;
    int idx;
    idx = search(sp, elt, &found);
    if(found == false)
    {
        sp->data[idx] = strdup(elt);
        sp->flag[idx] = 2;
        sp->count +=  1;
    }
    
}

void removeElement(SET *sp, char *elt)//Removes element in sp->data if element is found. Big O: O(m)
{
    assert(sp != NULL);
    bool found;
    int idx;
    idx = search(sp, elt, &found);
    if(found == true)
    {   
        free(sp->data[idx]);
        sp->flag[idx] = 1;
        sp->count -= 1;
    }
}

char *findElement(SET *sp, char *elt)//Takes an element and returns NULL if the element is not there and returnsthe element if it is there. Big O: O(m)
{
    assert(sp != NULL);
    bool found;
    int idx;
    idx = search(sp, elt, &found);
    if(found == false)
        return NULL;
    return sp->data[idx];
}

char **getElements(SET *sp)//Creates, copies and returns only the filled data in sp->data. Big O: O(m)
{
     int i;
     int j;
    assert(sp != NULL );
    char **data = malloc(sizeof(char *)*(sp->count));
    for(i = 0, j = 0; i <= sp->length; i++)
    {
        if(sp->flag[i] == 2)
        {
            data[j] = sp->data[i];
            j++;
        }
     
    }
    return data;
}
