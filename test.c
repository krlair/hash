#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hash.h"

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
