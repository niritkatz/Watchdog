/***************************************** 
 * Owner: Nirit Katz
 * Title: DS - Sort Link List
 * Reviewer: 
 * Last Update: 21/02/2024
 *****************************************/
#ifndef SRTLIST_H
#define SRTLIST_H

#include <stddef.h> /*size_t*/
#include "dlist.h" /*dlist_API*/

/****************************************************************************/
/* The structure of an ordered list is a collection of items where each item*/
/* holds a relative position. The ordering is typically either ascending or */
/* descending and we assume that list items have a meaningful comparison    */
/* operation that is already defined.						    */
/****************************************************************************/

/****************************************************************************/
/* Callback function for sorting the list						    */
/* Returns negative positive or zero integer    		                */
typedef int (*cmp_func_t)(const void *data, const void *param);

typedef struct srtlist srtlist_t;

typedef struct srtlist_iter
{
    dlist_iter_t iter;
    #ifndef NDEBUG 
    const srtlist_t *list;
    #endif 
} srtlist_iter_t;   

/***************************************************************************/
/*	Description: Creates a Sort List.						   */
/*	Complexity: O(1)								     	   */
/*	Return Value: An adress to the list.					   */	
srtlist_t *SrtListCreate(cmp_func_t cmp_func);

/***************************************************************************/
/*	Description: Free the allocation made for the list.			   */
/*	Complexity: O(1)									   */
/*	Arguments: list - pointer to the list to be freed.			   */
void SrtListDestroy(srtlist_t *list);

/***************************************************************************/
/*	Description: Get the first element in the list.				   */
/*	Complexity: O(1)									   */
/*	Arguments: list - pointer to the list					   */
/*	Return Value: An iterator to the first node in the list.		   */
srtlist_iter_t SrtListBegin(const srtlist_t *list);

/***************************************************************************/
/*	Description: go to end of list		.				   */
/*	Complexity: O(1)									   */
/*	Arguments: list - pointer to the list					   */
/*	Return Value: An iterator to end of list					   */
srtlist_iter_t SrtListEnd(const srtlist_t *list);

/***************************************************************************/
/*	Description: Get the next node to your iterator.			   */
/*	Complexity: O(1)									   */
/*	Arguments: iter - an iterator pointer					   */
/*	Return Value: An iterator to the next node in the list.		   */
srtlist_iter_t SrtListNext(srtlist_iter_t iter);

/***************************************************************************/
/*	Description: Get the previous node to your iterator.			   */
/*	Complexity: O(1)									   */
/*	Arguments: iter - an iterator pointer					   */
/*	Return Value: An iterator to the previous node in the list.		   */
srtlist_iter_t SrtListPrev(srtlist_iter_t iter);

/***************************************************************************/
/*	Description: Compare the adresses of 2 iterators			   */
/*	Complexity: O(1)									   */
/*	Arguments: iter1 - First iterator pointer					   */
/*		     iter2 - Second iterator pointer			         */
/*	Return Value: Returns 1 if the adresses are the same and 0 otherwise */
int SrtListIsIterSame(srtlist_iter_t iter1, srtlist_iter_t iter2);

/***************************************************************************/
/*	Description: Insert a node before the iterator pointer		   */
/*	Complexity: O(n)								         */
/*	Arguments: where - an iterator pointer					   */
/*		     data  - the data to be inserted to the node		   */
/*	Return Value: Returns an iterator pointed to the new node		   */
/*	Warning: when fail return end of list					   */
srtlist_iter_t SrtListInsert(srtlist_t *srtlist, void *data); 

/***************************************************************************/
/*	Description: Remove the node pointed by an iterator			   */
/*	Complexity: O(1)									   */
/*	Arguments: to_remove - an iterator pointer to the node needed to	   */
/*		  	 		   be removed, cannot point to end of list   */
/*	Return Value: Returns an iterator pointed to the node after the      */
/*        									removed        */
srtlist_iter_t SrtListRemove(srtlist_iter_t to_remove);

/***************************************************************************/
/*	Description: Get the data stored in the node				   */
/*	Complexity: O(1)									   */
/*	Arguments: iter - an iterator pointer					   */
/*	Return Value: Returns the data from the iterator			   */
void *SrtListGetData(srtlist_iter_t iter);

/***************************************************************************/
/*	Description: Get the number of nodes in the list		         */
/*	Complexity: O(n)									   */
/*	Arguments: list - the relevant list						   */
/*	Return Value: Returns the number of nodes in the list			   */
size_t SrtListCount(const srtlist_t *list);

/***************************************************************************/
/*	Description: Check if the list is empty					   */
/*	Complexity: O(1)									   */
/*	Arguments: list - the relevant list						   */
/*	Return Value: Returns 1 if the list is empty and 0 otherwise	   */
int SrtListIsEmpty(const srtlist_t *list);

/***************************************************************************/
/*	Description: Finds the first occurrence of an element in the	   */
/*				specified range that matches the given data.       */
/*	Complexity: O(n)									   */
/*	Arguments: list - the relevant list						   */
/*		     from  - first node to test				         */
/*		     to    - last node to test					   */
/*		     data - pointer to the data to be found.		 	   */
/*	Return Value: Iterator pointing to the first matching element	   */		
srtlist_iter_t SrtListFind(srtlist_t *list, srtlist_iter_t from,
					srtlist_iter_t to,
					void *data);

/***************************************************************************/
/*	Description: Run a match function through nodes in a list		   */
/*	Complexity: O(n)									   */
/*	Arguments: from  - first node to test				         */
/*		     to    - last node to test					   */
/*		     is_match_func_t - a function to run through the nodes	   */
/*		     param - parameter to pass to the function			   */
/*	Return Value: Iterator pointing to the first matching element	   */
srtlist_iter_t SrtListFindIf(srtlist_iter_t from,              
					srtlist_iter_t to,
					is_match_func_t is_match,
					void *param);

/***************************************************************************/
/*	Description: Run a function through nodes in a list			   */
/*	Complexity: O(n)									   */
/*	Arguments: from  - first node to test					   */
/*		     to    - last node to test					   */
/*		     action - a function to run through the nodes		   */
/*		     param - parameter to pass to the function		  	   */
/*	Return Value: Return 1 if function succeed and 0 otherwise		   */
/*	Warning: Using the function may defect the sort				   */
int SrtListForEach(srtlist_iter_t from,                     
				srtlist_iter_t to,
				action_func_t action,
				void *param);

/***************************************************************************/
/*	Description: Pop a node from the end of a list.				   */
/*	Complexity: O(1)									   */
/*	Arguments: list - the relevant list						   */
/*	Return Value: Returns an iterator pointed to end of the list	   */
/*    Warning: pop from empty list is undefined					   */
void *SrtListPopBack(srtlist_t *list);

/***************************************************************************/
/*	Description: Pop a node from the beginning of a list.			   */
/*	Complexity: O(1)									   */
/*	Arguments: list - the relevant list						   */
/*	Return Value: Returns an iterator pointed to the new first node	   */
/*    Warning: pop from empty list is undefined					   */
void *SrtListPopFront(srtlist_t *list);

/***************************************************************************/
/*	Description:  Merges two sorted linked lists into a single sorted 
			linked list in dest address. src list remain empty	   */
/*	Complexity: O(n)									   */
/*	Arguments: dest - A pointer to the destination list			   */
/*		     src- A pointer to the source list		 		   */
void SrtListMerge(srtlist_t *dest, srtlist_t *src);        

#endif /* SRTLIST_H */
