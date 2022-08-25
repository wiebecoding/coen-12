/*
 * File:	list.h
 *
 * Copyright:	2021, Darren C. Atkinson
 *
 * Description:	This file contains the public function and type
 *		declarations for a list abstract data type for generic
 *		pointer types.  The list supports deque operations, in
 *		which items can be easily added to or removed from the
 *		front or rear of the list.
 */

# ifndef LIST_H
# define LIST_H


typedef struct list LIST;

LIST *createList(int (*compare)());

void destroyList(LIST *lp);

int numItems(LIST *lp);

void addFirst(LIST *lp, void *item);

void addLast(LIST *lp, void *item);

void *removeFirst(LIST *lp);

void *removeLast(LIST *lp);

void *getFirst(LIST *lp);

void *getLast(LIST *lp);

void removeItem(LIST *lp, void *item);

void *findItem(LIST *lp, void *item);

void *getItems(LIST *lp);

# endif /* LIST_H */
