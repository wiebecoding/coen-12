/**
 * @file set.c
 * @author Brian Wiebe
 * @brief Created code for COEN 12 Lab - Week 7. This program has the capability 
 * to complete a radix sort as well as complete a maze.!
 * @version 0.1
 * @date 2022-02-20
 * 
 * @copyright Copyright (c) 2022
 */

//Declaration of dependencies
#include "set.h"
#include "list.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define EMPTY 0
#define FILLED 1
#define DELETED 2

typedef struct list{
    int count;
    struct node *head;
    int (*compare)();
}LIST;

//Declareation of set structure that contains the count, lenght, and data memory.
typedef struct set{
    int count;
    int length;
    LIST **lists;
    int *flags; //Flag options include FILLED, EMPTY, DELETED
    int (*compare)();
    unsigned (*hash)();
}SET;

//creates and allocates memory for set - O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL && compare != NULL && hash != NULL);
    sp->length = maxElts/20;
    sp->count = 0;
    sp->lists = malloc(sizeof(LIST*)*maxElts);
    assert(sp->lists != NULL);
    int cnt;
    for(cnt=0;cnt<sp->length;cnt++){
        sp->lists[cnt] = createList(compare);
    }
    sp->compare = compare;
    sp->hash = hash;
    return sp;
}

//destroys set to prevent memory leaks - O(1)
//TODO: Dont need to dealloc memory that has been done in other funciton.
void destroySet(SET *sp){
    assert(sp != NULL);
    free(sp->lists);
    free(sp);
};

//returns the number of elements currently in the array. O(1)
int numElements(SET *sp){assert(sp!=NULL);return sp->count;}

//adds the element to the last poisiton inside of the data array of a set. O(1)
void addElement(SET *sp, void *elt){
    assert(sp!=NULL && elt!=NULL);
    int hashValue = (sp->hash(elt)%sp->length);
    int len = sp->length;
    int hashLoc = hashValue%len;
    if(!findItem(sp->lists[hashLoc],elt)){
        addFirst(sp->lists[hashLoc],elt);
        sp->count++;
    }
}
    
//removes an element that is already inside of a set's sata array and moves everything up. O(1)
void removeElement(SET *sp, void *elt){
    assert(sp!=NULL && elt!=NULL);
    int hashValue = (sp->hash(elt)%sp->length);
    int len = sp->length;
    int hashLoc = hashValue%len;
    if(findItem(sp->lists[hashLoc],elt)!=NULL){
        removeItem(sp->lists[hashLoc],elt);
        sp->count--;
    }
    
}

//creates a memory allocated copy of the data inside of the set's data memory. O(n) based off of memcpy
void *getElements(SET *sp){
    void **elts;
    int i;
    assert(sp != NULL);
    elts = malloc(sizeof(void *) * sp->count);
    assert(elts != NULL);
    int locInElts = 0;
    for (i = 0; i < sp->length; i++){
        memcpy(elts+locInElts,getItems(sp->lists[i]),(sp->lists[i]->count)*sizeof(void *));
        locInElts += numItems(sp->lists[i]);
    }
    return elts;
}

//locates value in set - O(n)
void *findElement(SET *sp, void *elt){
    assert(sp!=NULL && elt!=NULL);
    int hashValue = (sp->hash(elt)%sp->length);
    int len = sp->length;
    int hashLoc = hashValue%len;
    if(findItem(sp->lists[hashLoc],elt) == NULL){
        return NULL;
    }
    return findItem(sp->lists[hashLoc],elt);
}
