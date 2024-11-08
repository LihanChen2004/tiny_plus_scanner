/****************************************************/
/* File: util.h                                     */
/* Utility functions implementation                 */
/* for the TINY plus compiler                       */
/* Compiler Construction: Principles and Practice   */
/* Lihan Chen                                       */
/****************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

#include "globals.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType, const char* );

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind);

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind);

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString( char * );

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * );

#endif
