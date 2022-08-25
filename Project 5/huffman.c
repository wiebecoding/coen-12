/**
 * @file huffman.c
 * @author Brian Wiebe
 * @brief Student created code to implement hoffman coding.
 * @version 0.1
 * @date 2022-03-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//Include dependacy
#include "pqueue.h"
#include "pack.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int findDepth(struct node* node);

static int ndecmp(struct node *one, struct node *two)
{
    return one->count-two->count;
}

//implements huffman coding 
int main(int argc, char *argv[]){
    //checking argc and agrv
    if(argc != 3){
        printf("Please try again with correct inputs.");
    }
    char* fileName = argv[1];
    //opening file
    FILE *fptr;
    fptr = fopen(fileName,"r");
    //declaring needed variables for occurence
    int count[257];
    struct node* structArr[257];
    int initCount;
    //O(n)
    for(initCount=0;initCount<257;initCount++){
        count[initCount] = 0;
        structArr[initCount] = NULL;
    }
    //finding occurences of letter in text
    int buffer;
    //O(words)
    while ((buffer = fgetc(fptr)) != EOF){
        count[buffer]+=1;
    }
    //creates array of structurs and adds to queue
    int structCount;
    PQ *pq = createQueue(ndecmp);
    //O(n)
    for(structCount = 0; structCount < 257;structCount++){
        if(count[structCount]>0){
            struct node* new = malloc(sizeof(struct node));
            new->parent = NULL;
            new->count = count[structCount];
            structArr[structCount] = new;
            addEntry(pq,new);
        }
    }
    
    //Adds EOF node
    struct node* new = malloc(sizeof(struct node));
    new->parent = NULL;
    new->count = 0;
    structArr[256] = new;
    addEntry(pq, new);

    //cobmines terms in queue until one node remains. O(n)
    while(numEntries(pq) > 1){
        struct node* val1 = removeEntry(pq);
        struct node* val2 = removeEntry(pq);
        struct node* new = malloc(sizeof(struct node));
        new->parent = NULL;
        new->count = val2->count + val1->count;
        val1->parent = new;
        val2->parent = new;
        addEntry(pq, new);
    }

    //prints characters found in file. O(n)
    int printCount;
    for(printCount = 0; printCount < 257;printCount++){
        if(structArr[printCount]!=NULL){
            if(isprint(printCount)!=0){
                printf("'%c': %i x %i bits = %i bits\n",printCount,count[printCount],findDepth(structArr[printCount]),count[printCount]*findDepth(structArr[printCount]));
            }else{
                printf("%03o: %i x %i bits = %i bits\n",printCount,count[printCount],findDepth(structArr[printCount]),count[printCount]*findDepth(structArr[printCount]));
            }
        }
    }

    //inputs into pack to compress.
    pack(fileName,argv[2],structArr);

    return 1;
}   

//caluclated depth of parent node O(h)
int findDepth(struct node* node){
    if(node->parent == NULL){
        return 0;
    }
    return findDepth(node->parent)+1;
}

