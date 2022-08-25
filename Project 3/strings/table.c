//Declaration of dependencies
#include "set.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define EMPTY 0
#define FILLED 1
#define DELETED 2

//Declaration of Local Search Function
static int search(SET *sp, char *elt, bool *found);
//Declareation of set structure that contains the count, lenght, and data memory.
typedef struct set{
    int count;
    int length;
    char **data;
    int *flags; //Flag options include FILLED, EMPTY, DELETED
}SET;

unsigned strhash(char *s){
    unsigned hash = 0;
    while (*s != '\0')
        hash = 31 * hash + *s ++;
    return hash;
}

//creates and allocates memory for set O(1)
SET *createSet(int maxElts){
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(char*)*maxElts);
    assert(sp->data != NULL);
    sp->flags = malloc(sizeof(int)*maxElts);
    assert(sp->flags != NULL);
    int cnt;
    for(cnt=0;cnt<sp->length;cnt++){
        sp->flags[cnt]=EMPTY;
    }
    return sp;
}

//destroys set to prevent memory leaks. O(n)
void destroySet(SET *sp){
    assert(sp != NULL);
    int i;
    for(i=0; i<sp->length; i++){
        if(sp->flags[i] == FILLED){
            free(sp->data[i]);
        }
    }
    free(sp->data);
    free(sp->flags);
    free(sp);
};

//returns the number of elements currently in the array. O(1)
//returns the number of elements currently in the array. O(1)
int numElements(SET *sp){return sp->count;}

//adds the element to the last poisiton inside of the data array of a set. O(1)
void addElement(SET *sp, char *elt){
    bool found;
    int elementLoc = search(sp, elt, &found);
    if(!found){
        assert(sp->count < sp->length);
        char* copy = strdup(elt);
        assert(copy != NULL);
        sp->data[elementLoc] = copy;
        sp->flags[elementLoc] = FILLED;
        sp->count +=1;
    }
}

//removes an element that is already inside of a set's sata array and moves everything up. O(n) based off of shifting of items
void removeElement(SET *sp, char *elt){
    bool found;
    int elementLoc = search(sp, elt, &found);
    if(found){
        free(sp->data[elementLoc]);
        sp->flags[elementLoc] = DELETED;
        sp->count -= 1;
    }
}

//creates a memory allocated copy of the data inside of the set's data memory. O(n) based off of memcpy
char **getElements(SET *sp){
    char **elts;
    int i, j;
    assert(sp != NULL);
    elts = malloc(sizeof(char *) * sp->count);
    assert(elts != NULL);
    for (i = 0, j = 0; i < sp->length; i ++){
        if (sp->flags[i] == FILLED){
            elts[j ++] = sp->data[i];
        }
    }
    return elts;
}

//locates the position of an item inside of the data set. O(logn)
static int search(SET *sp, char *elt, bool *found){
    int key = strhash(elt)%sp->length;
    int linCount;
    int delLoc = -1;
    int keyFinal;
    for(linCount = 0; linCount < sp->length; linCount++){
        keyFinal = (key+linCount)%sp->length;
        //printf("%i",keyFinal);
        /*if(strcmp(sp->data[keyFinal],elt)==0){
            *found = true;
            return keyFinal;
        }else*/
         if(sp->flags[keyFinal]==EMPTY){
            if (delLoc != -1){
                *found = false;
                return delLoc;
            }
            *found = false;
            return keyFinal;
        }else if(sp->flags[keyFinal]==DELETED){
            if(delLoc == -1){
                delLoc = keyFinal;
            }
        }else if(strcmp(sp->data[keyFinal],elt)==0){
            *found = true;
            return keyFinal;
        }
    }
    *found = false;
    return delLoc;
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