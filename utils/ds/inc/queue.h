/*****************************************
 * Owner: Nirit Katz
 * Title: DS - Queue
 * Reviewer: Guy
 * Last Update: 14/02/2024
 *****************************************/
#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>/*size_t*/

typedef struct queue queue_t;

/********************************
Description: Creates a new queue
Return Value: A pointer to the new queue.
*********************************/
queue_t *QCreate();

/********************************
Description: delete the queue
Parameters:
     queue: pointer to the queue to be deleted
*********************************/
void QDestroy(queue_t *queue);

/********************************************************************************
Description: Inserts a new element with the specified data to tail of the queue.
Parameters:
     queue: pointer to the queue
     data: pointer to the data of the new element
Return Value: 0 for success, 1 for fail.
**********************************************************************************/
int QEnqueue(queue_t *queue, void *data);

/******************************************************************************
Description: Remove the head node in the queue
Parameters:
     queue: pointer to the queue
*******************************************************************************/
void QDequeue(queue_t *queue);

/*****************************************************************************
Description: return a pointer to the data of the head node 
Parameters:
     queue: pointer to the queue
Return Value: a pointer to the data
******************************************************************************/
void *QPeek(const queue_t *queue);

/**************************************************
Description: count number of elements in the queue 
Parameters:
     queue: pointer to the queue 
Return Value: number of elements in the queue
***************************************************/
size_t QCount(const queue_t *queue);

/****************************************************
Description: checks if the queue is empty or not 
Parameters:
     queue: pointer to the queue 
Return Value: 0 for success, 1 for fail.
*****************************************************/
int QIsEmpty(const queue_t *queue);

/********************************************************************
Description: append src queue to dest queue
Parameters:
     src: pointer to src queue
     dest: pointer to dest queue
warning: after excecution src queue is empty
*********************************************************************/
void QAppend(queue_t *dest, queue_t *src);

#endif /*QUEUE_H*/
