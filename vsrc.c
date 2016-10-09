#include "macros.h"
#include "defs.h"
#include "vsrc.h"

void makeVsrc(Vsrc, numVsrc, buf)
vsource *Vsrc[];
int numVsrc;
char *buf;
{
    vsource *inst;
    int j, nodeA, nodeB, branchNum, atoi();
    char name[MAXFIELD], node[MAXFIELD], num[MAXFIELD];
    double value, atof();

	/* incrementing the number of branches */

    j = 0;	
    j = getNextField(buf, name, j);
    branchNum = getMappedBranch(name);
    j = getNextField(buf, node, j);
    nodeA = getMappedNode(node);
    j = getNextField(buf, node, j);
    nodeB = getMappedNode(node);
    j = getNextField(buf, num, j);
    value = atof(num);

    inst = CALLOC(vsource, 1);
    inst->name = (char *)strdup(name);
    inst->pNode = nodeA;
    inst->nNode = nodeB;
    inst->branchNum = branchNum ;
    inst->voltage = value;
    Vsrc[numVsrc] = inst;
}

void printVsrc(Vsrc, numVsrc)
vsource *Vsrc[];
int numVsrc;
{
    int i;
    vsource *inst;

    for(i = 1; i <= numVsrc; i++) {
	inst = Vsrc[i];
	printf("%s\t%s\t%s\t%f\n", inst->name, NodeArray[inst->pNode], NodeArray[inst->nNode], inst->voltage);
    }
}

void setupVsrc(Vsrc, numVsrc)
vsource *Vsrc[];
int numVsrc;
{
    int i;
    vsource *inst;

    /* do any preprocessing steps here */
    for(i = 1; i <= numVsrc; i++) {
	inst = Vsrc[i];
	inst->branchNum += NumNodes;
    }
}

void stampVsrc(Vsrc, numVsrc, cktMatrix, Rhs)
vsource *Vsrc[];
int numVsrc;
double **cktMatrix;
double *Rhs;
{
    int i, pNode, nNode, branchNum;
    vsource *inst;
    double voltage;
	
    /* stamp voltage source*/
    for(i = 1; i <= numVsrc; i++) {
	inst = Vsrc[i];
	pNode = inst->pNode;
	nNode = inst->nNode;
	branchNum = inst->branchNum;
	voltage = inst->voltage;
 	cktMatrix[pNode][branchNum] += 1;
 	cktMatrix[nNode][branchNum] -= 1;
 	cktMatrix[branchNum][pNode] += 1;
 	cktMatrix[branchNum][nNode] -= 1;
	Rhs[branchNum] += voltage;
    }
}
