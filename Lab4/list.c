/*
 * File:        list.c
 *
 * Author:      JT Vinolus
 * 
 * Date:        May 9 2019
 *
 * Description: This file contains the needed generic interface functions 
 *              for prj 4's maze and radix case.
 *
 *              
 */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "list.h"

typedef struct node{
    void *data;
    struct node *next;
    struct node *prev;
}NODE;

typedef struct list
{
    int count;
    struct node *head;
    int(*compare)();
}LIST;

LIST *createList(int (*compare)())//Initializes List. Big O: O(1)
{
    LIST *lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->head = malloc(sizeof(NODE));
    lp->compare = compare;
    lp->count = 0;
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    return lp;
}

void destroyList(LIST *lp)//Destroys List. Big O: O(n)
{
   assert(lp != NULL);
    NODE *pDel, *pNext;
    pDel = lp->head;

    do{
        pNext = pDel->next;
        free(pDel);
        pDel = pNext;  
    }while(pDel != lp->head);

    free(lp);
}

int numItems(LIST *lp)//Returns count of list. Big O: O(1)
{
    assert(lp != NULL);
    return lp->count;
}

void addFirst(LIST *lp, void *item)//Adds item to beginning of the list. Big O: O(1)
{
    assert(lp != NULL);
    NODE *temp = malloc(sizeof(NODE));
    assert(temp != NULL);
    temp->data = item;
   
    lp->head->next->prev = temp;
    temp->next = lp->head->next;
    temp->prev = lp->head;
    lp->head->next = temp; 
    
    lp->count++;
    return;
    
}

void addLast(LIST *lp, void *item)//Adds item to the end of the list. Big O: O(1)
{
    assert(lp != NULL && item != NULL);
    NODE *temp = malloc(sizeof(NODE));
    temp->data = item;
    
    lp->head->prev->next = temp;
    temp->next = lp->head;
    temp->prev = lp->head->prev;
    lp->head->prev = temp;
    
    lp->count++;

    return;

}

void *removeFirst(LIST *lp)//Removes first element from the list. Big O: O(1)
{
   assert(lp != NULL && lp->count > 0);
    void *item;
    NODE *pDel = lp->head->next;
    item = pDel->data;
    lp->head->next= pDel->next;
    pDel->next->prev = lp->head;
    lp->count--;
    free(pDel);
    return item;
    
}

void *removeLast(LIST *lp)//Removes last element from the list. Big O: O(1)
{
    assert(lp->head->next != lp->head);
    void *item;
    NODE *pDel = lp->head->prev;
    item = pDel->data;
    
    lp->head->prev = pDel->prev;
    pDel->prev->next = lp->head;
    
    lp->count--;
    free(pDel);
    return item;
}

void *getFirst(LIST *lp)//Retrieves first element and returns it. Big O: O(1)
{
    assert(lp->head->next != lp->head);
    return lp->head->next->data;
}

void *getLast(LIST *lp)//Retrieves last element and returns it. Big O: O(1)
{
   assert(lp->head->next != lp->head);
    return lp->head->prev->data;
}

void removeItem(LIST *lp, void *item)//Removes item from the list.  Big O: O(n)
{
    assert(lp != NULL);
    NODE *pSearch = lp->head->next;
    for(int i = 0; i < lp->count; i++)
    {
        if(lp->compare(pSearch->data, item) == 0)
        {
            pSearch->prev->next = pSearch->next;
            pSearch->next->prev = pSearch->prev;
            free(pSearch);
            lp->count--;
            break;
        }
        else
        { 
            pSearch = pSearch->next;
        }
    }
    return;
}

void *findItem(LIST *lp, void *item)//Travese list, returned item if it is the list and NUll  if it is not in the list. Big O: O(n)
{
    assert(lp != NULL);
    if(lp->count > 0)
    {   
        NODE *pSearch;
        pSearch = lp->head->next;
        
        while(pSearch != lp->head)
        {
            if((*lp->compare)(pSearch->data, item) == 0)
            {
                return pSearch->data;
            }
            pSearch = pSearch->next;

        }
     }
      
    return NULL;
}

void *getItems(LIST *lp)//Creates an array of the elements and return array. Big O: O(n)
{
    
    void **data = malloc(sizeof(void *)*(lp->count));
    int i = 0;
    NODE *pSearch = lp->head->next;
    
    while(i < lp->count)
    {
        data[i] = pSearch->data;
        pSearch = pSearch->next;
        i++;
    }
    
    return data;
}