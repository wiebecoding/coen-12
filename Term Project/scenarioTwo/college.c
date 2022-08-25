/**
 * @file college.c
 * @author Brian Wiebe
 * @brief This is the implementation of the second application as defined below
 * Assume  that  the  college  takes  very  few  transfer  students  and  has  most  of  its  students  stay  for  at  least  one  year 
 * (Hints:  no  frequent  insertion  and  deletion  operations).  And  the  maximum  student  number  is  given.  But  it  does 
 * require a lot of search operations. Specifically, all of the searches are based on student  IDs. 
 * 
 * For the second scenario, I will be using a hash table system to search through the student IDs.
 * Because of the high search frequency, the hash table provides an expected search time of O(1). 
 * I will be using quadratic probing because of the fact that there will not be duplicate id numbers. 
 * Because there is no requirement for max age gap, we don't have to worry about such an iteration.
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <time.h>
# include "college.h"

#define numStudents 3000

//Declareation of set structure that contains the count, lenght, and data memory.

int main(){
    //creates records
    srand(time(0));
    SET *sp;
    sp = createDataSet(numStudents);
    int recordCountInit;
    int prev = 0;
    for (recordCountInit = 0; recordCountInit < 1000; recordCountInit++){
        record *newRecord = generatorRecord(prev);
        prev = newRecord->id;
        insertRecord(sp, newRecord);
    }
    //finds record
    int idBase = rand()%1998 + 1;
    bool found;
    int foundRecord = searchRecords(sp, idBase, &found);

    //deletes record
    int idBaseDel = rand()%1998 + 1;
    printf("Student Delete #: %i\n",idBaseDel);
    deleRecord(sp, idBaseDel);
    //removes data set
    removeDataSet(sp);
}

//generates records to be inputed.
void* generatorRecord(int prev){
    record *newRecord = malloc(sizeof(record));
    int age = rand()%13 + 18;
    int idPre = rand()%2 + 1;
    newRecord->id = idPre + prev;
    newRecord->age = age;
    return newRecord;
}