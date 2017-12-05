#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_BUCKETS 47 // normally larger. We just picked a value.

//now we need a linked list to represent the lists in the buckets
//use typedef to shorten the name 
typedef struct Node {
	char * value; // we're storing strings 
	struct Node * next; // point to next node
} NODE; 
		// NODE is not a variable. If typedef was not there, it would be a variable
		// NODE can now be used to declare future variables instead of struct Node
		// NODE n vs struct Node n: these are the same

NODE * lookup(NODE ** htable, char * value);
int hash(char * value);
void insert(NODE ** htable, char * value);
void print(NODE ** htable);

/* Implement a lookup func to look for a given value in the hash table */
NODE * lookup(NODE ** htable, char * value) {

	//get index of hash_table
	int hash_value = hash(value);

	// go to start of linked list in appropriate bucket
	NODE * list = htable[hash_value];
	
	//advance until you find the element or reach the end
	while (list != NULL) {
		//compare value 
		if ((strcmp(list->value, value)) == 0)
			break;
		list = list->next;
	}

	// list will be NULL if it wasn't found
	// otherwise, list will still be pointing to the node containing the value
	return list;
}

/* Implement a function to hash a value */
int hash(char * value) {
	// convert value to an integer by adding ASCII values, multiplying, and modding
	// Make sure converted value will be bigger than the number of buckets
	// Otherwise, some buckets will never be used
	int i = 0;
	//treating value as a pointer. Advance ptr to next character in the string
	for (; *value != '\0'; value++) {
		// * value: character you are pointing to
		// cast this character to an int to get ASCII code
		// add that value to i
		i = i + (int)(*value);
	}
	//to make sure i > NUM_BUCKETS, multiply by some large prime
	// returns a value in [0, NUM_BUCKETS - 1]
	return (i * 1001) % NUM_BUCKETS;
}

/* Implement function to insert value into htable 
	Implement remove similarly */
void insert(NODE ** htable, char * value) {

	NODE * node = lookup(htable, value);
	
	// if value already exists in table
	if (node != NULL)
		return;

	// not found. create a new node
	int hash_value = hash(value);
	NODE * list = htable[hash_value];
	NODE * new_node = (NODE *)malloc(sizeof(NODE));
	new_node->value = (char *)malloc(strlen(value) + 1); // need space for /0
	sprintf(new_node->value, "%s", value); // copy value into new_node->vaue
	new_node->next = list; //add to the beginning of the list instead of having to iterate to end
	list = new_node;
	htable[hash_value] = list; /* This line fixes the error in class */

}

/* Print hash table contents */
void print(NODE ** htable) {
	for (int i = 0; i < NUM_BUCKETS; i++) {

		//print list htable i
		NODE * list = htable[i];
		if (list == NULL) continue;
		printf("Bucket #%d: ", i);
		while (list != NULL) {
			printf("%s ", list->value);
			list = list->next;
		}
		printf("\n");
	}
}

// main is for unit testing
int main() {

	// hashtable is a pointer pointing to Node *
	NODE ** hash_table;
	hash_table = (NODE**)malloc(NUM_BUCKETS * (sizeof(NODE *)));

	// initialize each list element so that it is empty
	for (int i = 0; i < NUM_BUCKETS; i++)
		hash_table[i] = NULL;

	insert(hash_table, "first string");
	insert(hash_table, "second string");

	print(hash_table);

	return 0;
}