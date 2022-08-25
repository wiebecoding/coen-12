/**
 * @file unsorted.c
 * @author Brian Wiebe 
 * @brief Sorted Version to support finding unique words in file as well as odd occurences of words.
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
    bool found;
    int elementLoc = search(sp, elt, &found);
    if(found){
        return;
    }
    int stepUp;
    for (stepUp = sp->count; stepUp > elementLoc; stepUp--){
        sp->data[stepUp] = sp->data[stepUp-1];
    }
    sp->data[elementLoc] = strdup(elt);
    sp->count +=1;
}

//removes an element that is already inside of a set's sata array and moves everything up. O(n) based off of shifting of items
void removeElement(SET *sp, char *elt){
    bool found;
    int elementLoc = search(sp, elt, &found);
    if (!found){
        return;
    }
    free(sp->data[elementLoc]);
    int stepUp;
    for (stepUp = elementLoc; stepUp < sp->count; stepUp++){
        sp->data[stepUp] = sp->data[stepUp+1];
    }
    sp->count -= 1;
}

//creates a memory allocated copy of the data inside of the set's data memory. O(n) based off of memcpy
char **getElements(SET *sp){
    char **data = malloc(sizeof(char*)*(sp->count));
    assert(data != NULL);
    memcpy(data, sp->data, sizeof(char*)*sp->count);
    return data;
}

//locates the position of an item inside of the data set. O(logn)
static int search(SET *sp, char *elt, bool *found){
    int lo,hi,mid;
    lo = 0;
    hi = sp->count-1;

    while(lo<=hi){
        mid = (lo+hi)/2;
        if(strcmp(elt, sp->data[mid]) < 0){
            hi = mid-1;
        }else if(strcmp(elt, sp->data[mid]) > 0){
            lo = mid+1;
        }else{
            *found = true;
            return mid;
        }
    }
    *found = false;
    return lo;
}

//returns the result held inside of the array at the position resulting from a search. O(1)
char *findElement(SET *sp, char *elt){
    bool found;
    int elementLoc = search(sp, elt, &found);
    if(!found){
        return NULL;
    }
    return sp->data[elementLoc];
}