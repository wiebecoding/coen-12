/**
 * @file pqueue.c
 * @author Brian Wiebe
 * @brief This program implements a queue stystem to store data elements as given by both huffman and pack.
 * @version 0.1
 * @date 2022-02-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//Declare dependecies

#include "pqueue.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define p(x) (((x)-1)/2)
//left and right 

typedef struct pqueue {
    int count;
    int length; 
    void **data; 
    int (*compare)();
}PQ;

//Creates a new queue for data storage
PQ *createQueue(int (*compare)()){
    PQ *newQueue;
    assert(newQueue!=NULL && compare != NULL);
    newQueue = malloc(sizeof(PQ));
    newQueue->count = 0;
    newQueue->length = 10;
    newQueue->compare = compare;
    newQueue->data = malloc(sizeof(void*)*newQueue->length); //Should this be 10? Can this be assessed by array index?
    assert(newQueue->data != NULL);
    return newQueue;
}

//frees allocated memeory from usage 
void destroyQueue(PQ *pq){
    assert(pq != NULL);
    free(pq->data);
    free(pq);
}

//Returns the length of PQ
int numEntries(PQ *pq){assert(pq!=NULL); return pq->count;} 

//adds entry of any type and reheaps.
void addEntry(PQ *pq, void *entry){
    assert(pq != NULL && entry!=NULL);
    int curCount = pq->count;
    //Check if pq is full
    if(pq->length == curCount){
        pq->length = pq->length*2;
        pq->data = realloc(pq->data, pq->length*sizeof(void*)); //Are we increasing this by one every time? //Assume that realloc keep the data within?
        assert(pq != NULL);
    }
    //inserting new data at end of binary tree
    pq->data[curCount] = entry; 
    pq->count++;
    //heaping up
    while (curCount > 0 && (*pq->compare)(entry, pq->data[p(curCount)])<0){
        void* temp = pq->data[p(curCount)]; 
        pq->data[p(curCount)] = pq->data[curCount];
        pq->data[curCount] = temp;
        curCount = p(curCount);
    }
    return;
}

//removes entry of any type and reheaps.
void *removeEntry(PQ *pq){
    assert(pq != NULL);
    int focusCount = 0;
    void *retVal = pq->data[focusCount];
    if(pq->count == 0){
        return retVal;
    }
    pq->data[focusCount] = pq->data[pq->count-1]; //pq->count-1 works esspct for zero;
    
    int count = numEntries(pq)-1;
    while (count >= 0){
        //gathers value of node's children
        int leftNode = ((focusCount) * 2 + 1);
        int rightNode = ((focusCount) * 2 + 2);
        int childChecker;
        bool leftBool = false, rightBool = false;
        //ensuring that nodes are less than the number of values
        if(leftNode < count){
            leftBool = true;
        }
        if(rightNode < count){
            rightBool = true;
        }

        //chekcing to see if there is children on right or left side
        if(count >= 0 && leftBool==true && rightBool==true){
            assert(pq->data[leftNode]!=NULL);
            if((*pq->compare)(pq->data[leftNode],pq->data[rightNode])<0){
                childChecker = leftNode;
            }else{
                childChecker = rightNode;
            }
        }else if(count >= 0 && leftBool==true && rightBool==false){
            childChecker = leftNode;
        }else{
            pq->count--;
            return retVal;
        }
        assert(pq->data[leftNode]!=NULL);
        if((*pq->compare)(pq->data[focusCount],pq->data[childChecker])<0){
            pq->count--;
            return retVal;
        }else{
            void* temp = pq->data[focusCount]; 
            pq->data[focusCount] = pq->data[childChecker];
            pq->data[childChecker] = temp;
            focusCount = childChecker;
        }
    }
    pq->count--;
    return retVal;
}