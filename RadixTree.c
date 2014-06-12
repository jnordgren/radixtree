
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
void set_label(RadixEdge * edge, char * value, int len){
	if(edge == NULL ){
		return;
	}
	edge->label = malloc(sizeof(char)*len);
	memcpy(edge->label, value,sizeof(char)*len);
	edge->label_len = strlen(edge->label);	//Since otherwise we would have to do this alot!
}

/**
 * Returns the lenght longest prefix where matched indicates at which index the c
 * comparison should start for argument 1.
 * returns the match length.
 */
int max_prefix_len(char * str1, char * prefix, int matched){
	int s1_len = strlen(str1);
	int s2_len = strlen(prefix);
	int i = 0;
	while( ( i < s1_len && i < s2_len )  && str1[i+matched] == prefix[i]){
		i++;
	}
	return i;
}
int is_prefix(char * str, char * prefix, int matched){
	return (0==strncmp(&str[matched],prefix,strlen(prefix)) ? true: false);
}

typedef struct Pair{
	int m_len;
	int p_len;
	RadixEdge * edge;
}Pair;

Pair * find_node(RadixNode * current, RadixEdge * current_edge, char * name, int match, int max_prefix){
	
	//~ if(current->num_edges <= 0 ){
		//~ Pair  * p = malloc(sizeof(Pair)); 
		//~ p->edge = current_edge;
		//~ p->m_len = match;
		//~ p->p_len = max_prefix;
		//~ return p;
	//~ }
	int i=0;
	RadixEdge * best_edge = NULL;
	int longest_prefix = -1;
	for(;i<current->num_edges; i++){
		int prefix_len = max_prefix_len(name,current->edges[i]->label,match);
		
		if(prefix_len > 0 ) {
			return find_node(current->edges[i]->target, current->edges[i], name, match + prefix_len, prefix_len);
		}
		
	}
	Pair  * p = malloc(sizeof(Pair)); 
	p->edge = current_edge;
	p->m_len = match;
	p->p_len = max_prefix;

	return p;
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
		set_label(edge,name,strlen(name));
		edge->from = root;
		edge->target = new_node;
		insert_in_array(root, edge);
		return;
	}
	

	
	Pair * edge_pair = find_node(root, NULL, name, 0,0);
	RadixEdge * best_edge =  edge_pair -> edge;
	//If true, we have to add new edge to root.
	if(NULL == best_edge){
		
		RadixEdge * edge = malloc(sizeof(RadixEdge));
		set_label(edge,name,strlen(name));
		edge->from = root;
		edge->target = new_node;
		insert_in_array(root, edge);
		return;
	}
	//~ fprintf(stderr,"Kanten i fann heter : %s matchning: %d på namnet :%s\n", best_edge->label, edge_pair->m_len, name);
	RadixEdge * new_edge = malloc(sizeof(RadixEdge));
	set_label(new_edge,&name[edge_pair->m_len],strlen(name)-edge_pair->m_len);
	//New edge point to new node (the node continag the value)
	new_edge->target = new_node;
		
		
	//in this we only have to add our new edge.
	if(strlen(best_edge->label) == edge_pair -> p_len ) {
		insert_in_array(best_edge->target, new_edge);
	}
	else{
		RadixEdge * old_new_edge = malloc(sizeof(RadixEdge));
		
		set_label(old_new_edge, &best_edge->label[edge_pair->p_len], strlen(best_edge->label) - edge_pair->p_len);
		
		old_new_edge->target = best_edge -> target;
		//empty intermediate node
		RadixNode * inter_mediate = malloc(sizeof(RadixNode));
		best_edge -> target = inter_mediate;
		

		//Add both new edges to intermediate node.
		insert_in_array(inter_mediate, old_new_edge);
		insert_in_array(inter_mediate, new_edge);
		
		//Update old label (the parent label)
		set_label(best_edge, best_edge->label,  edge_pair->p_len); 

	}
	//~ new_edge->from = best_edge->;
	//~ new_edge->target = new_node;
	//~ best_edge->from
	//Uppdatera kanten.
	//Flytta ner det som blir över.
	//Stoppa in nya värdet.
	
	
	//~ fprintf(stderr,"broke that shit\n");
	//~ assert(current_node != NULL);
	
	//Special case, no previous 
	//~ if(max_prefix <= 0 ){
		//~ RadixEdge * edge = malloc(sizeof(RadixEdge));
		//~ set_label(edge,name,strlen(name));
		//~ 
		//~ edge->from = current_node;
		//~ edge->target = new_node;
		//~ insert_in_array(current_node, edge);
		//~ return;
	//~ }
	//~ assert(current_edge != NULL);
	
	
	//~ RadixEdge * new_edge_old =  malloc(sizeof(RadixEdge));
	//~ RadixEdge * new_edge_new =  malloc(sizeof(RadixEdge));
	//~ 
	//~ fprintf(stderr,"Den kanten vi valde var: %s\n", current_edge->label);
	//~ RadixNode * new_sub_node =  malloc(sizeof(RadixNode));
	//~ 
	//~ new_edge_old->from = new_sub_node;
	//~ new_edge_old->target = current_edge->target;
	//~ set_label(new_edge_old, &current_edge->label[max_prefix], strlen(current_edge->label));
	//~ fprintf(stderr,"First label = %s\n", new_edge_old->label); 
	//~ new_edge_new ->target = new_node;
	//~ new_edge_new->from = new_sub_node;
	//~ set_label(new_edge_new, &name[max_prefix], strlen(name)-max_prefix);
	//~ fprintf(stderr,"Second label = %s\n", new_edge_new->label);
	//~ current_edge->target = new_sub_node;
	//~ 
	//~ //Set label to the maximal matched prefix.
	//~ set_label(current_edge,current_edge->label,max_prefix);
	//~ 
	//~ //Set correct label.
	//~ insert_in_array(new_sub_node, new_edge_old);
	//~ insert_in_array(new_sub_node, new_edge_new);

	
}

