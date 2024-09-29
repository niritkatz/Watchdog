/***************************************** 
 * Owner: Nirit Katz
 * Title: DS - Double Linked List Implementation
 * Reviewer:  
 * Last Update: 19/02/2024
 *****************************************/
 
#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>

typedef struct dlist dlist_t;
typedef struct dlist_node *dlist_iter_t;

/* if data and param are matched- return 1, otherwise 0*/
typedef int (*is_match_func_t)(const void *data, void *param);
/* if action function succeed- return 0, otherwise return error */
typedef int (*action_func_t)(void *data, void *param);

/***************************************************************************/
/*	Description: Creates a LinkList.						   */
/*	Complexity: O(1)								     	   */
/*	Return Value: An adress to the list.					   */	
dlist_t *DListCreate();

/***************************************************************************/
/*	Description: Free the allocation made for the list.			   */
/*	Complexity: O(1)									   */
/*	Arguments: list - the list to be freed.					   */
void DListDestroy(dlist_t *list);

/***************************************************************************/
/*	Description: Get the first element in the list.				   */
/*	Complexity: O(1)									   */
/*	Arguments: list - pointer to the list					   */
/*	Return Value: An iterator to the first node in the list.		   */
dlist_iter_t DListBegin(const dlist_t *list);

/***************************************************************************/
/*	Description: Get the last node in the list.				   */
/*	Complexity: O(1)									   */
/*	Arguments: list - pointer to the list					   */
/*	Return Value: An iterator to the last node in the list.		   */
dlist_iter_t DListEnd(const dlist_t *list);

/***************************************************************************/
/*	Description: Get the next node to your iterator.			   */
/*	Complexity: O(1)									   */
/*	Arguments: iter - an iterator pointer					   */
/*	Return Value: An iterator to the next node in the list.		   */
dlist_iter_t DListNext(dlist_iter_t iter);

/***************************************************************************/
/*	Description: Get the previous node to your iterator.			   */
/*	Complexity: O(1)									   */
/*	Arguments: iter - an iterator pointer					   */
/*	Return Value: An iterator to the previous node in the list.		   */
dlist_iter_t DListPrev(dlist_iter_t iter);

/***************************************************************************/
/*	Description: Compare the adresses of 2 iterators			   */
/*	Complexity: O(1)									   */
/*	Arguments: iter1 - First iterator pointer					   */
/*		     iter2 - Second iterator pointer			         */
/*	Return Value: Returns 1 if the adresses are the same and 0 otherwise */
int DListIsIterSame(dlist_iter_t iter1, dlist_iter_t iter2);

/*	Description: Insert a node before the iterator pointer		   */
/*	Complexity: O(1)								         */
/*	Arguments: where - an iterator pointer					   */
/*		     data  - the data to be inserted to the node		   */
/*	Return Value: Returns an iterator pointed to the new node		   */
dlist_iter_t DListInsert(dlist_iter_t where, void* data);

/***************************************************************************/
/*	Description: Remove the node pointed by an iterator			   */
/*	Complexity: O(1)									   */
/*	Arguments: to_remove - an iterator pointer to the node needed to	   */
/*		  	 		   be removed, cannot point to end node,	   */
/*	Return Value: Returns an iterator pointed to the node after the      */
/*        									removed        */
dlist_iter_t DListRemove(dlist_iter_t to_remove);

/***************************************************************************/
/*	Description: Get the data stored in the node				   */
/*	Complexity: O(1)									   */
/*	Arguments: iter - an iterator pointer					   */
/*	Return Value: Returns the data from the iterator			   */
void *DListGetData(dlist_iter_t iter);

/***************************************************************************/
/*	Description: Set data to a specific node					   */
/*	Complexity: O(1)									   */
/*	Arguments: iter - an iterator pointer					   */
/*		     data - the data to insert into the node			   */
void DListSetData(dlist_iter_t iter, void *data);

