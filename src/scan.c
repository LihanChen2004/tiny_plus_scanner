/****************************************************/
/* File: scan.c                                     */
/* The scanner implementation                       */
/* for the TINY plus compiler                       */
/* Compiler Construction: Principles and Practice   */
/* Lihan Chen                                       */
/****************************************************/

#include "scan.h"

#include "globals.h"
#include "util.h"

/* states in scanner DFA */
typedef enum {
  START,
  INASSIGN,
  INCOMMENT,
  INNUM,
  INID,
  DONE,
  INLT,
  INGT,
  INE,
  INUPDOX,
} StateType;

/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN + 1];

/* BUFLEN = length of the input buffer for
   source code lines */
#define BUFLEN 256

static char lineBuf[BUFLEN]; /* holds the current line */
static int linepos = 0;      /* current position in LineBuf */
static int bufsize = 0;      /* current size of buffer string */
static int EOF_flag = FALSE; /* corrects ungetNextChar behavior on EOF */

/* getNextChar fetches the next non-blank character
   from lineBuf, reading in a new line if lineBuf is
   exhausted */
static int getNextChar(void)
{
  if (!(linepos < bufsize)) {
    lineno++;
    if (fgets(lineBuf, BUFLEN - 1, source)) {
      if (EchoSource) fprintf(listing, "%d: %s", lineno, lineBuf);
      bufsize = strlen(lineBuf);
      linepos = 0;
      return lineBuf[linepos++];
    } else {
      EOF_flag = TRUE;
      return EOF;
    }
  } else
    return lineBuf[linepos++];
}

/* ungetNextChar backtracks one character
   in lineBuf */
static void ungetNextChar(void)
{
  if (!EOF_flag) linepos--;
}

/* lookup table of reserved words */
static struct
{
  char * str;
  TokenType tok;
} reservedWords[MAXRESERVED] = {
  {"if", IF},       {"then", THEN},     {"else", ELSE},     {"end", END},    {"repeat", REPEAT},
  {"until", UNTIL}, {"read", READ},     {"write", WRITE},   {"true", TRUE1}, {"false", FALSE1},
  {"or", OR},       {"and", AND},       {"not", NOT},       {"int", INT},    {"bool", BOOL},
  {"float", FLOAT}, {"double", DOUBLE}, {"string", STRING}, {"do", DO},      {"while", WHILE}};

/* lookup an identifier to see if it is a reserved word */
/* uses linear search */
static TokenType reservedLookup(char * s)
{
  int i;
  for (i = 0; i < MAXRESERVED; i++)
    if (!strcmp(s, reservedWords[i].str)) return reservedWords[i].tok;
  return ID;
}

/****************************************/
/* the primary function of the scanner  */
/****************************************/
/* function getToken returns the
 * next token in source file
 */
