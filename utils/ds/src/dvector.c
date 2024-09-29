/***************************************** 
 * Owner: Nirit Katz
 * Title: DS - Dvector
 * Reviewer: Anava
 * Last Update: 11/02/2024
 *****************************************/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/
#include <stdio.h> /*prinf*/

#define IS_SHRINKABLE (dvector->size <= 0.25 * capacity && capacity / 2 > 0)
#define SHRINK_TRESHOLD (0.25)
#define GROWTH_TRESHOLD (0.75)
#define SHRINK_FACTOR (2)
#define GROW_FACTOR (2)

typedef struct dvector
{
	void *elements;
	size_t element_size;
	size_t capacity;
	size_t size;
}dvector_t;

enum Status 
{ 
  SUCCESS = 0, 
  FAIL 
};

static void *GetBackAddress(const dvector_t *dvector);

dvector_t *DVectorCreate(size_t capacity, size_t element_size)
{
	dvector_t *dvector= (dvector_t *)malloc(sizeof(dvector_t));
	
	assert(capacity !=  0);
	assert(element_size !=  0);
	
	if (NULL == dvector)
	{
		return (NULL);
	}

	dvector->capacity = capacity;
	dvector->element_size = element_size;
	dvector->size = 0;
	dvector->elements = malloc(capacity * element_size);
	
	if (NULL == dvector->elements)
	{	
		free(dvector);
		return (NULL);
	}

	return (dvector);
}

void DVectorDestroy(dvector_t *dvector)
{
	assert (dvector);
	
	free(dvector -> elements);
	dvector->elements = NULL;
	free(dvector);

}

int DVectorReserve(dvector_t *dvector,size_t capacity)
{
	void *temp = NULL;
	
	assert(dvector);
	
	if (capacity < (dvector->size))
	{
		capacity = dvector-> size;
	}

	temp = realloc(dvector->elements, capacity * dvector->element_size);
	if (NULL == temp)
	{	
		return (FAIL);
	}
	
	dvector->elements = temp; 
	dvector->capacity = capacity;
	
	return (SUCCESS);
}

int DVectorShrink(dvector_t *dvector)
{
	size_t capacity = dvector->capacity;
	
	assert(dvector);
	
	if (dvector->size > SHRINK_TRESHOLD * capacity)
	{	
		printf("nothing to shrink!\n");
		return FAIL;
	}
	
	if (IS_SHRINKABLE)
	{
		capacity /= SHRINK_FACTOR;
	}
	
	return (DVectorReserve(dvector, capacity));

}

void *DVectorGetAccessToElement(const dvector_t *dvector,size_t idx)
{
	assert (dvector);
	
	if (idx > (dvector->size - 1))
	{
		printf("Error: Index is out of bounds\n\n");
		return NULL;
	}

	return ((char*)GetBackAddress(dvector) - dvector->element_size*(dvector->size - idx));
}

int DVectorPushBack(dvector_t *dvector,const void *data)
{
	assert (dvector);
	
	memcpy(GetBackAddress(dvector), data, dvector->element_size);
	++(dvector -> size);
	
	if (0.75 * dvector -> capacity < dvector -> size)
	{
		DVectorReserve(dvector, (dvector->capacity) * GROW_FACTOR);
	}
	
	return(SUCCESS);
}

void DVectorPopBack(dvector_t *dvector)
{	
	assert (dvector);
	assert(dvector -> size > 0); 
	
	dvector -> size --;
	
	if (0.25 * dvector -> capacity > dvector -> size)
	{
		DVectorShrink(dvector);
	}
}


static void *GetBackAddress(const dvector_t *dvector)
{
	return (char*)dvector->elements + (dvector -> size * dvector -> element_size);
}

size_t DVectorSize(const dvector_t *dvector)
{
	assert (dvector);
	
	return (dvector -> size);
}

size_t DVectorCapacity(const dvector_t *dvector)
{
	assert (dvector);
	
	return (dvector -> capacity);
}


