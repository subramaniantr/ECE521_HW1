#include "macros.h"
#include "defs.h"
#include "dio.h"

void makeDio(Dio, numDio, buf)
diode *Dio[];
int numDio;
char *buf;
{
    diode *inst;
    int j, nodeA, nodeB, atoi();
    char name[MAXFIELD], mname[MAXFIELD], node[MAXFIELD], num[MAXFIELD];
    double value, atof();

    j = 0;	
    j = getNextField(buf, name, j);
    j = getNextField(buf, node, j);
    nodeA = getMappedNode(node);
    j = getNextField(buf, node, j);
    nodeB = getMappedNode(node);
    j = getNextField(buf, mname, j);
    j = getNextField(buf, num, j);
    value = atof(num);

    inst = CALLOC(diode, 1);
    inst->name = (char *)strdup(name);
    inst->pNode = nodeA;
    inst->nNode = nodeB;
    inst->mname = (char *)strdup(mname);
    inst->area = value;
    Dio[numDio] = inst;
}

void printDio(Dio, numDio)
diode *Dio[];
int numDio;
{
    int i;
    diode *inst;

    for(i = 1; i <= numDio; i++) {
	inst = Dio[i];
	printf("%s\t%s\t%s\t%s\t%f\n", inst->name, NodeArray[inst->pNode], NodeArray[inst->nNode], inst->mname, inst->area);
    }
}

void setupDio(Dio, numDio)
diode *Dio[];
int numDio;
{
    int i;
    diode *inst;

    /* do any preprocessing steps here */
    for(i = 1; i <= numDio; i++) {
    }
}
