/***************************************** 
 * Owner: Nirit Katz
 * Title: DS - Heap
 * Reviewer: 
 * Last Update: 26/03/2024
 *****************************************/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include "dvector.h" /*dvector_t*/

typedef struct heap heap_t;
typedef int(*heap_cmp_func_t)(const void *data, const void *params);
typedef int(*heap_match_func_t)(const void *data, const void *params);

struct heap
{
    heap_cmp_func_t cmp_func;
    dvector_t *heap_container; 
};

typedef enum status
{
    SUCCESS = 0,
    FAILURE
} status_t;

static void HeapifyUp(heap_t *heap, size_t index);
static void HeapifyDown(heap_t *heap, size_t index);
static void Swap(size_t *val1, size_t *val2);
static size_t GetMinIdx(heap_t *heap, size_t left_idx, size_t right_idx);

heap_t *HeapCreate(heap_cmp_func_t cmp_func)
{
    heap_t *heap = (heap_t*)malloc(sizeof(heap_t));
    if (heap == NULL)
    {
        return (NULL);
    }

    heap->cmp_func = cmp_func;
    heap->heap_container = DVectorCreate(50, sizeof(void*));
    if (!heap->heap_container)
    {
        free(heap);
        return (NULL);
    }

    return (heap);
}

void HeapDestroy(heap_t *heap)
{
    assert(heap);

    DVectorDestroy(heap->heap_container);
    heap->heap_container = NULL;
    
    free(heap);
}

status_t HeapPush(heap_t *heap, void *data)
{
    status_t status = SUCCESS;
    size_t size = 0;

    assert(heap);

    status = DVectorPushBack(heap->heap_container, &data);
    size = DVectorSize(heap->heap_container);

    if (status != SUCCESS)
    {
        return (FAILURE);
    }
    
    if (size - 1 > 0)
    {
        HeapifyUp(heap, size - 1);
    }
    
    return (status);
}

void *HeapPeek(const heap_t *heap)
{
    void **data = NULL;

    assert(heap);

    if (0 == DVectorSize(heap->heap_container))
    {
        return (NULL);
    }
    data = DVectorGetAccessToElement(heap->heap_container, 0);

    return (*data);
}

void HeapPop(heap_t *heap)
{
    size_t size = 0;

    assert(heap);

    size = DVectorSize(heap->heap_container);

    if( size != 0)
    {
        Swap(DVectorGetAccessToElement(heap->heap_container, 0), DVectorGetAccessToElement(heap->heap_container, size-1));
        DVectorPopBack(heap->heap_container);
        HeapifyDown(heap, 0);
    }
}

size_t HeapSize(const heap_t *heap)
{
    return (DVectorSize(heap->heap_container));
}

void *HeapRemove(heap_t *heap, heap_match_func_t match_func, const void *params)
{
    size_t size = 0, i = 0;
    void **to_remove = NULL, **last_data = NULL, **parent_data = NULL;
    
    assert(heap);

    size = HeapSize(heap);
    last_data = DVectorGetAccessToElement(heap->heap_container, size-1);

    for (i=0; i < size; i++)
    {
        to_remove = DVectorGetAccessToElement(heap->heap_container, i);
        if (match_func(*to_remove, params))
        {
            if (i == 0)
            {
                HeapPop(heap);
                return (to_remove);
            }

            else
            {
                Swap((void*)to_remove, (void*)last_data);
                
                parent_data = DVectorGetAccessToElement(heap->heap_container, (i-1)/2); 
                if (*to_remove >= *parent_data)
                {
                    HeapifyDown(heap, i);
                }

                else
                {
                    HeapifyUp(heap, i);
                }
                
                DVectorPopBack(heap->heap_container);

                return(to_remove);
            }    
        }
    }
    return (NULL);
}

int HeapIsEmpty(const heap_t *heap)
{
    return (DVectorSize(heap->heap_container) == 0);
}

/*****************************STATIC FUNCTION***********************************/

static void HeapifyUp(heap_t *heap, size_t curr_index)
{
    int parent_idx = 0;
    void **new_data = NULL, **parent_data = NULL;

    assert(heap);

    parent_idx = (curr_index-1)/2;
    new_data = DVectorGetAccessToElement(heap->heap_container, curr_index);
    
    while (parent_idx >= 0 && parent_idx != (int)curr_index)
    {
        parent_data = DVectorGetAccessToElement(heap->heap_container, parent_idx);
        if (heap->cmp_func(*parent_data, *new_data) < 0 )
        {
            return;
        }

        Swap((void*)parent_data, (void*)new_data);
        new_data = DVectorGetAccessToElement(heap->heap_container, parent_idx);

        if (parent_idx == 0)
        {
            return;
        }
        parent_idx = (parent_idx -1)/2;
    }
}

static void HeapifyDown(heap_t *heap, size_t curr_index)
{
    size_t left_idx = 0, right_idx = 0, min_child_idx = 0;
    size_t size = 0;
    void **curr_data = NULL, **child_data = NULL;
    int flag = 1;

    assert (heap);

    curr_data = DVectorGetAccessToElement(heap->heap_container, 0);
    size = DVectorSize(heap->heap_container);

    left_idx = 2*curr_index + 1;
    right_idx = 2*curr_index + 2;

    while (left_idx < size && flag)
    {
        if (right_idx >= size)
        {
            min_child_idx = left_idx;
        }

        else
        {
            min_child_idx = GetMinIdx(heap, left_idx, right_idx);
        }
        
        child_data = DVectorGetAccessToElement(heap->heap_container, min_child_idx);

        if (heap->cmp_func(*child_data, *curr_data) >= 0)
        {
            return;
        }

        Swap((void*)child_data, (void*)curr_data);

        curr_index = min_child_idx;
        curr_data = DVectorGetAccessToElement(heap->heap_container, curr_index);
        left_idx = 2*curr_index + 1;
        right_idx = 2*curr_index + 2;
    }
}

static size_t GetMinIdx(heap_t *heap, size_t left_idx, size_t right_idx)
{
    void **data_left = 0, **data_right = 0;

    assert(heap);

    data_left = DVectorGetAccessToElement(heap->heap_container, left_idx);
    data_right = DVectorGetAccessToElement(heap->heap_container, right_idx);

    return (heap->cmp_func(*data_right, *data_left) > 0 ? left_idx : right_idx);
}

static void Swap(size_t *val1, size_t *val2)
{
    size_t temp = *val1;
    *val1 = *val2;
    *val2 = temp;
}




