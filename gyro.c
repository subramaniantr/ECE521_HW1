#include "macros.h"
#include "defs.h"
#include "gyro.h"

void makeGyro(Gyro, numGyro, buf)
gyrator *Gyro[];
int numGyro;
char *buf;
{
    gyrator *inst;
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

    inst = CALLOC(gyrator, 1);
    inst->name = (char *)strdup(name);
    inst->p2Node = nodeA;
    inst->n2Node = nodeB;
    inst->p1Node = nodeC;
    inst->n1Node = nodeD;
    inst->g = value;
    Gyro[numGyro] = inst;
}

void printGyro(Gyro, numGyro)
gyrator *Gyro[];
int numGyro;
{
    int i;
    gyrator *inst;
    for(i = 1; i <= numGyro; i++) {
	inst = Gyro[i];
	printf("%s\t%s\t%s\t%s\t%s\t%f\n", inst->name, NodeArray[inst->p2Node], NodeArray[inst->n2Node], NodeArray[inst->p1Node], NodeArray[inst->n1Node], inst->g);
    }
}

void setupGyro(Gyro, numGyro)
gyrator *Gyro[];
int numGyro;
{
    int i;
    gyrator *inst;

    /* do any preprocessing steps here */
   //Pushing Branch number columns after the Node numbers
    for(i = 1; i <= numGyro; i++) {
    }
}

void stampGyro(Gyro, numGyro, cktMatrix, Rhs)
gyrator *Gyro[];
int numGyro;
double **cktMatrix;
double *Rhs;
{
    int i, p2Node, n2Node, p1Node, n1Node;
    double g ;
    /* stamp T source*/
    for(i = 1; i <= numGyro; i++) {
	p2Node = Gyro[i]->p2Node;
	n2Node = Gyro[i]->n2Node;
	p1Node = Gyro[i]->p1Node;
	n1Node = Gyro[i]->n1Node;
        g      = Gyro[i]->g;
        //KCL for p2Node,n2Node,p1Node and n1Node
 	cktMatrix[p1Node][p2Node] -= g; 
 	cktMatrix[p1Node][n2Node] += g;
 	cktMatrix[n1Node][p2Node] += g;
 	cktMatrix[n1Node][n2Node] -= g;
 	cktMatrix[p2Node][p1Node] += g;
 	cktMatrix[p2Node][n1Node] -= g;
 	cktMatrix[n2Node][p1Node] -= g;
 	cktMatrix[n2Node][n1Node] += g;
    }
}
