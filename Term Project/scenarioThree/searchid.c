/**
 * @file searchid.c
 * @author Brian Wiebe
 * @brief This is the partner set for the third senario for the term project in COEN 12.
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
# include <string.h>


//creates and allocates memory for set
SET *createDataSet(){ 
    int maxElts = 13;
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length = 13;
    sp->count = 0;
    sp->lists = malloc(sizeof(LIST*)*maxElts);
    assert(sp->lists != NULL);
    int cnt;
    for(cnt=0;cnt<sp->length;cnt++){
        sp->lists[cnt] = createList();
    }
    return sp;
}

//creates sublists
LIST *createList(){
    struct list *lp;    
    lp = malloc(sizeof(struct list));    
    assert(lp != NULL);    
    lp->count = 0;  
    lp->head = NULL;
    return lp;
}

//destroys set to prevent memory leaks.
void removeDataSet(SET *sp){
    assert(sp != NULL);
    int i;
    for(i=0;i<sp->length;i++){
        struct node* tmp;
        struct node* head = sp->lists[i]->head;
        while (head != NULL){
            tmp = head;
            head = head->next;
            free(tmp);
        }
    }
    free(sp->lists);
    free(sp);
    return;
}

//returns location of hashkey
int hashFunctionKey(record *newRecord){
    return newRecord->age;
}

//inserts record to the bottom of lists
void insertRecord(SET *sp, record *newRec){
    assert(sp!=NULL && newRec!=NULL);
    int hashValue = hashFunctionKey(newRec);
    int len = sp->length;
    int hashLoc = hashValue-18;
    NODE* newNode = malloc(sizeof(NODE));
    newNode->record = newRec;
    newNode->next = NULL;
    struct node* tmp = sp->lists[hashLoc]->head;
    if(tmp == NULL){
        sp->lists[hashLoc]->head = newNode;
        
    }else{
        assert(sp->lists[hashLoc]->head != NULL);
        while(tmp->next!= NULL){
            tmp = tmp->next;
        }
        tmp->next = newNode;
    }
    sp->lists[hashLoc]->count+=1;
    return;
}

//searches for ID in data structure
int searchID(SET *sp, record *newRecord){
    int arrayCount = sp->length;
    int mkr =0;
    printf("---------------------------------------\n");
    printf("Looking for ID: %i\n", newRecord->id, newRecord->age);
    for(mkr=0;mkr<13;mkr++){
        NODE *temp = sp->lists[mkr]->head;
        while(temp->next!= NULL){
            if(newRecord->id==temp->record->id){
                printf("The student has been found.\nThe student's id number is: %i\nThe student's age is: %i\n",temp->record->id,temp->record->age);
                printf("---------------------------------------\n");
                return (temp->record->age);
            }
            temp = temp->next;
        }
    }
    printf("No students could be found with id; %i\n",newRecord->id);
    return -1;
}

// searches for Age in data structure
int searchAge(SET *sp, record *newRecord){
    int age = newRecord->age;
    int len = sp->length;
    int hashLoc = age-18;
    int count = sp->lists[hashLoc]->count;
    
    NODE *temp = sp->lists[hashLoc]->head;
    printf("Searching for all students with age: %i\n", age);
    printf("---------------------------------------\n");
    if(count == 0){
        printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        printf("No students could be found with age; %i\n",age);
    }else if(count == 1){
        printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
        printf("1 student has been found!\n");
        printf("ID#: %i Age: %i\n",temp->record->id,temp->record->age);
    }else{
        printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
        printf("%i student has been found.\n",count);
        int prog = 0;
        while(temp->next!= NULL){
            printf("Student #%i:\n",prog);
            printf("ID#: %i Age: %i\n",temp->record->id,temp->record->age);
            temp = temp->next;
            prog++;
        }
        printf("End of Students\n");
    }
    return 1;
}

//Max Age Gap
int maxAgeGap(SET *sp){
    int minCount=-1;
    do{
        if(minCount>13){
            printf("No students");
            return -1;
        }
        minCount++;
    }while(sp->lists[minCount]->count == 0);
    
    int maxCount=14;
    do{
        if(maxCount<0){
            printf("No students");
            return -1;
        }
        maxCount--;
    }while(sp->lists[minCount]->count == 0);
    printf("Max Age Gap: %i\n", (maxCount-minCount));
    return maxCount-minCount;
}

//Deletes record
void deleRecord(SET *sp, record *newRecord){
    printf("Looking for ID value to Delete: %i\n", newRecord->id);
    int elementLoc = searchID(sp, newRecord);
    elementLoc = elementLoc -18;
    if(elementLoc < 0){
        printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        printf("Because no student was found, it can't be deleted.\n");
        return;
    }
    NODE *temp = sp->lists[elementLoc]->head;

    if(newRecord->id==temp->record->id){
        NODE *hold;
        printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");

        printf("The student has been deleted.\nThe student's id number is: %i\nThe student's age is: %i\n",temp->record->id,temp->record->age);
        hold = temp;
        temp = hold->next;
        free(hold);
        return;
    }
    
    while(temp->next!= NULL){
        if(newRecord->id==temp->next->record->id){
            printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");

            printf("The student has been deleted.\nThe student's id number is: %i\nThe student's age is: %i\n",temp->next->record->id,temp->next->record->age);
            NODE *hold = temp->next;
            temp->next = hold->next;
            free(hold);
            return;
        }
        temp = temp->next;
        
    }
    return;
}