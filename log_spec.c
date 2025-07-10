/****************************************************************************/
/*                                                                          */
/* MODULE NAME : LOG_SPEC.C                                                 */
/*                                                                          */
/*                                                                          */
/* MODULE FUNCTIONALITIES :                                                 */
/*                                                                          */
/* - manage log on serial output                                            */
/*                                                                          */
/* CREATION : creation date  : 11.08.99                                     */
/*            author         : V REMY                                       */
/*            module version : V1.0                                         */
/* CHANGE:                                                                  */
/*                                                                          */
/****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "search.h"
#include "editgets.h"
#include "log_spec.h"
#include "log.h"



//FLASH_STRING_ARRAY(digits, PSTR("Zero"), PSTR("One"));

Log LogStr[] = {     /* please , follow the LOG_ENUM order */
	{"STD",STANDARD_LOG,LOG_ENABLE},
	{"ERR",ERROR_LOG,LOG_ENABLE},
	{"DBG",DEBUG_LOG,LOG_ENABLE},
	{"WAR",WARNING_LOG,LOG_ENABLE},
	{NULL,LAST_LOG_ITEM,0}
};

#include "log.c"

