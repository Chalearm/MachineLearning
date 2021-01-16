#ifndef REPLACEWORD_H_
#define REPLACEWORD_H_

struct replaceW
{
	char *oldWord;
	char *newWord;
	int  numReplace;
};
typedef struct replaceW replaceW;
void constructorReplaceW(replaceW* rel);
void destructorReplaceW(replaceW* rel);
int  countWordInBuff(const char *buff,const char *word);
void setAttrb(replaceW *rel,const char* old,const char* nw,int count);
void makeEmptyReplaceW(replaceW *rel);
int findNthFirstIndexOfWord(const char *buff,const char *word,int indexN);
char* replaceAll(const char *buffer,const char *old,const char *nw);
char* replaceNWord(const char *buffer,const char *old,const char *nw,int count);
#endif /* REPLACEWORD_H_ */
