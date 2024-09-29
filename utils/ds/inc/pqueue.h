/***************************************** 
 * Owner: Nirit Katz
 * Title: DS - Priority Queue
 * Reviewer: 
 * Last Update: 29/02/2024
 *****************************************/
 
#ifndef P_Q
#define P_Q

#include <stddef.h> /* size_t */

typedef int (*cmp_func_t)(const void *data, const void *param);
typedef int (*is_match_func_t)(const void *data, void *param);
typedef struct pq pq_t;

/******************************************************************
Description: Creates a new priority queue
Parameters:
     cmp_func: function that defines the rule of priority
Return Value: A pointer to the new priority queue.
Complexity: O(1)
******************************************************************/
pq_t *PQCreate(cmp_func_t cmp_func); 

/******************************************************************
Description: Destroy the priority queue
Parameters:
     pq: pointer to the relevant queue
Complexity: O(n)
******************************************************************/
void PQDestroy(pq_t *pq); 

/******************************************************************
Description: Inserts a new element with the specified data to tail 
		 of the queue.
Parameters:
     pq: pointer to the relevant queue
     data: pointer to the data of the new element
Return Value:  0 for success, 1 for fail.
Complexity: O(n)
******************************************************************/
int PQEnqueue(pq_t *pq, void *data); 

/******************************************************************
Description: Remove the head node in the queue
Parameters:
     pq: pointer to the relevant queue
Return Value: data of the removed node
Complexity: O(1)
******************************************************************/
void *PQDequeue(pq_t *pq);

/******************************************************************
Description: return a pointer to the data of the head node 
Parameters:
     pq: pointer to the relevant queue
Return Value: data of the head node
Complexity: O(1)
******************************************************************/
void *PQPeek(const pq_t *pq); 

/******************************************************************
Description: checks if the queue is empty
Parameters:
     pq: pointer to the relevant queue
Return Value: 1 when empty, 0 otherwise
Complexity: O(1)
******************************************************************/
int PQIsEmpty(const pq_t *pq); 

/******************************************************************
Description: count number of elements in the priority queue 
Parameters:
     pq: pointer to the relevant queue
Return Value: number of elements in the queue
Complexity: O(n)
******************************************************************/
size_t PQCount(const pq_t *pq); 

/******************************************************************
Description:  Find the first occurence of an object based on a 
		  custom sorting method
Parameters:
     pq: pointer to the relevant queue
     match_func: a function to define matching rule
     param: parameter to pass to the function
Return Value: Returns the first ocurrence of an object
Complexity: O(n)
******************************************************************/
void *PQErase(pq_t *pq, is_match_func_t match_func, void *param);

/******************************************************************
Description: Clears the queue from elements
Parameters:
     pq: pointer to the relevant queue
Return Value: pointer to the queue
Complexity: O(n)
******************************************************************/
void PQClear(pq_t *pq); 

#endif /* P_Q */

