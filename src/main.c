/****************************************************/
/* File: main.c                                     */
/* Main program for TINY plus compiler              */
/* Compiler Construction: Principles and Practice   */
/* Lihan Chen                                       */
/****************************************************/

#include "scan.h"

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = TRUE;
int TraceScan = TRUE;
int TraceParse = TRUE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

int main(int argc, char * argv[])
{
  TreeNode * syntaxTree;
  char pgm[120]; /* source code file name */
  if (argc != 2) {
    fprintf(stderr, "usage: %s <filename>\n", argv[0]);
    exit(1);
  }
  strcpy(pgm, argv[1]);
  if (strchr(pgm, '.') == NULL) strcat(pgm, ".tny");
  source = fopen(pgm, "r");
  if (source == NULL) {
    fprintf(stderr, "File %s not found\n", pgm);
    exit(1);
  }
  listing = stdout; /* send listing to screen */
  fprintf(listing, "\nTINY COMPILATION: %s\n\n", pgm);

  while (getToken() != ENDFILE);

  fclose(source);
  return 0;
}
