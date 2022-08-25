/**
 * @file unsorted.c
 * @author Brian Wiebe 
 * @brief 
 * @version 0.1
 * @date 2022-01-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//Declaration of dependencies
#include "set.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Declaration of Local Search Function
static int search(SET *sp, char *elt, bool *found);


//Declareation of set structure that contains the count, lenght, and data memory.
typedef struct set
{
    int count;
    int length;
    char **data;
}SET;

//creates and allocates memory for set O(1)
SET *createSet(int maxElts){
    SET *sp;

    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(char*)*maxElts);
    assert(sp->data != NULL);
    return sp;
}

//destroys set to prevent memory leaks. O(n)
void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;
    for(i=0; i<sp->count; i++){
        free(sp->data[i]);
    }
    free(sp->data);
    free(sp);
};

//returns the number of elements currently in the array. O(1)
int numElements(SET *sp){return sp->count;}

//adds the element to the last poisiton inside of the data array of a set. O(1)
void addElement(SET *sp, char *elt){
    int dupCount = search(sp, elt, false);
    if (dupCount == -1){
        sp->data[sp->count] = strdup(elt); 
        sp->count += 1;
    }
}

//removes an element that is already inside of a set's sata array and moves everything up. O(n) based off of shifting of items
void removeElement(SET *sp, char *elt){
    int elementLoc = search(sp, elt, false);
    if (elementLoc == -1){
        return;
    }
    int behind = elementLoc;
    for (int stepUp = elementLoc+1; stepUp < sp->count; stepUp++){
        sp->data[behind] = sp->data[stepUp];
    }
    sp->count -= 1;
}

//creates a memory allocated copy of the data inside of the set's data memory. O(n) based off of memcpy
char **getElements(SET *sp){
    char **data = malloc(sizeof(char*)*(sp->count));
    memcpy(data, sp->data, sizeof(char*)*sp->count);
    return data;
}

//locates the position of an item inside of the data set. O(n)
static int search(SET *sp, char *elt, bool *found){
    int max = sp->count;
    int counter;
    for(counter = 0; counter < sp->count; counter++){
        if(strcmp(sp->data[counter],elt) == 0){
            return counter;
        }
    }
    return -1;
}

//returns the result held inside of the array at the position resulting from a search. O(1)
char *findElement(SET *sp, char *elt){
    int elementLoc = search(sp, elt, false);
    if(elementLoc == -1){
        return NULL;
    }
    return sp->data[elementLoc];
}