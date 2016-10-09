/* information used to describe a single instance */

typedef struct resistor{
    char *name;  /* pointer to character string naming this instance */
    int pNode; /* number of positive node of resistor */
    int nNode; /* number of negative node of resistor */

    double value;  /* resistance */
    double conduct;  /* conductance */
} resistor ;

