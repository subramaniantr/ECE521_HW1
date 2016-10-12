typedef struct transformer{
    char *name;  /* pointer to character string naming this transformer */
    int p2Node; /* number of positive node of transformer */
    int n2Node; /* number of negative node of transformer */
    int p1Node; /* number of positive control node of transformer */
    int n1Node; /* number of negative control node of transformer */
    int branchNum ; /* number of branch */
    double n;  /* value of n */
} transformer ;

