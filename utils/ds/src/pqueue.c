/***************************************** 
 * Owner: Nirit Katz
 * Title: DS - Priority Queue
 * Reviewer: 
 * Last Update: 29/02/2024
 *****************************************/
 
 #include <stdlib.h> /*malloc*/
 #include <assert.h> /*assert*/
 #include "srtlist.h" /*srtlist_t*/
 
/**********************IMPLEMENTATION WITH SORT LIST****************************/
/*
 typedef struct pq
 {
 	srtlist_t *list;
 }pq_t;
 
 pq_t *PQCreate(cmp_func_t cmp_func)
 {	
 	pq_t *pq = {0};
 	
 	pq = (pq_t*)malloc(sizeof(pq_t));
 	if (NULL == pq)
 	{
 		return (NULL);
 	}
 	
 	pq->list = SrtListCreate(cmp_func);
 	if (NULL == pq->list)
 	{
 		free (pq);
 		return (NULL);
 	}
 	
 	return (pq);
 }
 
 void PQDestroy(pq_t *pq)
 {
 	assert (pq);
 	
 	SrtListDestroy(pq->list);
 	
 	free(pq);
 }
 
 int PQEnqueue(pq_t *pq, void *data)
 {
 	assert (pq);
 	
 	return SrtListIsIterSame(SrtListInsert(pq->list, data), SrtListEnd(pq->list));
 }
 
 void *PQDequeue(pq_t *pq)
 {
 	assert (pq);
 	
 	return SrtListPopFront(pq->list);
 }
 
 void *PQPeek(const pq_t *pq)
 {
 	assert (pq);
 	
 	return SrtListGetData(SrtListBegin(pq->list));
 }
 
 int PQIsEmpty(const pq_t *pq)
 {
 	assert (pq);
 	
 	return SrtListIsEmpty(pq->list);
 }
 
 size_t PQCount(const pq_t *pq)
 {
 	assert (pq);
 	
 	return SrtListCount(pq->list);
 }
 
 void *PQErase(pq_t *pq, is_match_func_t match_func, void *param)
 {	
 	srtlist_iter_t iter = SrtListFindIf(SrtListBegin(pq->list), 
 						SrtListEnd(pq->list), match_func, param);
 	void *data = SrtListGetData(iter);
 	
 	assert (pq);
					            
 	if (SrtListIsIterSame(iter, SrtListEnd(pq->list)))
 	{
 		return (NULL);
 	}
 	
 	SrtListRemove(iter);
 	return (data);
 }
 
 void PQClear(pq_t *pq)
 {
 	assert (pq);
 	
 	while (!PQIsEmpty(pq))
 	{
 		PQDequeue(pq);
 	}
 }
 */

/**********************IMPLEMENTATION WITH HEAP****************************/


#include "heap.h"
typedef int (*match_func_t)(const void *data, const void *param);

typedef struct pq 
{
    heap_t *heap;
}pq_t;

pq_t *PQCreate(cmp_func_t cmp_func)
{
    pq_t *pq = malloc(sizeof(pq_t));
    if (pq == NULL)
    {
        return NULL;
    }

    pq->heap = HeapCreate(cmp_func);
    if (pq->heap == NULL)
    {
        return NULL;
    }

    return pq;
}

void PQDestroy(pq_t *pq)
{
    assert(pq);
    HeapDestroy(pq->heap);
    free(pq);
}


int PQEnqueue(pq_t *pq, void *data)
{
    assert(pq);
    
    return (HeapPush(pq->heap, data));
}

void *PQDequeue(pq_t *pq)
{
    void *data = NULL;

	assert(pq);
	
	data = HeapPeek(pq->heap);
	HeapPop(pq->heap);

	return (data);
}

void PQPeek(const pq_t *pq)
{
    assert(pq);

    HeapPeek(pq->heap);
} 

int PQIsEmpty(const pq_t *pq)
{
    assert(pq);

    return (HeapIsEmpty(pq->heap));
} 

size_t PQCount(const pq_t *pq)
{
    assert(pq);

    return HeapSize(pq->heap);
}


void *PQErase(pq_t *pq, match_func_t match_func, void *param)
{
    assert(pq);

    return (HeapRemove(pq->heap, match_func, param));
}

void PQClear(pq_t *pq)
{
    assert(pq);

    while (!(PQIsEmpty(pq)))
	{
		PQDequeue(pq);
	}
}
