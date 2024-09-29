/***************************************** 
 * Owner: Nirit Katz
 * Title: DS - Sort Link List
 * Reviewer: 
 * Last Update: 21/02/2024
 *****************************************/
 #include <stdlib.h> /*malloc*/
 #include <assert.h> /*assert*/
 #include "dlist.h" /*dlist_API*/
 #include "srtlist.h" /*srtlist_API*/
 
 struct srtlist
 {
 	dlist_t *list;
 	cmp_func_t cmp_func;
 };

static dlist_iter_t SrtToDListIter(srtlist_iter_t iter);
static srtlist_iter_t DListToSrtIter(dlist_iter_t iter, srtlist_t *list);
static srtlist_iter_t IterAfterVal(srtlist_t *dest, srtlist_iter_t from, void *val);

srtlist_t *SrtListCreate(cmp_func_t cmp_func)
{
	
	srtlist_t *srt_list = NULL;
	dlist_t *list = DListCreate();
	if (NULL == list)
	{
		return (NULL);
	}
	
	
	srt_list = (srtlist_t*)malloc(sizeof(srtlist_t));
	if (NULL == srt_list)
	{
		free(list);
		return (NULL);
	}
	
	srt_list->list = list;
	srt_list->cmp_func = cmp_func;
	
	return (srt_list);
}

void SrtListDestroy(srtlist_t *list)
{
	assert(list);
	
	DListDestroy(list->list);
	free(list);
}

srtlist_iter_t SrtListBegin(const srtlist_t *list)
{
	assert(list);
	
      return (DListToSrtIter(DListBegin(list->list), (srtlist_t *)list));
}

srtlist_iter_t SrtListEnd(const srtlist_t *list)
{
	assert(list);
	
      return (DListToSrtIter(DListEnd(list->list), (srtlist_t *)list));
}

srtlist_iter_t SrtListNext(srtlist_iter_t iter)
{
	iter.iter = DListNext(SrtToDListIter(iter));
	
	return (iter);
}

srtlist_iter_t SrtListPrev(srtlist_iter_t iter)
{
	iter.iter = DListPrev(SrtToDListIter(iter));
	
	return (iter);
}

int SrtListIsIterSame(srtlist_iter_t iter1, srtlist_iter_t iter2)
{
	return (DListIsIterSame(SrtToDListIter(iter1), SrtToDListIter(iter2)));
}

srtlist_iter_t SrtListInsert(srtlist_t *srtlist, void *data)
{
	srtlist_iter_t from = SrtListBegin(srtlist);
	srtlist_iter_t to = SrtListEnd(srtlist);
	
	while (!SrtListIsIterSame(from, to) && srtlist->cmp_func
   					 	         (SrtListGetData(from), data) <= 0)
	{
		from = SrtListNext(from);
	}
	
	return (DListToSrtIter(DListInsert(from.iter, data), srtlist));
}

srtlist_iter_t SrtListRemove(srtlist_iter_t to_remove)
{
	srtlist_iter_t iter = to_remove;
	
	iter.iter = DListRemove(SrtToDListIter(to_remove));

	return (iter);
}

void *SrtListGetData(srtlist_iter_t iter)
{
	return (DListGetData(SrtToDListIter(iter)));
}

size_t SrtListCount(const srtlist_t *list)
{
	assert(list);
	
	return (DListCount(list->list));
}

int SrtListIsEmpty(const srtlist_t *list)
{
	assert(list);
	
	return (DListIsEmpty(list->list));
}

srtlist_iter_t SrtListFind(srtlist_t *list, srtlist_iter_t from,
								srtlist_iter_t to, void *data)
{
	assert(list);
	assert(data);
	assert (from.list == from.list);
	
	while (!SrtListIsIterSame(from, to) && list->cmp_func
							    (SrtListGetData(from), data) < 0)
	{
		from = SrtListNext(from);
	}
	
	return (from);
}

srtlist_iter_t SrtListFindIf(srtlist_iter_t from, srtlist_iter_t to,
					            is_match_func_t is_match, void *param)
{
	assert (from.list == from.list);
	
	from.iter = DListFind(SrtToDListIter(from), SrtToDListIter(to), is_match, 
												param);
	
	return (from);
}

int SrtListForEach(srtlist_iter_t from, srtlist_iter_t to,
						     	   action_func_t action, void *param)
{
	assert (from.list == from.list);
	
	return (DListForEach(from.iter, to.iter, action, param));
}

void *SrtListPopBack(srtlist_t *list)
{
	assert(list);
	
	return (DListPopBack(list->list));
}

void *SrtListPopFront(srtlist_t *list)
{
	assert(list);
	
	return (DListPopFront(list->list));
}

void SrtListMerge(srtlist_t *dest, srtlist_t *src)
{
	srtlist_iter_t from = SrtListBegin(src);
	srtlist_iter_t to = from;
	srtlist_iter_t where = SrtListBegin(dest);
	
	while (!SrtListIsEmpty(src))
	{
		from = SrtListBegin(src);
		to = from;
		where = IterAfterVal(dest ,where, SrtListGetData(from));
		
		if (SrtListIsIterSame(where, SrtListEnd(dest)))
		{
			to = SrtListEnd(src);
		}
		else
		{
			to = IterAfterVal(src, to, SrtListGetData(where));
		}
		
		DListSplice(SrtToDListIter(from),SrtToDListIter(to), SrtToDListIter
												(where));
	}                                                        
}

/*******************************STATIC FUNCTIONS*******************************/

static dlist_iter_t SrtToDListIter(srtlist_iter_t iter)
{
	return (iter.iter);
}

static srtlist_iter_t DListToSrtIter(dlist_iter_t iter, srtlist_t *list)
{
	srtlist_iter_t srt_iter = {0};
	srt_iter.iter = iter;
	
	#ifndef NDEBUG 
   	srt_iter.list = list;
   	#endif 
    
	return (srt_iter);
}

static srtlist_iter_t IterAfterVal(srtlist_t *dest, srtlist_iter_t from, void *val)
{
	while (!SrtListIsIterSame(from, SrtListEnd(dest)) && 
		   0 >= dest->cmp_func(SrtListGetData(from), val))
	{
		from = SrtListNext(from);
	}
	
	return (from);
}
