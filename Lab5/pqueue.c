/*
 * File:        pqueue.c
 *
 * Author:      JT Vinolus
 * 
 * Date:        May 23 2019
 *
 * Description: This file contains the needed generic interface functions 
 *              for prj 5's priority queue.
 *
 *              
 */


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "pqueue.h"
# define elements 10;


typedef struct pqueue{
    int count;
    int length;
    void **data;
    int (*compare)();
}PQ;

int parent(int x)
{
    return (x-1)/2;
}

int left(int x)
{
    return (x*2)+1;
}

int right(int x)
{
    return (x*2)+2;
}

PQ *createQueue(int (*compare)())//Creates Queue. Big O: O(1).
{
    PQ *pq = malloc(sizeof(PQ));
    assert(pq != NULL);
    pq->compare = compare;
    pq->count = 0;
    pq->length = elements;
    pq->data = malloc(sizeof(void*)*pq->length);
    return pq;
}

void destroyQueue(PQ *pq)//Destroys Queue. Big O: O(n).
{
  assert(pq != NULL);
  for(int i = 0; i < pq->count; i++)
  {
    free(pq->data[i]);
  }
  free(pq->data);
  free(pq);
  return;
}

int numEntries(PQ *pq)//Returns Queues Count. Big O: O(1).
{
    assert(pq != NULL);
    return pq->count;
}


void addEntry(PQ *pq, void *entry)//Adds am entry to priority queue. Big O: O(log(n)).
{
	assert(pq!=NULL && entry!=NULL);
	if (pq->count == pq->length)
	{
		pq->data = realloc(pq->data,sizeof(void*)*pq->length*2);	
		pq->length = pq->length * 2;
	}
	pq->data[pq->count] = entry;									
	int index = pq->count;										
	while (pq->compare(pq->data[index], pq->data[parent(index)])<0) 
    {	
		//swap with parent
		void* temp = pq->data[parent(index)];
		pq->data[parent(index)] = pq->data[index];					
		pq->data[index] = temp;

		index=parent(index);
	}
	pq->count++;												
}

void *removeEntry(PQ *pq)//Removes priority entry from queue. Big O: O(log(n)).
{
	void* root = pq->data[0];												
	int index = 0, smallestIndex = 0;										
	pq->data[index]=pq->data[pq->count-1];									
	
															
	while (left(index)<pq->count - 1)
    {											
		smallestIndex = left(index);
		if (right(index)<pq->count - 1) 
        {											
			if (pq->compare(pq->data[left(index)],pq->data[right(index)])<0)
            {
				smallestIndex=left(index);
			} else {
				smallestIndex=right(index);
			}
		}
		
		if (pq->compare(pq->data[smallestIndex],pq->data[index])<0) 
        {		
			void* temp = pq->data[smallestIndex];
			pq->data[smallestIndex] = pq->data[index];
			pq->data[index] = temp;
			index = smallestIndex;											
		}
		else 
        {
			break;
		}
	}
    pq->count--;	
	return root;															
}
