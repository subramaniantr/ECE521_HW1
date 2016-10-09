
#include <stdio.h>
#include <strings.h>
#include "macros.h"
#include "defs.h"

int getNextField(input, field, start)
char *input, *field;
int start;
{
    int i, j;
    for(i=0; i < MAXFIELD; i++, j++) {
	field[i] = '\0';
    }
    for(i = 0, j = start; i < MAXFIELD; i++, j++) {
	if (input[j] == ' ' OR input[j] == '\n') break;
	field[i] = input[j];
    }
    /* strip trailing blanks */
    while( input[j] == ' ') j++;
    return( j );
}

/* map a nodename to an integer */
int getMappedNode(nodeName)
char *nodeName;
{
    int i;
    for(i = 0; i <= NumNodes; i++) {
	if(!strcmp(NodeArray[i], nodeName)) return( i );
    }
    /* node doesn't exist in NodeArray - so insert */
    NumNodes++;
    strcpy(NodeArray[NumNodes],  nodeName);
    return(NumNodes);
}

/* map a branch name to an integer */
int getMappedBranch(branchName)
char *branchName;
{
    int i;
    for(i = 0; i <= NumBranches; i++) {
	if(!strcmp(BranchArray[i], branchName)) return( i );
    }
    /* branch doesn't exist in BranchArray - so insert */
    NumBranches++;
    strcpy(BranchArray[NumBranches],  branchName);
    return(NumBranches);
}

/* code adapted from Sparse 1.3 */

void printMatrix(Matrix, Size)
double **Matrix;
int Size;
{
register  int  J = 0;
int I, Row, Col, Top, StartCol = 1, StopCol, Columns, ElementCount = 0;

/* Print header. */
    printf("MATRIX SUMMARY\n\n");
    printf("Size of matrix = %1d x %1d.\n", Size, Size);
    putchar('\n');

/* Set how many columns to use. */
    Columns = 8;

/*
 * Print matrix by printing groups of complete columns until all the columns
 * are printed.
 */
    J = 0;
    while ( J <= Size )

/* Calculate index of last column to printed in this group. */
    {   StopCol = StartCol + Columns - 1;
        if (StopCol > Size)
            StopCol = Size;

/* Print every row ...  */
        for (I = 1; I <= Size; I++)
        {   Row = I;
/* ... in each column of the group. */
            for (J = StartCol; J <= StopCol; J++)
            {   Col = J;
		printf(" %9.3g", Matrix[I][J]);
	    }
            putchar('\n');
	}

/* Calculate index of first column in next group. */
	StartCol = StopCol;
	StartCol++;
        putchar('\n');
    }
    return;
}

