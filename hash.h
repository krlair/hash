#define NUM_BUCKETS 47 

typedef struct Node {
	char * value;
	struct Node * next; 
} NODE;

/*list of functions to assess the hash table */

NODE * lookup(NODE **, char *); //if you include the variable name, they must be implement with that exact name
int hash(char *);
void insert(NODE **, char *);
void print(NODE **);