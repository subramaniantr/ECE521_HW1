#include "macros.h"
#include "defs.h"
#include "res.h"

void makeRes(Res, numRes, buf)
resistor *Res[];
int numRes;
char *buf;
{
    resistor *inst;
    int j, nodeA, nodeB, atoi();
    char name[MAXFIELD], node[MAXFIELD], num[MAXFIELD];
    double value, atof();

    j = 0;	
    j = getNextField(buf, name, j);
    j = getNextField(buf, node, j);
    nodeA = getMappedNode(node);
    j = getNextField(buf, node, j);
    nodeB = getMappedNode(node);
    j = getNextField(buf, num, j);
    value = atof(num);

    inst = CALLOC(resistor, 1);
    inst->name = (char *)strdup(name);
    inst->pNode = nodeA;
    inst->nNode = nodeB;
    inst->value = value;
    Res[numRes] = inst;
}

void printRes(Res, numRes)
resistor *Res[];
int numRes;
{
    int i;
    resistor *inst;

    for(i = 1; i <= numRes; i++) {
	inst = Res[i];
	printf("%s\t%s\t%s\t%f\n", inst->name, NodeArray[inst->pNode], NodeArray[inst->nNode], inst->value);
    }
}

void setupRes(Res, numRes)
resistor *Res[];
int numRes;
{
    int i;
    resistor *inst;

    /* do any preprocessing steps here */
    for(i = 1; i <= numRes; i++) {
	inst = Res[i];
	inst->conduct = 1.0/inst->value;
    }
}

void stampRes(Res, numRes, cktMatrix, Rhs)
resistor *Res[];
int numRes;
double **cktMatrix;
double *Rhs;
{
    int i, pNode, nNode;
    double conduct;

    /* stamp resistor*/
    for(i = 1; i <= numRes; i++) {
	pNode = Res[i]->pNode;
	nNode = Res[i]->nNode;
	conduct = Res[i]->conduct;
	cktMatrix[pNode][pNode] += conduct;
	cktMatrix[nNode][nNode] += conduct;
	cktMatrix[pNode][nNode] -= conduct;
	cktMatrix[nNode][pNode] -= conduct;
    }
}
