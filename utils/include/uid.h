/* *****************************
 Name:     Alon Nov
 Exercise: unique identifier 
 Date:	   07.11.2024   
 Reviewer: Liad Tiblum

********************************/

#ifndef _UID_H_ 
#define _UID_H_

#include <sys/types.h> /* size_t, pid_t, time_t */


typedef struct unid
{
    time_t time;
    pid_t pid;
    unsigned char ip[4];
    size_t counter;
}unid_t;

extern const unid_t bad_unid;


/*@Desc - generates a UID
* @Params - N/A
* @Return - generated UID on success
* @Return - bad_uid on fail
* @Warnings - N/A
* @time complexity - O(1)  
* @Space complexity - O(1) */
unid_t UnIDGenerate(void);


/*@Desc - tests if two given UIDs are equal
* @Params - uid1: first UID to compare
* @Params - uid2: second UID to compare
* @Return - 1 (TRUE) if equal
* @Return - 0 (FALSE) if not equal
* @time complexity - O(1) 
* @Space complexity - O(1) */
int UnIDIsEqual(unid_t unid1, unid_t unid2);

#endif
