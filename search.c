/****************************************************************************/
/*                                                                          */
/* MODULE NAME : search.c                                                   */
/*                                                                          */
/*                                                                          */
/* MODULE FUNCTIONALITIES :                                                 */
/*                                                                          */
/* -  string searching functions                                            */
/*                                                                          */
/* CREATION : creation date  : 20.12.2005                                   */
/*            author         : V REMY                                       */
/*            module version : V1.0                                         */
/* CHANGE:                                                                  */
/*                                                                          */
/****************************************************************************/

#include <stddef.h>
#include <string.h>

#define UCHAR_MAX 255 /* table contains 255 ascii characters */

static unsigned char table[UCHAR_MAX];
static unsigned char len;
static char *findme;

/*
**  Call this with the string to locate to initialize the table
*/

void init_search(const char *string)
{
      unsigned int i; /* integer allows up to UCHAR_MAX iteration */

      len = (unsigned char)strlen(string);
      for (i = 0; i <= UCHAR_MAX; i++)
            table[i] = len;
      for (i = 0; i < len; i++)
            table[(unsigned char)string[i]] = len - i - 1;
      findme = (char *)string;
}

/*
**  Call this with a buffer to search
*/

char *strsearch(const char *string)
{
       unsigned char shift;
       unsigned char pos = len - 1;
      char *here;
      unsigned char limit=(unsigned char)strlen(string);

      while (pos < limit)
      {
            while( pos < limit &&
                  (shift = table[(unsigned char)string[pos]]) > 0)
            {
                  pos += shift;
            }
            if (0 == shift)
            {
                  if (0 == strncmp(findme,
                        here = (char *)&string[pos-len+1], len))
                  {
                        return(here);
                  }
                  else  pos++;
            }
      }
      return NULL;
}

#ifdef TEST

#include <stdio.h>

main()
{
      char *here;
      char *find_strings[] = {"abb", "you", "not", "it", "dad", "yoo", "hoo",
                              "oo", "oh", "xx", "xx", "x", "x", NULL};
      char *search_strings[] = {"cabbie", "your", "It isn't here",
                                "But it is here", "hodad", "yoohoo", "yoohoo",
                                "yoohoo", "yoohoo", "yoohoo", "xx", "x", "."};
      int i;

      for (i = 0; find_strings[i]; i++)
      {
            init_search(find_strings[i]);
            here = strsearch(search_strings[i]);
            printf("\"%s\" is%s in \"%s\"", find_strings[i],
                  here ? "" : " not", search_strings[i]);
            if (here)
                  printf(" [\"%s\"]", here);
            putchar('\n');
      }

      return 0;
}

#endif /* TEST */

#ifdef AZERTY

#endif
/*---------------------------------------------- eof --------------------------------------------------*/