/***************************************************************************/
/*	Description: Get the number of nodes in a list				   */
/*	Complexity: O(n)									   */
/*	Arguments: list - the relevant list						   */
/*	Return Value: Returns the number of nodes in the list			   */
size_t DListCount(const dlist_t *list);

/***************************************************************************/
/*	Description: Check if the list is empty					   */
/*	Complexity: O(1)									   */
/*	Arguments: list - the relevant list						   */
/*	Return Value: Returns 1 if the list is empty and 0 otherwise	   */
int DListIsEmpty(const dlist_t *list);

/***************************************************************************/
/*	Description: Run a match function through nodes in a list		   */
/*	Complexity: O(n)									   */
/*	Arguments: from  - first node to test				         */
/*		     to    - last node to test					   */
/*		     match_func_t - a function to run through the nodes	   */
/*		     param - parameter to pass to the function			   */
/*	Return Value: Returns the node where function passed			   */
dlist_iter_t DListFind(dlist_iter_t from,
					dlist_iter_t to,
					is_match_func_t is_match,
					void *param);

/***************************************************************************/
/*	Description: Run a function through nodes in a list			   */
/*	Complexity: O(n)									   */
/*	Arguments: from  - first node to test					   */
/*			 to    - last node to test					   */
/*			 action - a function to run through the nodes		   */
/*			 param - parameter to pass to the function		   */
/*	Return Value: Return 1 if function succeed and 0 otherwise		   */
int DListForEach(dlist_iter_t from,
				dlist_iter_t to,
				action_func_t action,
				void *param);

/***************************************************************************/
/*	Description: Run a function through nodes in a list			   */
/*	Complexity: O(1)									   */
/*	Arguments: from  - first node to slice					   */
/*			 to    - last node to slice ("to"'s node is excluded)	   */
/*			 where - insert the sliced list before "where"'s node	   */
/*				   "where" iterator must not point to a node within*/
/*				   the sliced list"					   */
void DListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where);

/***************************************************************************/
/*	Description: Run a match function through nodes in a list and inserts */
/*			   all matches to a different list				    */
/*	Complexity: O(n)									    */
/*	Arguments: from  - first node to test					    */
/*			 to    - last node to test					    */
/*			 match_func_t - a function to run through the nodes	    */
/*			 param - parameter to pass to the function		    */
/*	Return Value: Returns 0 if atleast one match is found and -1 otherwise*/
int DListMultiFind(dlist_iter_t from,
				dlist_iter_t to,
				is_match_func_t is_match,
				void *param, dlist_t *found_elements);

/***************************************************************************/
/*	Description: Push a node to the end of a list.				   */
/*	Complexity: O(1)									   */
/*	Arguments: list - the relevant list						   */
/*		  	 data  - the data to be inserted to the node		   */
/*	Return Value: Returns an iterator pointed to the new node		   */
dlist_iter_t DListPushBack(dlist_t *list, void *data);

/***************************************************************************/
/*	Description: Pop a node from the end of a list.				   */
/*	Complexity: O(1)									   */
/*	Arguments: list - the relevant list						   */
/*	Return Value: Returns an iterator pointed the end of the list	   */
/*    Warning: pop from empty list is undefined					   */
void *DListPopBack(dlist_t *list);

/***************************************************************************/
/*	Description: Push a node to beginning of a list.			   */
/*	Complexity: O(1)									   */
/*	Arguments: list - the relevant list						   */
/*		  	 data  - the data to be inserted to the node		   */
/*	Return Value: Returns an iterator pointed to the new node		   */
dlist_iter_t DListPushFront(dlist_t *list, void *data);

/***************************************************************************/
/*	Description: Pop a node from the beginning of a list.			   */
/*	Complexity: O(1)									   */
/*	Arguments: list - the relevant list						   */
/*	Return Value: Returns an iterator pointed to the new first node	   */
/*    Warning: pop from empty list is undefined					   */
void *DListPopFront(dlist_t *list);


#endif /* DLIST_H */
