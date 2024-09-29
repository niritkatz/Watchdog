/***************************************** 
 * Owner: Nirit Katz
 * Title: DS - Uniq ID
 * Reviewer: Anava
 * Last Update: 28/02/2024
 *****************************************/
#ifndef ILRD_UID_H
#define ILRD_UID_H

#include <stddef.h> /*size_t*/
#include <sys/types.h> /*pid_t*/
#include <time.h> /*time_t*/

/*******************************************************************************
The program offers functions for generating and comparing unique identifiers 
(UIDs) in C. It generates UIDs based on system time, process ID, and a counter. 
The `UIDIsEqual()' function compares UIDs for equality based on their components.
This program is valuable for ensuring data integrity, resource management, and 
unique identification across various software systems and applications.
********************************************************************************/

typedef struct ilrd_uid
{
    size_t counter;
    pid_t pid;
    time_t time;
} ilrd_uid_t;

extern const ilrd_uid_t bad_uid;

/***************************************************************************/
/*	Description: Generate UID							   */
/*	Complexity: O(1)									   */
/*	Return Value: new UID								   */
ilrd_uid_t UIDGenerate(void);

/***************************************************************************/
/*	Description: Compare between two uid's					   */
/*	Complexity: O(1)									   */
/*	Arguments: one - First uid							   */
/*		     other - Second uid						         */
/*	Return Value: Returns 1 if the uid are equal and 0 otherwise 	   */
int UIDIsEqual(ilrd_uid_t one, ilrd_uid_t other);

#endif /*ILRD_UID_H*/
