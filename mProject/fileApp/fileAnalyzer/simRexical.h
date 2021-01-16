/********************************************************************/
/*
      FILE        :   simRexical.h
      Name        :   Chalearm Saelim
      Date        :   5 December 2016
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   Rexical

      Description :    -
      Dependency     :   We use the included library as below 
                                                #include -
      How to compile: gcc simRexical.c -o  a
      How to run        : -
      
      revision-history
      version   date          author     Description
      1.        05-12-2016    csaelim    First draft
*/


/*******************************************************************/
#ifndef _SIMREXICAL_H
#define _SIMREXICAL_H
#define NAME_SIZE 30
#define WORD_SIZE 50
#define BUFF_SIZE 300
#define EXP_SIZE 15
#define MAX_REX 100
/* reserver word */
#define LEFT_PAR   '['
#define RIGHT_PAR  ']'
#define OR_SYM     '|'
#define PLUS_SYM   '+'
#define COMPLE_SYM '-'
#define STAR_SYM   '*'
#define CONCAT     '.'
#define RANGE_SYM   '2'
#define CHAR_SYM   '\''
#define Q_SYM      '?'
#define BSLASH_SYM   '\\'


/* WHITE space char  */
#define W1_SYM ' '
#define W2_SYM '\t'
#define W3_SYM '\n'
#define W3_SYM '\n'
#define W4_SYM '\r'

#define END_STR '\0'

/* default value */
#define DEFUALT_TYPE -1
#define DEFUALT_CHAR -1
#define DEFUALT_OPER -1

/* state define */
#define DEF_OK 1
#define DEF_NOK 0

#define DEF_FOUND -2
#define DEF_NOT_FOUND 0 
#define DEF_FOUND_LT_PAR 1
#define DEF_FOUND_RT_PAR 2

struct expRex /* rexical expression*/
{
    /* 
      type 
      Unary :
                0=char unary, 
                1= expression unary
      Binary                
                2 = bin char vs char, 
                3 =  bin  char vs expression, 
                4 = expression vs char, 
                5 = expression vs express */
    char m_type; 
    /* operator
        0 = concatation
        1 = plus
        2 = star
        3 = ?
        4 = or
    */
    char m_operator;
    char m_charA;
    char m_charB;
    struct expRex *m_expA;
    struct expRex *m_expB;
};
struct aRex
{
    char m_name[NAME_SIZE];
    struct expRex m_expR[EXP_SIZE];
    int m_numRexExp;
};

struct rexSet
{
    struct aRex m_rexs[MAX_REX];
    int m_numRex;
};

void constructorExpRex(struct expRex *obj);
void constructorARex(struct aRex *obj);
void constructorRexS(struct rexSet*obj);
void destructorExpRex(struct expRex *obj);
void destructorARex(struct aRex *obj);
void destructorRexS(struct rexSet*obj);
void readLexicalFileRexS(struct rexSet*obj,const char *filename);
void cleanResSInput(char *input);
int isStartStopCharExpRex(char ch);
int isLtParExpRex(char ch);
int isRtParExpRex(char ch);
int isStartWordExpRex(char ch);
int isOperatorExpRex(char ch);
int isAlphaRex(char ch);
int isNumRex(char ch);
int isStringRex(const char *text,int *strIndex,int *lenght);
int isVarNameRex(const char *text,int *strIndex,int *lenght);

int getCharRex(char *text,char **nxtAddr,char *ch1);

int getStringRex(char *text,char **nxtAddr,char *word);
int getVarNameRex(char *text,char **nxtAddr,char *var);

int isWordRex(char ch);
void inputAnalyze2Arex(struct expRex *obj,const char *expression);
void findOperator(const char *input,int *nextStr,int *oper);
void findPairPar(const char *input,int *strPos,int *stopPos,int *stateO);
void readStatement2Exp(struct expRex *obj,const char *input);
void readStatement2Arex(struct aRex *obj,const char *input); 
#endif