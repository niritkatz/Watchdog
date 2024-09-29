/*****************************************
 * Owner: Nirit Katz
 * Title: DS - Queue
 * Reviewer: Guy
 * Last Update: 14/02/2024
 *****************************************/
#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include "../inc/queue.h" /*queue API*/
#include "../inc/slist.h" /*slist API*/

struct queue
{
	slist_t *list;
};

queue_t *QCreate()
{
	queue_t *queue = NULL;
	
	queue = (queue_t*)malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		return NULL;
	}
	
	queue -> list = SListCreate();
	
	return (queue);
}
void QDestroy(queue_t *queue)
{
	assert(queue);
	
	SListDestroy(queue -> list);
	
	free(queue);
}
int QEnqueue(queue_t *queue, void *data)
{
	slist_iter_t iter_end = SListEnd(queue->list);
	
	assert(queue);
	assert(data);
	
	return (iter_end == SListInsert(iter_end, data));
}
void QDequeue(queue_t *queue)
{
	assert(queue);
	
	SListRemove(SListBegin(queue->list));
}
void *QPeek(const queue_t *queue)
{
	assert(queue);
	
	return (SListGetData(SListBegin(queue->list)));
}
size_t QCount(const queue_t *queue)
{
	assert(queue);
	
	return (SListCount(queue->list));
}
int QIsEmpty(const queue_t *queue)
{
	assert(queue);
	
	return (SListIsEmpty(queue->list));
}
void QAppend(queue_t *dest, queue_t *src)
{
	assert(dest);
	assert(src);
	
	SListAppend(dest->list, src->list);
}
