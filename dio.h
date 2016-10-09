/* information used to describe a single instance */

typedef struct diode{
    char *name;  /* pointer to character string naming this instance */
    int pNode; /* number of positive node of resistor */
    int nNode; /* number of negative node of resistor */

    char *mname;  /* pointer to character string naming the model */
    double area;  /* area factor */
} diode ;

