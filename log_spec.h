/****************************************************************************/
/*                                                                          */
/* MODULE NAME : LOG_SPEC.H                                                 */
/*                                                                          */
/*                                                                          */
/* MODULE FUNCTIONALITIES :                                                 */
/*                                                                          */
/* - Logging                                                                */
/*                                                                          */
/* CREATION : creation date  : 12.08.99                                     */
/*            author         : V REMY                                       */
/*            module version : V1.0                                         */
/* CHANGE:                                                                  */
/*         C.V.: changed for Board 6                                        */
/****************************************************************************/

#ifndef _LOGSPEC_H_
#define _LOGSPEC_H_

//#define LOG_ENABLE ((BOOL) 1)
//#define LOG_DISABLE ((BOOL) 0)


/*****************************************************************
* LOG_ENUM:
*		This enumeration defines the labels for Log items:
*   - STANDARD_LOG: standard log messages
		- ERROR_LOG: error log messages
		- DEBUG_LOG: debug log messages
	- LAST_LOG_ITEM: only used for enum length defining
******************************************************************/
typedef enum {
    FIRST_LOG_ITEM,
	STANDARD_LOG = FIRST_LOG_ITEM,
	ERROR_LOG,
	DEBUG_LOG,
	WARNING_LOG,
	LAST_LOG_ITEM
} LOG_ENUM;


#endif /* log_spec.h */
