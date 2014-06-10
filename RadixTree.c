
#include "RadixTree.h"


#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))



RadixNode * create(){
		RadixNode * res = malloc(sizeof(RadixNode));
		res->num_edges = 0;
		res->edge_len = 0;
		return res;
}

/**
 * Insert edge into the specific nodes, edge array 
 * 
 */
void insert_in_array(RadixNode * node, RadixEdge * edge){
	//If true, we have to increase array space.
	if ( node->num_edges + 1 > node->edge_len ) {
		node->edge_len += ARRAY_G_FACTOR;
		RadixEdge ** tmp = realloc (node->edges, node->edge_len * sizeof(RadixEdge*));
		if(tmp == NULL ){
			free(tmp);
			exit(1);
		}
		node->edges = tmp;
	} 
	//Add the array.
	node->edges[node->num_edges] = edge;
	node->num_edges++;
}
/**
 * Helps setting the value of edge, only used for making code prettier.
 */ 
void set_label(RadixEdge * edge, char * value){
	if(edge == NULL ){
		return;
	}
	edge->label = malloc(sizeof(char)*strlen(value));
	memcpy(edge->label, value,sizeof(char)*strlen(value));
	edge->label_len = strlen(edge->label);	//Since otherwise we would have to do this alot!
}

/**
 * 
 */
int max_prefix_len(char * str1, char * prefix ){
	int s1_len = strlen(str1);
	int s2_len = strlen(prefix);
	int i = 0;
	while( ( i < s1_len && i < s2_len )  && str1[i] == prefix[i]){
		i++;
	}
	fprintf(stderr,"Jag kommr retuenr %d\n",i);
	return i;
}
void insert(RadixNode * root, char * name, void * value){
	
	//~ //Create the actual new node.
	RadixNode * new_node = malloc(sizeof(RadixNode));
	int name_len = strlen(name);
	new_node->name = malloc(sizeof(char)*name_len);
	memcpy(new_node->name, name,sizeof(char)*name_len);
	new_node -> value = value;
	
	//New empty tree, insert immidiately.
	if(root->num_edges == 0 ){
		RadixEdge * edge = malloc(sizeof(RadixEdge));
		set_label(edge,name);
		edge->from = root;
		edge->target = new_node;
		insert_in_array(root, edge);
		return;
	}
	
	RadixNode * current_node = root;
	RadixEdge * current_edge = NULL;
	
	RadixNode * best_node = NULL;
	RadixEdge * best_edge = NULL;
	int max_prefix;
	while(current_node != NULL){
		max_prefix = 0;
		int i;
		
		//Find the longest prefix.
		for(i = 0; i< current_node -> num_edges; i++){
			
			int prefix_len = max_prefix_len(current_node->edges[i]->label, name);
			if(prefix_len > 0 && prefix_len > max_prefix ) {
				max_prefix = prefix_len;
				best_node = current_node;
				best_edge  =  current_node->edges[i];
			}
		}
	
		//To avoid iterating same edges.
		if(current_node == best_node || best_node == NULL){
			break;
		}
		
		current_node = best_node;
		current_edge = best_edge;
	}
	
	//Special case, no previous 
	if(max_prefix <= 0 ){
		RadixEdge * edge = malloc(sizeof(RadixEdge));
		set_label(edge,name);
		
		edge->from = current_node;
		edge->target = new_node;
		insert_in_array(current_node, edge);
		return;
	}
	fprintf(stderr,"%d -> \n", max_prefix);
	//~ if(max_prefix > current_edge->label_len){
//~ 
	//~ }
	//~ current_node = max_prefix_som_Stämmer;
	//~ resten av gamla prefix = new edge; 
	//~ restena av nya värdet = new edge;
//~ 
	//~ RadixEdge * edge = malloc(sizeof(RadixEdge));
	//~ set_label(edge,&name[current_edge->label_len]);
	//~ edge->from = current_node;
	//~ edge->target = new_node;
	//~ insert_in_array(current_node, edge);
	
}

void delete();

RadixNode * find(char * name);
