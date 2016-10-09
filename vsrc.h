/* information used to describe a single instance */

typedef struct vsource{
    char *name;  /* pointer to character string naming this vsource */
    int pNode; /* number of positive node of vsource */
    int nNode; /* number of negative node of vsource */
	int branchNum ; /* number of branch */
    double voltage;  /* value of vsource */
} vsource ;

