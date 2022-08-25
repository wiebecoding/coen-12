# include <stdbool.h>

typedef struct record{
    int id;
    int age;
}record;

typedef struct node{
    struct record *record;
    struct node *next;
}NODE;

typedef struct list{
    int count;
    struct node *head;
}LIST;

typedef struct set{
    int count;
    int length;
    LIST **lists;
}SET;

LIST *createList();

void* generatorRecord(int prev);

SET *createDataSet();

void removeDataSet(SET *sp);

int searchAge(SET *sp, record *newRecord);
int searchID(SET *sp, record *newRecord);

void deleRecord(SET *sp, record *newRecord);

void insertRecord(SET *sp, record *newRec);

int maxAgeGap(SET *sp);