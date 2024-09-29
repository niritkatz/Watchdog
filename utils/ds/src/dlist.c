/***************************************** 
 * Owner: Nirit Katz
 * Title: DS - Double Linked List Implementation
 * Reviewer:  
 * Last Update: 19/02/2024
 *****************************************/
#include <assert.h> /*assert*/
#include <stdlib.h> /* malloc, free */
#include "../inc/dlist.h" /*DList API*/

enum status 
{ 
   NOT_FOUND = -2,
   FAIL = -1, 
   SUCCESS = 0
};

typedef struct dlist_node node_t;

struct dlist_node
{
    void *data;
    node_t *next;
    node_t *prev;
};

struct dlist
{
    node_t head;
    node_t tail;
};

static dlist_iter_t NodeToIter(node_t *node);
static node_t *IterToNode(dlist_iter_t iter);
static int AddOne(void *data, void *param);
static int IsNotInRange(dlist_iter_t from, dlist_iter_t to, dlist_iter_t who);
static dlist_iter_t GoToEnd(dlist_iter_t iter);

dlist_t *DListCreate()
{
	dlist_t *list = NULL;
	
	list = (dlist_t*)malloc(sizeof(dlist_t));
	if (NULL == list)
	{
		return (NULL);
	}
	
	list->head.next = &(list->tail);
	list->tail.prev = &(list->head);
	list->head.prev = NULL;
	list->tail.next = NULL;
	
	return (list);
	
}

void DListDestroy(dlist_t *list)
{
	dlist_iter_t head = DListBegin(list);
	dlist_iter_t next = DListNext(head);
	
	assert(list);
	
	while (DListEnd(list) != head)
	{
		free(head);
		head = next;
		next = DListNext(head);
	}

	free(list);
}

dlist_iter_t DListBegin(const dlist_t *list)
{
	assert(list);
	
	return (NodeToIter(list->head.next));
}

dlist_iter_t DListEnd(const dlist_t *list)
{
	assert(list);
	
	return (NodeToIter((dlist_iter_t)&(list->tail)));
}

dlist_iter_t DListNext(dlist_iter_t iter)
{
	node_t *node = IterToNode(iter);
	
	assert(node);
	
	return (NodeToIter(node->next));
}

dlist_iter_t DListPrev(dlist_iter_t iter)
{
	node_t *node = IterToNode(iter);
	
	assert(node);
	assert(node -> prev);
	
	return (NodeToIter(node->prev));
}

int DListIsIterSame(dlist_iter_t iter1, dlist_iter_t iter2)
{
	assert(iter1);
	assert(iter2);
	
	return (iter1 == iter2);
}

dlist_iter_t DListInsert(dlist_iter_t where, void* data)
{

	node_t *new_node = NULL;
	
	new_node = (node_t*)malloc(sizeof(node_t));
	if (!new_node)
	{
		return GoToEnd(where);
	}
	
	
	new_node -> data = data;
	new_node ->prev = where -> prev;
	new_node -> next = where;
	
	(new_node ->prev) -> next = new_node;
	where-> prev = new_node;
	
	return(NodeToIter(new_node));
}

dlist_iter_t DListRemove(dlist_iter_t to_remove)
{
	node_t *next_node = to_remove -> next;
	
	(to_remove -> prev) -> next = to_remove -> next;
	(to_remove -> next) -> prev = to_remove -> prev;
	
	free(to_remove);
	
	return(NodeToIter(next_node));
}

void *DListGetData(dlist_iter_t iter)
{
	node_t *node = IterToNode(iter);
	
	assert(node);
	
	return (node -> data);
}

void DListSetData(dlist_iter_t iter, void *data)
{
	node_t *node = IterToNode(iter);
	
	assert(node);
	assert(data);
	
	node->data = data;
}

int DListForEach(dlist_iter_t from, dlist_iter_t to, action_func_t action, void *param)
{
	size_t status = 0;
	
	assert(from);
	assert(to);
	
	while(!DListIsIterSame(from, to) && 0 == status)
	{  
		status = action(DListGetData(from), param);
		from = DListNext(from);
	}
	
	return (status);
}

size_t DListCount(const dlist_t *list)
{
	size_t param = 0;
	
	assert(list);
	
	DListForEach( DListBegin(list), DListEnd(list), AddOne, &param);
		
	return (param);
}

int DListIsEmpty(const dlist_t *list)
{
	assert(list);
	
	return DListIsIterSame(DListBegin(list), DListEnd(list));
}

dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, is_match_func_t is_match, void *param)
{
	assert(IterToNode(from));
	assert(IterToNode(to));
	
	while (!DListIsIterSame(from, to) && !is_match(DListGetData(from), param))
	{
		from = DListNext(from);
	}
	
	return (from);
}

dlist_iter_t DListPushBack(dlist_t *list, void *data)
{
	return (DListInsert(DListEnd(list),data));
}

void *DListPopBack(dlist_t *list)
{
	void *data = DListGetData(DListEnd(list)->prev);
	
	assert(list);
	
	DListRemove(DListEnd(list)->prev);
	
	return (data);
}

dlist_iter_t DListPushFront(dlist_t *list, void *data)
{
	assert(list);
	
	return (DListInsert(DListBegin(list),data));
}

void *DListPopFront(dlist_t *list)
{
	void *data = DListGetData(DListBegin(list));
	
	assert(list);
	
	DListRemove(DListBegin(list));
	
	return (data);
}

void DListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where)
{
	node_t *temp_node = where->prev;
	
	assert(from);
	assert(where);
	assert(IsNotInRange(from, to, where));
	
	(from->prev)->next = to;
	(where->prev)->next = from;
	(to->prev)->next = where;
	where->prev = to->prev;
	to->prev = from->prev;
	from->prev = temp_node;
}

int DListMultiFind(dlist_iter_t from, dlist_iter_t to, is_match_func_t is_match, void *param, dlist_t *found_elements)
{
	dlist_iter_t iter = DListEnd(found_elements);
	int status = FAIL;
	dlist_iter_t res = 0;
	
	assert(from);
	assert(to);
	assert(param);
	assert(found_elements);
	
	while (!DListIsIterSame(from, to))
	{
		if (is_match(from->data, param))
		{
			res = DListInsert(iter, from->data);
			if (DListIsIterSame(res, DListEnd(found_elements)))
			{
				return NOT_FOUND;
			}
			
			status = SUCCESS;
		}

		from = DListNext(from);
	}
	
	return (status);
}
/*******************************STATIC FUNCTION****************************/

static dlist_iter_t NodeToIter(node_t *node)
{
	return ((dlist_iter_t)node);
}

static node_t *IterToNode(dlist_iter_t iter)
{
	return ((node_t*)iter);
}

static int AddOne(void *data, void *param)
{
	(void)data;
	
	assert(param);
	
	*(int*)param += 1;
	
	return(SUCCESS);
}

static int IsNotInRange(dlist_iter_t from, dlist_iter_t to, dlist_iter_t who)
{
	while (!DListIsIterSame(from, to) && !DListIsIterSame(from, who))
	{
		from = DListNext(from);
	}
	
	return (!DListIsIterSame(from, who));
}

static dlist_iter_t GoToEnd(dlist_iter_t iter)
{	
	while (DListNext(iter))
	{
		iter = DListNext(iter);
	}
	
	return (iter);
}
