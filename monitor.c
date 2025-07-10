/****************************************************************************/
/*                                                                          */
/* MODULE NAME : MONITOR.C                                                  */
/*                                                                          */
/*                                                                          */
/* MODULE FUNCTIONALITIES :                                                 */
/*                                                                          */
/* - Parse application command from editgets module. This module is used    */
/* as a separate file in order to be included inside several projects.      */
/*                                                                          */
/* CREATION : creation date  : 4.01.2006                                    */
/*            author         : V REMY                                       */
/*            module version : V1.0                                         */
/* CHANGE:                                                                  */
/*                                                                          */
/****************************************************************************/


#define BAD_ARG() printf("Bad option(s)\n")

int GetArg(char *Str,char *token_ptr[],char *token);
int SearchCommand(Command *Com,char *Source);
void ListCommands(Command *Com);
int GetHelpIndex (MESSAGES msgid);
void ProcessCommand(MESSAGES Code,char *buffer);


void PrintPromt(void) {
	printf("\ncmd:");
	}

/* using strtok to extract tokens from a string */
int GetArg(char *Str,char *token_ptr[],char *token)
{
	char *string_ptr;
	int index=0;
	/*string_ptr point to the start of the string */
	string_ptr=Str;

	/* use a while-loop to extract the tokens.  strtok takes two parameters.
	These are the array you are searching, and a string of delimiters.  In this
	case our delimiters are a whitespace and '!'.  You can have as many
	delimiters as you want. Pointers to the tokens are put in the pointer array
	token_ptr */
	while ((token_ptr[index]=strtok(string_ptr, token)) != NULL)
		{

		string_ptr=NULL;
		index++;
		}
	return index;
}


void ListCommands(const Command *Com)
{
	int i=0;
	int j;
	printf("\nList of commands:\n");
	do {
		for (j = 0;j<4;j++){
			if (Com[i+j].Text) {
				printf("%15s",Com[i+j].Text);
				}
			else {
				printf("\n");
				return;
				}
			}
		printf("\n");
		i+=j;
		}
	while(Com[i].Text);
	printf("\n");
}


int SearchCommand(const Command *Com,char *Source)
{
	char *here;
	int i, tmp;

	for (i = 0;Com[i].Text; i++)
		{
		init_search(Com[i].Text);
		here = strsearch(Source);
		if (here){
			if(!strncmp(Com[i].Text,Source,strlen(Com[i].Text)-1)){
				if(Source[strlen(Com[i].Text)] == ' ' || Source[strlen(Com[i].Text)] == 0 ) { /* token for first par or terminator */
					tmp = (int)Com[i].Code;
					return (tmp);
					}
				}
			}
		}

	return (-1);
}

int GetHelpIndex (MESSAGES msgid) {
 int i;
	for(i=0;Msg[i].Help;i++){
		if(msgid == Msg[i].Code){
			return i;
			}
		}
	return -1;

	}

static char Str[MAX_LEN+1]; /*edit line working buffer */

void MonitorHandling(void) {

	if (Serial.available() > 0) {
		if(EditGets(Str) >  -1){
			if(SearchCommand(Msg,Str) ==  -1) {
				if(strlen(Str)){
					printf("\nBad command\n");
					}
				InitEditGets();
				PrintPromt();
				}
			else {
				ProcessCommand((MESSAGES)SearchCommand(Msg,Str),Str);
				InitEditGets();
				PrintPromt();
				}
			}
		}

	}

/*---------------------------------------------- eof --------------------------------------------------*/
