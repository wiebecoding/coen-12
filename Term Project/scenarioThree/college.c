/**
 * @file college.c
 * @author Brian Wiebe
 * @brief Assume  a  new  college  that  is  expanding  frequently  and  dramatically  on  its  student  amount.  This  leads  to  two 
 * consequences.  First,  accurately  estimating  the  total  number  of  students  is  extremely  difficult.  Second,  frequent 
 * insertions and deletions are performed. In addition, the college frequently requires calculating the largest age gap 
 * among  its  students.  Assume  that  search  operations  are  not  performed  frequently.  Your  implementation  has  to 
 * support  searches  on  either  student  ID  or  age.  The  major  interfaces  provided  by  your  code  should  include 
 * createDataSet, destroyDataSet, searchAge, searchID, insertion, deletion, maxAgeGap. 
 * 
 * For the third scenario, I will be using a hask table chaining with singly linked lists. This allows
 * the data structure to be variable in storage size because there is no need to change previously allocated
 * memory. This also allows the MaxAgeGap funciton to occur in a simple way because they are ordered by age.
 * Because I had to both search for age and ID, I knew that one of them was going to be disadvatages with the 
 * O(n) runtime. Thus, I selected the id to have this downside so that the MaxAgeGap could be acheived.
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


int main(){
    //create values
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
    
    //searching values
    int idBase = rand()%1998 + 1;
    record *newRec = generatorRecord(idBase);
    int foundRecord2 = searchAge(sp, newRec);
    int foundRecord1 = searchID(sp, newRec);
    
    //delete records
    int idBaseDel = rand()%1998 + 1;
    record *newRecDel = generatorRecord(idBaseDel);
    deleRecord(sp, newRecDel);
    
    //age gap
    int ageGap = maxAgeGap(sp);
    removeDataSet(sp);
    
}

//generates 
void* generatorRecord(int prev){
    record *newRecord = malloc(sizeof(record));
    int age = rand()%13 + 18;
    int idPre = rand()%2 + 1;
    newRecord->id = idPre + prev;
    newRecord->age = age;
    return newRecord;
}