void delete();

RadixNode * find(RadixNode * root, char * name){
	
	RadixNode * current_node = root;
	RadixEdge * current_edge = NULL;
	int matched = 0;
	int name_len = strlen(name);
	bool prefix_match = false;
	int i;
	while(root != NULL && matched < name_len){
		for(i = 0; i<current_node->num_edges; i++){
			if( true == is_prefix(name, current_node->edges[i]->label, matched) ){
					//~ fprintf(stderr," det i matchad: %s == %s med match %d\n", name, current_node->edges[i]->label, matched);
					current_edge = current_node->edges[i];
					prefix_match = true;
					//~ fprintf(stderr,"prefix = %s mat = %d\n", current_node->edges[i]->label,matched);
					break; 
			}
		}
		if(!prefix_match){	//If no prefix is matched, value does not exist.
			break;
		}
		else{
			//~ fprintf(stderr,"inana e matched %d s: %s\n", matched,current_edge->label);
			matched += strlen(current_edge->label);
			current_node = current_edge->target;
			
			//~ fprintf(stderr, "vad böor denna %d %d\n", is_prefix("bassning", "pet", 0),true);
			return NULL;
		}
		
	}
	//~ fprintf(stderr,"matched = %d\n", matched);
	return (matched==name_len && 0 == current_edge->target->num_edges ? current_edge->target : NULL);
}

void * find_value(RadixNode * root,char * name){
	return find(root,name)->value;
}

void print_tabs(int tabs){
	while(tabs--){
		printf("\t");
	}
}
void pretty_print(RadixNode * root, int tabs){
		RadixNode * current = root;
		int i = 0;
			
			for( i = 0; i< current->num_edges; i++){
				print_tabs(tabs);
				printf("'%s'\n",current->edges[i]->label);
				if(current->edges[i]->target->num_edges > 0 ){
					pretty_print(current->edges[i]->target,tabs+1);
				}
			}
		
}
