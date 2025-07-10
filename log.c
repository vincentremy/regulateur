/****************************************************************************/
/*                                                                          */
/* MODULE NAME : LOG.C                                                      */
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
#include "log.h"

unsigned char globalLog;


void ListLog(void)
{
	unsigned char i;
	Serial.print("\nList of Items logged :");
//	printf("\nList of Items logged :");
	for (i = FIRST_LOG_ITEM;i < LAST_LOG_ITEM; i++)
	{
		printf("\n%s:%02d ",LogStr[i].Text,LogStr[i].EnableFlag);
	}
	printf("\n");
}

void SetLog(LOG_ENUM LogItem, boolean Flag){
	LogStr[LogItem].EnableFlag = Flag;
}

boolean IsLogItemEnable(LOG_ENUM LogItem) {

	if (LogItem >= 0 && LogItem < LAST_LOG_ITEM) { /* check range */
		return (LogStr[LogItem].EnableFlag);
	}
	else {
		return LOG_DISABLE; /* not in range */
	}
}

LOG_ENUM SearchLogItem(char *Source)
{
	char *here;
	unsigned char i;

	for (i = FIRST_LOG_ITEM; i < (unsigned char)LAST_LOG_ITEM; i++)
	{
		init_search(LogStr[i].Text);
		here = strsearch(Source);
		if (here){
			if(!strncmp(LogStr[i].Text,Source,strlen(LogStr[i].Text)-1)){
				if(Source[strlen(LogStr[i].Text)] == ' ' || Source[strlen(LogStr[i].Text)] == 0 ) { /* token for first par or terminator */
				    return ((LOG_ENUM)i);
				}
			}
		}
	}
	return (LAST_LOG_ITEM); /* item not found */
}

const char *GetLogStr(LOG_ENUM LogItem) {
	if (LogItem >= 0 && LogItem < LAST_LOG_ITEM) { /* check range */
		return (LogStr[LogItem].Text);
	}
	else {
		return NULL;
	}
}

void StopGlobalLog(void) {
	globalLog = 0;
	}

void StartGlobalLog(void) {
	globalLog = 1;
	}

void PrintHMS(unsigned long t_ms)
{
unsigned short h,m,rs;
unsigned long s;

s = t_ms/1000;

h   = (s / 60 / 60);
m  = s / 60 % 60;
rs = s % 60;
printf("%02d:%02d:%02d-",h,m,rs);
}


void LogPrintfLocal(LOG_ENUM LogItemRequest,char *fmt,...)
{
	char LogBuffer[60];
	if(LogStr[LogItemRequest].EnableFlag == LOG_ENABLE) {
		va_list argptr;
		va_start(argptr,fmt);
		vsprintf(LogBuffer,fmt,argptr);
        PrintHMS(millis());
		printf("%06ld :%s :%s",millis(),GetLogStr(LogItemRequest),LogBuffer);
		va_end(argptr);
	}
}

/*---------------------------------------------- eof --------------------------------------------------*/
