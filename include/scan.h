/****************************************************/
/* File: scan.h                                     */
/* The scanner interface                            */
/* for the TINY plus compiler                       */
/* Compiler Construction: Principles and Practice   */
/* Lihan Chen                                       */
/****************************************************/

#ifndef _SCAN_H_
#define _SCAN_H_

#include "globals.h"

/* MAXTOKENLEN is the maximum size of a token */
#define MAXTOKENLEN 40

/* tokenString array stores the lexeme of each token */
extern char tokenString[MAXTOKENLEN + 1];

/* function getToken returns the 
 * next token in source file
 */
TokenType getToken(void);

#endif
