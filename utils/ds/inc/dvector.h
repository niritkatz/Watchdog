/***************************************** 
 * Owner: Nirit Katz
 * Title: DS - Dvector
 * Reviewer: Anava
 * Last Update: 11/02/2024
 *****************************************/

#ifndef DVECTOR_H
#define DVECTOR_H

#include <stddef.h> /* size_t */

typedef struct dvector dvector_t;


/*
Description: Creates a new dynamic vector with the specified capacity and element size.
Parameters:
     capacity: Maximum number elements in the initial vector.
     element_size: The size of each element in bytes.
Return Value: A pointer to the created dynamic vector (dvector_t).
*/
dvector_t *DVectorCreate(size_t capacity , size_t element_size);

/*
Description: delete the dynamic vector
Parameters:
     dvector: pointer to the relevant dynamic vector
*/
void DVectorDestroy(dvector_t *dvector);

/*
Description: return the value of the element in the specified idx
Parameters:
     dvector: pointer to the relevant dynamic vector
     idx: index in the vector
Return Value: A pointer to the value of the element in the specified idx.
*/
void *DVectorGetAccessToElement(const dvector_t *dvector, size_t idx);

/*
Description: add element at the back of the vector
Parameters:
     dvector: pointer to the relevant dynamic vector
     data: pointer to the element to be pushed to the vector
Return Value: 0 for success, 1 for fail.
*/
int DVectorPushBack(dvector_t *dvector, const void *data);

/*
Description: delete element from the back of the vector
Parameters:
     dvector: pointer to the relevant dynamic vector
*/
void DVectorPopBack(dvector_t *dvector);

/*
Description: checks the number of elements currently in the vector
Parameters:
     dvector: pointer to the relevant dynamic vector
Return Value: number of elements currently in the vector(size_t)
*/
size_t DVectorSize(const dvector_t *dvector); 

/*
Description: checks what is the maximum amount of element the vector can hold
Parameters:
     dvector: pointer to the relevant dynamic vector
Return Value: the maximum amount of element the vector can hold(size_t)
*/
size_t DVectorCapacity(const dvector_t *dvector);

/*
Description: resize the dynamic vector for a bigger capacity
Parameters:
     dvector: pointer to the relevant dynamic vector
     capacity: Maximum number of elements in the new vector.
Return Value: 0 for success, 0 for fail.
*/
int DVectorReserve(dvector_t *vdector, size_t capacity);

/*
Description: shrink the vector with capacity that is equal to double size
Parameters:
     dvector: pointer to the relevant dynamic vector
Return Value: 0 for success, 0 for fail.
*/
int DVectorShrink(dvector_t *dvector);


#endif /* DVECTOR_H */





