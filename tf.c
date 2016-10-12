#include "macros.h"
#include "defs.h"
#include "tf.h"

void makeTf(Tf, numTf, buf)
transformer *Tf[];
int numTf;
char *buf;
{
    transformer *inst;
    int j, nodeA, nodeB, nodeC, nodeD, branchNum, atoi();
    char name[MAXFIELD], node[MAXFIELD], num[MAXFIELD];
    double value, atof();

    j = 0;	
    j = getNextField(buf, name, j);
    NumBranches++; // Adding an extra Branch current variable
    branchNum = NumBranches;
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

    inst = CALLOC(transformer, 1);
    inst->name = (char *)strdup(name);
    inst->p2Node = nodeA;
    inst->n2Node = nodeB;
    inst->p1Node = nodeC;
    inst->n1Node = nodeD;
    inst->branchNum = branchNum ;
    inst->n = value;
    Tf[numTf] = inst;
}

void printTf(Tf, numTf)
transformer *Tf[];
int numTf;
{
    int i;
    transformer *inst;
    for(i = 1; i <= numTf; i++) {
	inst = Tf[i];
	printf("%s\t%s\t%s\t%s\t%s\t%f\n", inst->name, NodeArray[inst->p1Node], NodeArray[inst->n1Node], NodeArray[inst->p2Node], NodeArray[inst->n2Node], inst->n);
    }
}

void setupTf(Tf, numTf)
transformer *Tf[];
int numTf;
{
    int i;
    transformer *inst;

    /* do any preprocessing steps here */
   //Pushing Branch number columns after the Node numbers
    for(i = 1; i <= numTf; i++) {
	inst = Tf[i];
	inst->branchNum += NumNodes;
    }
}

void stampTf(Tf, numTf, cktMatrix, Rhs)
transformer *Tf[];
int numTf;
double **cktMatrix;
double *Rhs;
{
    int i, p2Node, n2Node, p1Node, n1Node, branchNum;
    double n ;
    /* stamp N source*/
    for(i = 1; i <= numTf; i++) {
	p2Node = Tf[i]->p2Node;
	n2Node = Tf[i]->n2Node;
	p1Node = Tf[i]->p1Node;
	n1Node = Tf[i]->n1Node;
	branchNum = Tf[i]->branchNum;
        n   = Tf[i]->n;
        //KCL for p2Node,n2Node,p1Node and n1Node
 	cktMatrix[p1Node][branchNum] += 1;
 	cktMatrix[n1Node][branchNum] -= 1;
 	cktMatrix[p2Node][branchNum] -= n; 
 	cktMatrix[n2Node][branchNum] += n;
        //BCE for Transformer : (V1p-V1n)-n*(V2p-V2n)=0
 	cktMatrix[branchNum][p1Node] += 1;
 	cktMatrix[branchNum][n1Node] -= 1;
 	cktMatrix[branchNum][p2Node] -= n;
 	cktMatrix[branchNum][n2Node] += n;
    }
}
