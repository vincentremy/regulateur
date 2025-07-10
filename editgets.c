/* +++Date last modified: 05-Jul- 2005 */
/* editgets.c - line input w/editing  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <arduino.h>                            /* Serial communication driver */
#include "editgets.h"

#define CTRL_CHARS_ALLOWED 0                   /* Non-zero allows entry of Ctrl-characters   */
#define NUL '\0'
#define BAD_KEY() {putchar('\a'); break;}
#define putch(x)  putchar(x)
//#define min(x,y) (((x) <= (y)) ? (x) : (y))
//#define max(x,y) (((x) >= (y)) ? (x) : (y))

#define Key_ESC         0x1b                   /* ASCII codes                */
#define Key_ENTER       '\r'
#define Key_TAB         '\t'
#define Key_BACKSPC     '\b'
#define Key_NL          '\n'
#define Key_LFEED       '\n'
#define Key_FFEED       '\f'


// char *temp[MAX_LEN+1];   /* Working buffer                         */
static char done = 0;   /* Non-Zero if done                       */
static int pos,         /* Our position within the string         */
           len ;        /* The current length of the string       */

/*
 */

void InitEditGets( void) {
	len = pos = 0;
	done = 0;              /* reset flag */
	}

/*
 **  Arguments: Buffer to receive string
 **  return 0 if not done, return len when done
 */
int EditGets(char *temp) {
	int insert,           /* Non-zero if in insert mode             */
	i, j, k,              /* Temporary variables                    */
	skip;                 /* Spaces to skip when tabbing            */
	char  c;              /* Keyboard input                         */

//	temp = (char *)s;

	/* Set insert mode, save cursor, and use a big cursor */
	insert = 1;

	c =  Serial.read(); // Read a character;
	switch (c)
		{
		case Key_ESC :
			if (len == 0)
				break;
			if (pos != len)
				{
				for (i = pos; i < len; i++)
					putch(' ');
				}
			for (i = len; i > 0; i--)
				{
				putch('\b');
				putch(' ');
				putch('\b');
				}
			pos = len = 0;
			break;
		case Key_BACKSPC :
			if (pos == 0)
				break;
			if (pos != len)
				{
				for (i = pos - 1; i < len; i++)
					temp[i] = temp[i + 1];
				pos--;
				len--;
				putch('\b');
				for (i = pos; i < len; i++)
					putch(temp[i]);
				putch(' ');
				for (i = len; i >= pos; i--)
					putch('\b');
				}
			else
				{
				putch('\b');
				putch(' ');
				putch('\b');
				pos = --len;
				}
			break;

		case Key_NL :
			break;
		case Key_ENTER :
			done = 1;
			putch('\n');
			break;
		case Key_TAB :

			if (pos == MAX_LEN)
				break;

			skip = TABSIZE - ((pos + TABSIZE) % TABSIZE);

			if (insert)
				{
				if ((len + skip) > MAX_LEN)
					skip = MAX_LEN - len;

				for (i = pos, j = len + skip - 1, k = len - 1;
					 i < len ; ++i, --j, --k)
					{
					temp[j] = temp[k];
					}
				}
			else  /* overwrite */
				{
				if ((pos + skip) > MAX_LEN)
					skip = MAX_LEN - pos;
				}
			for (i = 0; i < skip; ++i)
				{
				temp[pos++] = ' ';
				putch(' ');
				}
			len = insert ? len + skip : max(len, pos);
			for (i = pos; i < len; ++i)
				putch(temp[i]);
			for (i = len; i > pos; --i)
				putch('\b');
			break;

		default :
			if (pos == MAX_LEN)
				break;

			if (c & 0xff00          /* Illegal extended character */

#if !CTRL_CHARS_ALLOWED

				|| iscntrl(c)
#endif
			   )
				{
				BAD_KEY();
				}

			if ((!(insert)) || pos == len)
				{
				temp[pos++] = (char)c;
				if (pos > len) len++;
				putch(c);
				}
			else
				{
				if (len == MAX_LEN)
					break;
				for (i = len++; i >= pos; i--)
					temp[i + 1] = temp[i];
				temp[pos++] = (char)c;
				putch(c);
				for (i = pos; i < len; i++)
					putch(temp[i]);
				for (i = len; i > pos; i--)
					putch('\b');
				}
		}
	if (done ) {
		temp[len] = '\0';
		return len;
		}
	else {

		/* return 0 if not done */
		return -1;
		}
	}

/* #define TEST */
#ifdef TEST

main()
{
	char *mystring;

	/* memset(mystring, 0, 60); */
	puts("                  "
		 "0        1         2         3         4         5         6");
	puts("                  "
		 "123456789012345678901234567890123456789012345678901234567890");
	Editgets(50, "This is a test");
	puts("Enter any string: ");
	while(!Editgets(mystring);
	printf("editgets() returned:\n\"%s\"\n", mystring);
	return 0;
}

#endif /* TEST */

#ifdef AZERTY

#endif
/*---------------------------------------------- eof --------------------------------------------------*/
