/* +++Date last modified: 05-Jul-1997 */

/*
**  line input w/editing
*/

#ifndef EDITGETS__H
#define EDITGETS__H


#define TABSIZE 8    /* size of one tab */
#define MAX_LEN 60   /* max size working string */

/*

*/

void InitEditGets(void);

/*
**  Arguments: Buffer to receive string
**  return 0 if not done, return len when done
*/

int EditGets(char *);

#endif /* EDITGETS__H */

#ifdef AZERTY

#endif
/*---------------------------------------------- eof --------------------------------------------------*/
