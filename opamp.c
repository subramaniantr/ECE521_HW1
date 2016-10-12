#include "macros.h"
#include "defs.h"
#include "opamp.h"

void makeOp(Op, numOp, buf)
opamp *Op[];
int numOp;
char *buf;
{
    opamp *inst;
    int j, nodeA, nodeB, nodeC, branchNum, atoi();
    char name[MAXFIELD], node[MAXFIELD], num[MAXFIELD];
    double value, atof();

    j = 0;	
    j = getNextField(buf, name, j);
    NumBranches++;
    branchNum = NumBranches;
    j = getNextField(buf, node, j);
    nodeA = getMappedNode(node);
    j = getNextField(buf, node, j);
    nodeB = getMappedNode(node);
    j = getNextField(buf, node, j);
    nodeC = getMappedNode(node);
    j = getNextField(buf, num, j);
    value = atof(num);

    inst = CALLOC(opamp, 1);
    inst->name = (char *)strdup(name);
    inst->oNode = nodeA;
    inst->pNode = nodeB;
    inst->nNode = nodeC;
    inst->branchNum = branchNum ;
    inst->A = value;
    Op[numOp] = inst;
}

void printOp(Op, numOp)
opamp *Op[];
int numOp;
{
    int i;
    opamp *inst;
    for(i = 1; i <= numOp; i++) {
	inst = Op[i];
	printf("%s\t%s\t%s\t%s\t%f\n", inst->name, NodeArray[inst->oNode], NodeArray[inst->pNode], NodeArray[inst->nNode], inst->A);
    }
}

void setupOp(Op, numOp)
opamp *Op[];
int numOp;
{
    int i;
    opamp *inst;

    /* do any preprocessing steps here */
   //Pushing Branch number columns after the Node numbers
    for(i = 1; i <= numOp; i++) {
	inst = Op[i];
	inst->branchNum += NumNodes;
    }
}

void stampOp(Op, numOp, cktMatrix, Rhs)
opamp *Op[];
int numOp;
double **cktMatrix;
double *Rhs;
{
    int i, pNode, nNode, oNode, branchNum;
    double A ;
    /* stamp N source*/
    for(i = 1; i <= numOp; i++) {
	pNode = Op[i]->pNode;
	nNode = Op[i]->nNode;
	oNode = Op[i]->oNode;
        A     = Op[i]->A;
	branchNum = Op[i]->branchNum;
        //KCL for output Node
 	cktMatrix[oNode][branchNum] += 1;
        //BCE for Opamp : A(Vp-Vn)+ Vo=0
 	cktMatrix[branchNum][pNode] += A;
 	cktMatrix[branchNum][nNode] -= A;
 	cktMatrix[branchNum][oNode] += 1;
    }
}
