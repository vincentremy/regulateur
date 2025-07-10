/****************************************************************************/
/*                                                                          */
/* MODULE NAME : LOG.H                                                      */
/*                                                                          */
/*                                                                          */
/* MODULE FUNCTIONALITIES :                                                 */
/*                                                                          */
/* - manage log on serial output                                            */
/*                                                                          */
/* CREATION : creation date  : 12.08.99                                     */
/*            author         : V REMY                                       */
/*            module version : V1.0                                         */
/* CHANGE:                                                                  */
/*                                                                          */
/****************************************************************************/

#ifndef _LOG_H_
#define _LOG_H_

#include "log_spec.h"
#include <arduino.h>

#define LOG_ENABLE (true)
#define LOG_DISABLE (false)

typedef struct {
	const char *Text;
	LOG_ENUM Code;
	boolean EnableFlag;
	} Log;

extern Log LogStr[];

#define LogPrintf  if(globalLog)LogPrintfLocal
#define ForceLogPrintf	LogPrintfLocal

extern unsigned char globalLog;
extern boolean IsLogItemEnable(LOG_ENUM);
extern void LogPrintfLocal(LOG_ENUM,char *,...);
extern LOG_ENUM SearchLogItem(char *);
extern void SetLog(LOG_ENUM , boolean);
extern void ListLog(void);
extern void StopGlobalLog(void);
extern void StartGlobalLog(void);

#endif /* log.h */

#ifdef AZERTY

#endif
/*---------------------------------------------- eof --------------------------------------------------*/
