/**
 * @file list.c
 * @author Brian Wiebe
 * @brief Created code for COEN 12 Lab - Week 7. This program has the capability 
 * to store words from text files so that they can be counted. This uses a hash sort
 * and an array of linked lists!
 * @version 0.1
 * @date 2022-02-20
 * @copyright Copyright (c) 2022
 */


//Declaration of Dependancies
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

//Declaration of Struct Values
typedef struct node{
    void *data; 
    struct node *next;
    struct node *prev;
}NODE;

struct list{
    int count;
    struct node *head;
    int (*compare)(); // function pointer
};

//return a pointer to a new list using compare as its comparison function, which may be NULL - O(n)
LIST *createList(int (*compare)()){
    struct list *lp;    
    lp = malloc(sizeof(struct list));    
    assert(lp != NULL);    
    lp->count = 0;    
    lp->compare = compare;    
    lp->head = malloc(sizeof(struct node));    
    assert(lp->head != NULL);    
    lp->head->next = lp->head;    
    lp->head->prev = lp->head;    
    return lp;
}

//deallocate memory associated with the list pointed to by lp - O(n)
void destroyList(LIST *lp){
    struct node *pDel, *pNext;
    assert(lp != NULL);
    pDel = lp->head;
    do {
        pNext = pDel->next;
        free(pDel);
        pDel = pNext;
    } while (pDel!= lp->head);
    free(lp);
    return;
}

//return the number of items in the list pointed to by lp - O(1)
int numItems(LIST *lp){return lp->count;}

//add item as the first item in the list pointed to by lp - O(1)
//Basis for adding values: define vars to be used, finish newNode, change next and prev, increase count
void addFirst(LIST *lp, void *item){
    assert(lp!=NULL); 
    struct node *newNode = malloc(sizeof(struct node));
    assert(newNode != NULL);
    newNode->data = item;
    newNode->prev = lp->head;
    newNode->next = lp->head->next;
    lp->head->next->prev = newNode;
    lp->head->next = newNode;
    lp->count+=1;
}

//add item as the last item in the list pointed to by lp - O(1)
void addLast(LIST *lp, void *item){
    assert(lp!=NULL);
    struct node *newNode = malloc(sizeof(struct node));
    assert(newNode != NULL);
    newNode->data = item;
    newNode->next = lp->head;
    newNode->prev = lp->head->prev;
    lp->head->prev->next = newNode;
    lp->head->prev = newNode;
    lp->count+=1;
}

//removes item as the first item in the list pointed to by lp - O(1)
void *removeFirst(LIST *lp){
    assert(lp!=NULL);
    struct node *delNode;
    void *dataDelete;
    //struct node *pastNode = lp->head->next->next;
    delNode = lp->head->next;
    dataDelete = delNode->data;
    lp->head->next->next->prev = lp->head;
    lp->head->next = lp->head->next->next;
    free(delNode);
    lp->count--;
    return dataDelete;
}

//removes item as the last item in the list pointed to by lp - O(1)
void *removeLast(LIST *lp){
    assert(lp!=NULL);
    struct node *delNode;
    void *delData;
    assert(delNode != NULL);
    delNode = lp->head->prev;
    delData = delNode->data;
    lp->head->prev = lp->head->prev->prev;
    lp->head->prev->prev->next = lp->head;
    free(delNode);
    lp->count--;
    return delData;
}

//returns first and last values in the list - O(1)
void *getFirst(LIST *lp){assert(lp!=NULL);return lp->head->next->data;}
void *getLast(LIST *lp){assert(lp!=NULL);return lp->head->prev->data;}

//removes an item from any part of the list - O(n)
void removeItem(LIST *lp, void *item){
    assert(lp!=NULL&&item!=NULL);
    struct node *locNode = lp->head->next;
    struct node *prevNode = lp->head;

    while (locNode != lp->head){
        if((*lp->compare)(locNode->data,item)==0){
            prevNode->next = locNode->next;
            locNode->next->prev = prevNode;
            free(locNode);
            lp->count--;
            return;
        }else{
            prevNode = locNode;
            locNode = locNode->next;
        }
    }
    return;
}

//returns data at specific node found in list - O(n)
void *findItem(LIST *lp, void *item){
    assert(lp!=NULL && item!=NULL);
    struct node *locNode = lp->head->next;
    while(locNode != lp->head){
        if((*lp->compare)(locNode->data,item)==0){
            return locNode->data;
        }else{
            locNode = locNode->next;
        }
    }
    return NULL;
}

//cathers all items and returns them
void *getItems(LIST *lp){
    assert(lp!=NULL);
    void **arrNodes = malloc(sizeof(void*)*lp->count);
    assert(arrNodes!=NULL);
    struct node *locNode = lp->head->next;
    int counter = 0;
    while (locNode!=lp->head){
        arrNodes[counter] = locNode->data;
        counter++;
        locNode = locNode->next;
    }
    return arrNodes;
}