/* information used to describe a single instance */

typedef struct transformer{
    char *name;  /* pointer to character string naming this vcvs */
    int p2Node; /* number of positive node of vcvs */
    int n2Node; /* number of negative node of vcvs */
    int p1Node; /* number of positive control node of vcvs */
    int n1Node; /* number of negative control node of vcvs */
	int branchNum ; /* number of branch */
    int n;  /* value of n */
} transformer ;

