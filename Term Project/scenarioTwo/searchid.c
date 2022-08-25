/**
 * @file searchid.c
 * @author Brian Wiebe
 * @brief This is the partner file to college.c for the second situation 
 * for COEN 12 (Winter Quarter)
 * @version 0.1
 * @date 2022-03-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

# include "college.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <stdbool.h>

//creates and allocates memory for set 
SET *createDataSet(int maxElts){
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(record*)*maxElts);
    assert(sp->data != NULL);
    return sp;
}

//destroys set to prevent memory leaks. 
void removeDataSet(SET *sp){
    assert(sp != NULL);
    int i;
    for(i=0; i<sp->count; i++){
        free(sp->data[i]);
    }
    free(sp->data);
    free(sp);
    return;
}

//returned the hashing key
int hashFunctionKey(record *newRecord){
    return newRecord->id;
}

//compared ids
bool recordCompare(int idOne, int idTwo){
    if(idOne == idTwo){
        return true;
    }else{
        return false;
    }
}

// inserts record into array
void insertRecord(SET *sp, record *newRecord){
    int keyLoc = hashFunctionKey(newRecord);
    sp->data[keyLoc] = newRecord;
    sp->count+=1;
    return;
}

//searches for records in the hash table
int searchRecords(SET *sp, int id, bool *found){
    printf("Student Search #: %i\n",id);
    int key = id;
    if(sp->data[key] != NULL){
        int key2 = sp->data[key]->id;
        if(recordCompare(key2,id)==true){
            record *locatedRecord = sp->data[key];
            printf("The student has been found!\nThe student's id number is: %i\nThe student's age is: %i\n",locatedRecord->id,locatedRecord->age);
            *found = true;
            return key;
        }else{
            printf("The student has not been found!\n");
            *found = false;
            return -1;
        }
    }else{
        printf("The student has not been found!\n");
        *found = false;
        return -1;
    }
    
}

//removed record in hash table.
void deleRecord(SET *sp, int id){
    bool found;
    int elementLoc = searchRecords(sp, id, &found);
    if(found){
        printf("The student has been deleted!\nThe student's id number is: %i\nThe student's age is: %i\n",sp->data[elementLoc]->id,sp->data[elementLoc]->age);
        free(sp->data[elementLoc]);
        sp->count -= 1;
    }else{
        printf("The student has not been deleted!\n");
    }
    return;
}