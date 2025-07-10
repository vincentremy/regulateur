/****************************************************************************/
/*                                                                          */
/* MODULE NAME : MONITOR_SPEC.C                                             */
/*                                                                          */
/*                                                                          */
/* MODULE FUNCTIONALITIES :                                                 */
/*                                                                          */
/* - Parse application command from editgets module                         */
/*                                                                          */
/* CREATION : creation date  : 4.01.2006                                    */
/*            author         : V REMY                                       */
/*            module version : V1.0                                         */
/* CHANGE:                                                                  */
/*                                                                          */
/****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <Flash.h>
#include <arduino.h>
#include <Servo.h>


#include "search.h"
#include "editgets.h"
#include "log.h"
#include "monitor.h"

#include "RTDTrigger.h"


extern RTDTrigger rtdA0;
extern RTDTrigger rtdA1;
extern Servo myservo;
extern byte fan_pin;
extern void SetValveOpening(byte val);

typedef enum
{
    HELP,
    REV,
    LIST_LOG,
    SET_LOG,
    START_LOG,
    STOP_LOG,
    SERVO_PC,
    FAN_PC,
    PRINT_TEMP,
    LAST_CMD
} MESSAGES;


typedef struct
{
    const char *Text;
    const MESSAGES Code;
    const char *Help;
} Command;

const Command Msg[] =
{
    {"?",HELP,"Type help [command]"},
    {"l",START_LOG,"Start global log"},
    {"L",STOP_LOG,"Stop global log"},
    {"help",HELP,"Type help [command]"},
    {"revision",REV,"Print the software revision"},
    {"setlog",SET_LOG,"Set item to log\n\rType :setlog [item to log] [0-1]"},
    {"servo",SERVO_PC,"Set servo position\n\rType: servo [0-100]"},
    {"fan",FAN_PC,"Set fan voltage\n\rType: fan [0-255]"},
    {"listlog",LIST_LOG,"Print items log and its status"},
    {"print",PRINT_TEMP,"Print A0,A1"},
    {NULL,LAST_CMD,NULL}
};

FLASH_STRING(menu,
             "\r\n"
             "+********* Stuv regulator / command line editor***************+\r\n"
             "| This program is a simple monitor command handling.          |\r\n"
             "| Type 'help' or 'help <COMMAND>'  for more informations      |\r\n"
             "+-------------------------------------------------------------+\r\n")



#include "monitor.c" /* common function in order to parse terminal command */



void InitMonitor(void)
{
    Serial << menu;
//	printf(menu);
//	printf("\r\nFTM Stacker version: %s\r\nTime compilation: %s\r\n", GetReleaseText(),GetCompilerTime());
    StartGlobalLog();
    InitEditGets();
    PrintPromt();
}


void ProcessCommand(const MESSAGES Code,char *buffer)
{
    char *token_ptr[10];
    short Param;
    int i,nbrtoken;
    switch (Code)
    {

    case HELP:
        if((nbrtoken=GetArg(buffer,token_ptr,"- ")) > 1)
        {
            if( nbrtoken == 2)
            {
                int tmp;
                if((tmp=SearchCommand(Msg,token_ptr[1])) >= 0)
                {
                    for(i=0; Msg[i].Help; i++)
                    {
                        if(tmp == Msg[i].Code)
                        {
                            printf("\r\n%s", Msg[i].Help);
                            break;
                        }
                    }
                }
                else
                    BAD_ARG();
            }
            else
                BAD_ARG();

        }
        else
            ListCommands(Msg);

        break;
    case REV:
        //Serial << menu;
        menu.print(Serial);
        Serial.println(rtdA1.getTemperatureSmooth());
        break;
    case PRINT_TEMP:
        LogPrintf(STANDARD_LOG,"A0:");
        Serial.println(rtdA0.getTemperatureSmooth());
        LogPrintf(STANDARD_LOG,"A1:");
        Serial.println(rtdA1.getTemperatureSmooth());
        break;
    case LIST_LOG:
        ListLog();
        break;
    case SET_LOG:
        if((nbrtoken=GetArg(buffer,token_ptr,"- ")) > 1)
        {
            if( nbrtoken == 3)
            {
                int tmp;
                tmp=SearchLogItem(token_ptr[1]);
                if(tmp != -1)
                {
                    if((strcmp(token_ptr[2],"0") == 0) || (strcmp(token_ptr[2],"1") == 0))
                    {
                        if(strcmp(token_ptr[2],"1") == 0)
                            SetLog((LOG_ENUM)tmp, LOG_ENABLE);
                        else
                            SetLog((LOG_ENUM)tmp, LOG_DISABLE);

                    }
                    else
                        BAD_ARG();
                }
                else
                    BAD_ARG();
            }
            else
                BAD_ARG();
        }
        break;
    case START_LOG:
        printf("\r\nStart global log\n");
        StartGlobalLog();
        break;
    case STOP_LOG:
        printf("\r\nStop global log\n");
        StopGlobalLog();
        break;
    case SERVO_PC:
        if((nbrtoken=GetArg(buffer,token_ptr,"- ")) > 1)
        {
            if( nbrtoken == 2)
            {
                sscanf(token_ptr[1], "%d", &Param);
                if(sscanf(token_ptr[1], "%d", &Param))
                {
                    if(Param >=0 && Param <= 100)
                    {
                       // myservo.write(Param);
                       SetValveOpening((byte)Param);
                        printf("valve set to %d%\n",Param);
                    }
                    else
                        BAD_ARG();
                }
                else
                    BAD_ARG();
            }
            else
                BAD_ARG();

        }
        else
            printf("type servo [angle]\n");
        break;
    case FAN_PC:
        if((nbrtoken=GetArg(buffer,token_ptr,"- ")) > 1)
        {
            if( nbrtoken == 2)
            {
                sscanf(token_ptr[1], "%d", &Param);
                if(sscanf(token_ptr[1], "%d", &Param))
                {
                    if(Param >=0 && Param <= 255)
                    {
                        analogWrite(fan_pin, Param);
                        printf("fan set to %d%\n",Param);
                    }
                    else
                        BAD_ARG();
                }
                else
                    BAD_ARG();
            }
            else
                BAD_ARG();

        }
        else
            printf("type fan [0-255]\n");
        break;

    default:
        printf("\n");
        LogPrintf(ERROR_LOG,"Undefined case in monitor module\n");
    }
}



