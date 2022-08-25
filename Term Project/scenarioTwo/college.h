# include <stdbool.h>

typedef struct record{
    int id;
    int age;
} record;

typedef struct set{
    int count;
    int length;
    record **data;
}SET;

void* generatorRecord(int prev);

SET *createDataSet(int maxElts);

void removeDataSet(SET *sp);

int searchRecords(SET *sp, int id, bool *found);

void insertRecord(SET *sp, record *newRecord);

void deleRecord(SET *sp, int id);