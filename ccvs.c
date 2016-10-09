#include "macros.h"
#include "defs.h"
#include "ccvs.h"

void makeHsrc(Hsrc, numHsrc, buf)
ccvs *Hsrc[];
int numHsrc;
char *buf;
{
    ccvs *inst;
    int j, nodeA, nodeB, cbranchNum, branchNum, atoi();
    char name[MAXFIELD], cname[MAXFIELD], node[MAXFIELD], num[MAXFIELD];
    double value, atof();

    j = 0;	
    j = getNextField(buf, name, j);
    branchNum = getMappedBranch(name);
    j = getNextField(buf, node, j);
    nodeA = getMappedNode(node);
    j = getNextField(buf, node, j);
    nodeB = getMappedNode(node);
    j = getNextField(buf, cname, j);
    cbranchNum = getMappedBranch(cname);
    j = getNextField(buf, num, j);
    value = atof(num);

    inst = CALLOC(ccvs, 1);
    inst->name = (char *)strdup(name);
    inst->pNode = nodeA;
    inst->nNode = nodeB;
    inst->branchNum = branchNum ;
    inst->cbranchNum = cbranchNum ;
    inst->Rt = value;
    Hsrc[numHsrc] = inst;
}

void printHsrc(Hsrc, numHsrc)
ccvs *Hsrc[];
int numHsrc;
{
    int i;
    ccvs *inst;
    for(i = 1; i <= numHsrc; i++) {
	inst = Hsrc[i];
	printf("%s\t%s\t%s\t%s\t%f\n", inst->name, NodeArray[inst->pNode], NodeArray[inst->nNode], BranchArray[inst->cbranchNum],  inst->Rt);
    }
}

void setupHsrc(Hsrc, numHsrc)
ccvs *Hsrc[];
int numHsrc;
{
    int i;
    ccvs *inst;

    /* do any preprocessing steps here */
   //Pushing Branch number columns after the Node numbers
    for(i = 1; i <= numHsrc; i++) {
	inst = Hsrc[i];
	inst->branchNum += NumNodes;
	inst->cbranchNum += NumNodes;
    }
}

void stampHsrc(Hsrc, numHsrc, cktMatrix, rhs)
ccvs *Hsrc[];
int numHsrc;
double **cktMatrix;
double *rhs;
{
    int i, pNode, nNode, cbranchNum, branchNum;
    double Rt ;
    /* stamp H source*/
    for(i = 1; i <= numHsrc; i++) {
	pNode      = Hsrc[i]->pNode;
	nNode      = Hsrc[i]->nNode;
	cbranchNum = Hsrc[i]->cbranchNum;
	branchNum  = Hsrc[i]->branchNum;
        Rt         = Hsrc[i]->Rt;

        //KCL for pNode & nNode
 	cktMatrix[pNode][branchNum] += 1; //I leaving pNode
 	cktMatrix[nNode][branchNum] -= 1; //I entering nNode
        //BCE for the CCVS : Vp-Vn-I*Rt = 0
 	cktMatrix[branchNum][pNode] += 1;
 	cktMatrix[branchNum][nNode] -= 1;
 	cktMatrix[branchNum][cbranchNum] -= Rt;
    
    }
}
