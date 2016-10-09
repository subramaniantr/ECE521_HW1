#include "macros.h"
#include "defs.h"
#include "vcvs.h"

void makeEsrc(Esrc, numEsrc, buf)
vcvs *Esrc[];
int numEsrc;
char *buf;
{
    vcvs *inst;
    int j, nodeA, nodeB, nodeC, nodeD, branchNum, atoi();
    char name[MAXFIELD], node[MAXFIELD], num[MAXFIELD];
    double value, atof();

    j = 0;	
    j = getNextField(buf, name, j);
    branchNum = getMappedBranch(name);
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

    inst = CALLOC(vcvs, 1);
    inst->name = (char *)strdup(name);
    inst->pNode = nodeA;
    inst->nNode = nodeB;
    inst->pCNode = nodeC;
    inst->nCNode = nodeD;
    inst->branchNum = branchNum ;
    inst->gain = value;
    Esrc[numEsrc] = inst;
}

void printEsrc(Esrc, numEsrc)
vcvs *Esrc[];
int numEsrc;
{
    int i;
    vcvs *inst;
    for(i = 1; i <= numEsrc; i++) {
	inst = Esrc[i];
	printf("%s\t%s\t%s\t%s\t%s\t%f\n", inst->name, NodeArray[inst->pNode], NodeArray[inst->nNode], NodeArray[inst->pCNode], NodeArray[inst->nCNode], inst->gain);
    }
}

void setupEsrc(Esrc, numEsrc)
vcvs *Esrc[];
int numEsrc;
{
    int i;
    vcvs *inst;

    /* do any preprocessing steps here */
   //Pushing Branch number columns after the Node numbers
    for(i = 1; i <= numEsrc; i++) {
	inst = Esrc[i];
	inst->branchNum += NumNodes;
    }
}

void stampEsrc(Esrc, numEsrc, cktMatrix, Rhs)
vcvs *Esrc[];
int numEsrc;
double **cktMatrix;
double *Rhs;
{
    int i, pNode, nNode, pCNode, nCNode, branchNum;
    double gain ;
    /* stamp E source*/
    for(i = 1; i <= numEsrc; i++) {
	pNode = Esrc[i]->pNode;
	nNode = Esrc[i]->nNode;
	pCNode = Esrc[i]->pCNode;
	nCNode = Esrc[i]->nCNode;
	branchNum = Esrc[i]->branchNum;
        gain   = Esrc[i]->gain;
        //KCL for pNode & nNode
 	cktMatrix[pNode][branchNum] += 1; //I leaving pNode
 	cktMatrix[nNode][branchNum] -= 1;
        //BCE for VCVS : Vp-Vn-gain*(Vpc-Vnc)=0
 	cktMatrix[branchNum][pNode] += 1;
 	cktMatrix[branchNum][nNode] -= 1;
 	cktMatrix[branchNum][pCNode] -= gain;
 	cktMatrix[branchNum][nCNode] += gain;
    }
}
