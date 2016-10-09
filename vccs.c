#include "macros.h"
#include "defs.h"
#include "vccs.h"

void makeGsrc(Gsrc, numGsrc, buf)
vccs *Gsrc[];
int numGsrc;
char *buf;
{
    vccs *inst;
    int j, nodeA, nodeB, nodeC, nodeD, atoi();
    char name[MAXFIELD], node[MAXFIELD], num[MAXFIELD];
    double value, atof();

    j = 0;	
    j = getNextField(buf, name, j);
    j = getNextField(buf, node, j);
    nodeA = getMappedNode(node);
    j = getNextField(buf, node, j);
    nodeB = getMappedNode(node);
    j = getNextField(buf, node, j);
    nodeC = getMappedNode(node);
    j = getNextField(buf, node, j);
    nodeD = getMappedNode(node);
    j = getNextField(buf, num, j);
    value = atof(num);

    inst = CALLOC(vccs, 1);
    inst->name = (char *)strdup(name);
    inst->pNode = nodeA;
    inst->nNode = nodeB;
    inst->pCNode = nodeC;
    inst->nCNode = nodeD;
    inst->Gm = value;
    Gsrc[numGsrc] = inst;
}

void printGsrc(Gsrc, numGsrc)
vccs *Gsrc[];
int numGsrc;
{
    int i;
    vccs *inst;
    for(i = 1; i <= numGsrc; i++) {
	inst = Gsrc[i];
	printf("%s\t%s\t%s\t%s\t%s\t%f\n", inst->name, NodeArray[inst->pNode], NodeArray[inst->nNode], NodeArray[inst->pCNode], NodeArray[inst->nCNode], inst->Gm);
    }
}

void setupGsrc(Gsrc, numGsrc)
vccs *Gsrc[];
int numGsrc;
{
    int i;
    vccs *inst;

    /* do any preprocessing steps here */
    for(i = 1; i <= numGsrc; i++) {
    }
}

void stampGsrc(Gsrc, numGsrc, cktMatrix, Rhs)
vccs *Gsrc[];
int numGsrc;
double **cktMatrix;
double *Rhs;
{
    int i, pNode, nNode, pCNode, nCNode;
    double Gm;
    /* stamp G source*/
    for(i = 1; i <= numGsrc; i++) {
	pNode = Gsrc[i]->pNode;
	nNode = Gsrc[i]->nNode;
	pCNode = Gsrc[i]->pCNode;
	nCNode = Gsrc[i]->nCNode;
	Gm = Gsrc[i]->Gm;
	cktMatrix[pNode][pCNode] += Gm;
	cktMatrix[pNode][nCNode] -= Gm;
	cktMatrix[nNode][pCNode] -= Gm;
	cktMatrix[nNode][nCNode] += Gm;
    }
}
