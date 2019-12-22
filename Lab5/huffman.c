/*
 * File:        huffman.c
 *
 * Author:      JT Vinolus
 * 
 * Date:        May 30 2019
 *
 * Description: This file contains the needed code for prj 5's Huffman Coding.
 *
 *              
 */


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "pack.h"
#include "pqueue.h"
# include <ctype.h>



typedef struct node NODE;


static NODE* makeNode(int data, NODE* left, NODE* right);
static int depth(NODE* np);
static int nodeCompare(NODE* np1, NODE* np2);


int ascii[257];
NODE *global[257];


int main(int argc, char* argv[])//Big O: O(n)
{
    if(argc == 2)
    {
        printf("Missing or the number of required files have not been met.\n");
        return 0;
    }
    else//entering characters from file into array ascii.
    {
        FILE* fp = fopen(argv[1], "r");
        if(fp == NULL)
        {
            printf("File cannot be opened.\n");
            return 0;
        }
        int x = getc(fp);
        while(x != EOF)
        {
            ascii[x]++;
            x = getc(fp);
        }
        fclose(fp);
    }
    PQ *pq = createQueue(nodeCompare);// Creating priority queue.
    for(int i = 0; i < 256; i++)
    {
        if(ascii[i] > 0)
        {
            global[i] = makeNode(ascii[i], NULL, NULL);
            addEntry(pq, global[i]);
        }
    }
    global[256] = makeNode(0, NULL, NULL);
    addEntry(pq, global[256]);
    while(numEntries(pq) > 1)
    {
        NODE* leftNode = removeEntry(pq);
        NODE* rightNode = removeEntry(pq);
        NODE* parentNode = makeNode(leftNode->count + rightNode->count, leftNode, rightNode);
        addEntry(pq, parentNode);
    }
    for(int i = 0; i < 256; i++)
    { 
        if(global[i] != NULL)
        {
            printf(isprint(i) ? "%c" : "%03o", i);
            printf(": %d x %d bits = %d bits\n", ascii[i], depth(global[i]), ascii[i]*depth(global[i]));
        }
    }
    pack(argv[1], argv[2], global);//Calls Pack.
    destroyQueue(pq);//Destroys Queue.
    return 0;
}


static int nodeCompare(NODE* node1, NODE* node2){//return the bigger of the two nodes. Big O: O(1).
    assert(node1 != NULL && node2 != NULL);
    if(node1->count < node2->count)
        return -1;
    else if (node1->count > node2->count)
        return 1;
    else
    {
        return 0;
    }
}

static int depth(NODE* np)//Returns the depth of node. Big O: O(h).
{ 
    assert(np != NULL);
    if(np->parent == NULL)
        return 0;
    return depth(np->parent) + 1;
}

static NODE* makeNode(int data, NODE* left, NODE* right) //Big O: O(1).
{
    NODE* root = malloc(sizeof(NODE));
    assert(root != NULL);
    root->count = data;
    root->parent = NULL;
  
    if(left != NULL)
        left->parent = root;
  
    if(right != NULL)
        right->parent = root;
  
  return root;
}