TokenType getToken(void)
{ /* index for storing into tokenString */
  int tokenStringIndex = 0;
  /* holds current token to be returned */
  TokenType currentToken;
  /* current state - always begins at START */
  StateType state = START;
  /* flag to indicate save to tokenString */
  int save;
  while (state != DONE) {
    int c = getNextChar();
    save = TRUE;
    switch (state) {
      case START:
        if (isdigit(c))       // 数字
          state = INNUM;      // 数字常量状态
        else if (isalpha(c))  // 字母
          state = INID;       // 标识符状态
        else if (c == ':')
          state = INASSIGN;
        else if ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r'))
          save = FALSE;
        else if (c == '{') {
          save = FALSE;
          state = INCOMMENT;  // 注释状态
        } else if (c == '\'') {
          save = FALSE;
          state = INUPDOX;
        } else if (c == '<') {
          state = INLT;
        } else if (c == '>') {
          state = INGT;
        } else {
          state = DONE;
          switch (c) {
            case EOF:
              save = FALSE;
              currentToken = ENDFILE;
              break;
            case '=':
              currentToken = EQ;
              break;
            case '<':
              currentToken = LT;
              break;
            case '+':
              currentToken = PLUS;
              break;
            case '-':
              currentToken = MINUS;
              break;
            case '*':
              currentToken = TIMES;
              break;
            case '/':
              currentToken = OVER;
              break;
            case '(':
              currentToken = LPAREN;
              break;
            case ')':
              currentToken = RPAREN;
              break;
            case ';':
              currentToken = SEMI;
              break;
            case '>':
              currentToken = GT;
              break;
            case ',':
              currentToken = COMMA;
              break;
            case '^':
              currentToken = UPDOX;
              break;
            default:
              currentToken = ERROR;
              break;
          }
        }
        break;
      case INCOMMENT:
        save = FALSE;
        if (c == EOF) {  // 没有遇到 } 就结束
          save = FALSE;
          state = DONE;
          currentToken = ERROR;
          char * msg = "comment missing \" } \" !";
          strcpy(tokenString, msg);
          tokenStringIndex += strlen(msg);
        } else if (c == '{') {  // 嵌套
          save = FALSE;
          state = DONE;
          currentToken = ERROR;
          char * msg = "comment cannot be nested";
          strcpy(tokenString, msg);
          tokenStringIndex += strlen(msg);
        } else if (c == '}') {
          state = START;
        }
        break;
      case INASSIGN:
        state = DONE;
        if (c == '=')
          currentToken = ASSIGN;
        else { /* backup in the input */
          ungetNextChar();
          save = FALSE;
          currentToken = ERROR;
          char * msg = "missing \" = \" after \" : \"!";
          strcpy(tokenString, msg);
          tokenStringIndex += strlen(msg);
        }
        break;
      case INNUM:
        if (!isdigit(c)) { /* backup in the input */
          ungetNextChar();
          save = FALSE;
          state = DONE;
          currentToken = NUM;
        }
        break;
      case INID:
        if (!isalpha(c) && !isdigit(c)) { /* backup in the input */
          ungetNextChar();
          save = FALSE;
          state = DONE;
          currentToken = ID;
        }
        break;
      case INLT:  // <
        state = DONE;
        if (c == '=') {  // <=
          state = DONE;
          currentToken = LE;
        } else {
          ungetNextChar();
          save = FALSE;
          state = DONE;
          currentToken = LT;
        }
        break;
      case INGT:  // >
        state = DONE;
        if (c == '=') {  // >=
          state = DONE;
          currentToken = GE;
        } else {
          ungetNextChar();
          save = FALSE;
          state = DONE;
          currentToken = GT;
        }
        break;
      case INE:  // !=
        state = DONE;
        if (c == '=') {  // !=
          state = DONE;
          currentToken = NE;
        } else {
          ungetNextChar();
          save = FALSE;
          state = DONE;
          currentToken = ERROR;
        }
      case INUPDOX:       // '
        if (c == '\'') {  // 读到下一个上引号
          save = FALSE;
          state = DONE;
          currentToken = STR;
        } else if (!(linepos < bufsize)) {  // 注释的右部括号缺失
          save = FALSE;
          state = DONE;
          currentToken = ERROR;
          char * msg = "STR missing \" \' \" !";
          strcpy(tokenString, msg);
          tokenStringIndex += strlen(msg);
        }
        break;
      case DONE:
      default: /* should never happen */
        fprintf(listing, "Scanner Bug: state= %d\n", state);
        state = DONE;
        currentToken = ERROR;
        break;
    }
    if ((save) && (tokenStringIndex <= MAXTOKENLEN)) tokenString[tokenStringIndex++] = (char)c;
    if (state == DONE) {
      tokenString[tokenStringIndex] = '\0';
      if (currentToken == ID) currentToken = reservedLookup(tokenString);
    }
  }
  if (TraceScan) {
    fprintf(listing, "\t%d: ", lineno);
    printToken(currentToken, tokenString);
  }
  return currentToken;
} /* end getToken */
