#ifndef BINTREETEMP_H_
#define BINTREETEMP_H_
// int is an example of temp type
typedef int element;
struct binTreeNodeTemp
{
	struct binTreeNodeTemp *left;
	struct binTreeNodeTemp *right;
	element data;
};
typedef struct binTreeNodeTemp binTreeNodeTemp;
struct binTreeTemp
{
	binTreeNodeTemp *root;
	int numNode;
	int numNodeLeft;
	int numNodeRight;
	int level;	// root node is at 0 level. this variable keeps maximum level the tree
};
typedef struct binTreeTemp binTreeTemp;

void constructorBinTreeTemp(binTreeTemp *bin);
void destructorBinTreeTemp(binTreeTemp *bin);
void makeEmptyBinTreeTemp(binTreeTemp *bin);
int  addDataBinTreeTempPt(binTreeTemp *bin,element *data);
int  addDataBinTreeTemp(binTreeTemp *bin,element data);
int  deleteSunTreeTempPT(binTreeTemp *bin,element *data);
int  deleteSunTreeTemp(binTreeTemp *bin,element data);


#endif
