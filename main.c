#include <stdio.h>
#include "macros.h"
#include "defs.h"
#include "res.h"
#include "isrc.h"
#include "vsrc.h"
#include "vcvs.h"
#include "cccs.h"
#include "vccs.h"
#include "ccvs.h"
#include "dio.h"
#include "tf.h"
#include "gyro.h"
#include "opamp.h"

int NumNodes = 0;
int NumBranches = 0;
char **NodeArray;
char **BranchArray;

main(ac, av)
char **av;
{
    char *inFile;
    FILE *fopen(), *fpIn;
    char buf[MAXLINE];
    resistor 	*Res[MAXELEM];
    isource	*Isrc[MAXELEM];
    vsource	*Vsrc[MAXELEM];
    vcvs	*Esrc[MAXELEM];
    cccs	*Fsrc[MAXELEM];
    vccs	*Gsrc[MAXELEM];
    ccvs	*Hsrc[MAXELEM];
    diode    	*Dio[MAXELEM]; 
    transformer    *Tf[MAXELEM]; 
    gyrator    *Gyro[MAXELEM]; 
    opamp      *Op[MAXELEM]; 
    int i = 0;
    int j = 0;
    int numRes = 0;
    int numIsrc = 0;
    int numVsrc = 0;
    int numEsrc = 0;
    int numFsrc = 0;
    int numGsrc = 0;
    int numHsrc = 0;
    int numDio = 0;
    int numTf = 0;
    int numGyro = 0;
    int numOp = 0;
    int numEqns;
    double **cktMatrix;
    double *Rhs;

    switch (ac) {
        case 2:
            inFile = av[1];
            break;
        default:
            printf( "\n File Name Required \n");
            exit(-1);
    }
    /* initialization */
    NodeArray = CALLOC(char *, MAXNODE);
    BranchArray = CALLOC(char *, MAXBRANCH);
    for(i = 0; i < MAXNODE; i++) {
	NodeArray[i] = CALLOC(char, MAXFIELD);
    }
    for(i = 0; i < MAXBRANCH; i++ ) {
	BranchArray[i] = CALLOC(char, MAXFIELD) ;
    }
    /* fill in ground node */
    strcpy(NodeArray[0], (char *)"0");

    
    fpIn = fopen( inFile, "r" );
    while (fgets( buf, MAXLINE, fpIn ) != NULL) {
	if(tolower(buf[0]) == 'r') 
	{
	    /* resistor */
	    numRes++;
	    makeRes(Res, numRes, buf);
	} 
	else if(tolower(buf[0]) == 'i') 
	{
	    /* isource */
	    numIsrc++;
	    makeIsrc(Isrc, numIsrc, buf);
	}
	else if(tolower(buf[0]) == 'v') 
	{
	    /* vsource */
	    numVsrc++;
	    makeVsrc(Vsrc, numVsrc, buf);
	}
	else if(tolower(buf[0]) == 'e') 
	{
	    /* vcvs */
	    numEsrc++;
	    makeEsrc(Esrc, numEsrc, buf);
	}
	else if(tolower(buf[0]) == 'f') 
	{
	    /* cccs */
	    numFsrc++;
	    makeFsrc(Fsrc, numFsrc, buf);
	}
	else if(tolower(buf[0]) == 'g') 
	{
	    /* vccs */
	    numGsrc++;
	    makeGsrc(Gsrc, numGsrc, buf);
	}
	else if(tolower(buf[0]) == 'h') 
	{
	    /* ccvs */
	    numHsrc++;
	    makeHsrc(Hsrc, numHsrc, buf);
	}
	else if(tolower(buf[0]) == 'd') 
	{
	    /* diode */
	numDio++;
	    makeDio(Dio, numDio, buf);
	}
	else if(tolower(buf[0]) == 'n') 
	{
	    /* transformer */
	numTf++;
	    makeTf(Tf, numTf, buf);
	}
	else if(tolower(buf[0]) == 't') 
	{
	    /* gyrator */
	numGyro++;
	    makeGyro(Gyro, numGyro, buf);
	}
	else if(tolower(buf[0]) == 'o') 
	{
	    /* opamp */
	numOp++;
	    makeOp(Op, numOp, buf);
	}
    }
    fclose( fpIn );

    /* print circuit elements */
    printRes(Res, numRes);
    printIsrc(Isrc, numIsrc); 
    printVsrc(Vsrc, numVsrc); 
    printEsrc(Esrc, numEsrc); 
    printFsrc(Fsrc, numFsrc); 
    printGsrc(Gsrc, numGsrc); 
    printHsrc(Hsrc, numHsrc); 
    printDio(Dio, numDio);
    printTf(Tf, numTf);
    printGyro(Gyro, numGyro);
    printOp(Op, numOp);

    /* setup circuit matrix */
    numEqns = NumNodes+NumBranches+1;
    cktMatrix = CALLOC(double *, numEqns);
    for(i = 0; i <= NumNodes+NumBranches; i++) {
	cktMatrix[i] = CALLOC(double, numEqns);
    }

    /* setup Rhs vector */
    Rhs = CALLOC(double, numEqns);
    
    /* do any preprocessing */
    setupRes(Res, numRes);
    setupVsrc(Vsrc, numVsrc);
    setupEsrc(Esrc, numEsrc);
    setupFsrc(Fsrc, numFsrc);
    setupGsrc(Gsrc, numGsrc);
    setupHsrc(Hsrc, numHsrc);
    setupIsrc(Isrc, numIsrc);
    setupDio(Dio, numDio);
    setupTf(Tf, numTf);
    setupGyro(Gyro, numGyro);
    setupOp(Op, numOp);

    /* stamp circuit matrix */
    stampRes(Res, numRes, cktMatrix, Rhs);
    stampIsrc(Isrc, numIsrc, cktMatrix, Rhs);
    stampVsrc(Vsrc, numVsrc, cktMatrix, Rhs);
    stampEsrc(Esrc, numEsrc, cktMatrix, Rhs);
    stampFsrc(Fsrc, numFsrc, cktMatrix, Rhs);
    stampGsrc(Gsrc, numGsrc, cktMatrix, Rhs);
    stampHsrc(Hsrc, numHsrc, cktMatrix, Rhs);
    stampTf(Tf, numTf, cktMatrix, Rhs);
    stampGyro(Gyro, numGyro, cktMatrix, Rhs);
    stampOp(Op, numOp, cktMatrix, Rhs);

    /* print circuit matrix */
    printf("\n");
    printMatrix(cktMatrix, NumNodes+NumBranches);

    /* print Rhs vector */
    printf("\nRHS\n");
    for(i = 1; i <= NumNodes+NumBranches; i++) {
	printf(" %9.3g\n",Rhs[i]);
    }
}
