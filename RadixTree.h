#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define ARRAY_G_FACTOR 2

 
typedef struct RadixNode{
	void * value;
	char * name;
	int num_edges;
	int edge_len;
	struct RadixEdge ** edges;

} RadixNode;

typedef struct RadixEdge{
	RadixNode * from;
	RadixNode * target;
	char * label;
	int label_len;
} RadixEdge;

int error_code;

RadixNode * create();

void insert(RadixNode * root, char * name, void * value);

void delete();

RadixNode * find(RadixNode * root,char * name);

void * find_value(RadixNode * root,char * name);

void pretty_print(RadixNode * root, int tabs);
