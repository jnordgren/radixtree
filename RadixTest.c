#include "RadixTest.h"
#include "AceUnitData.h"	//BS. that this has to be included

#include "RadixTree.h"

A_Test void testRadixInsertionsAndFinds() {
		RadixNode * root = create();
		char * val1 = "hej sa petronella";
		char * val2 = "ipsum_dollares";
		char * val3 = "€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€";
		char * val4 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
		char * val5 = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
		char * val6 = "popiyguyhashdsgjsdfuhiuwhiujadsiuhiuahfohtåphlåptlåprlhåpelhgopjkdg";
		insert(root,"petronella",val1);
		insert(root,"bilen",val3);
		insert(root,"peter",val2);
		insert(root,"petelapa",val2);
		
		
		
		
		//~ fprintf(stderr,"Nu kommer bassningen **************\n");
		insert(root,"bassning",val5);
		insert(root,"banankaka",val4);
pretty_print(root,0);
		insert(root,"båẗen heter anna",val6);

		pretty_print(root,0);
		RadixNode * found = find(root,"NoTHEREMATE");
		assertEquals("This name should not be found",found,NULL);
		found = find(root,"petronella");
		//~ assertNotNull("petronella : val1", found);
//~ 
		//~ assertEquals("petronella : val1", found->value,val1);
		//~ 
		//~ found = find(root,"peter");
		//~ assertNotNull("peter - not found", found);
		//~ assertEquals("peter : val2", found->value,val2);
		//~ 
		//~ found = find(root,"bilen");
		//~ assertNotNull("bilen - not found", found);
		//~ assertEquals("bilen : val3", found->value,val3);
		//~ 
		//~ found = find(root,"banankaka");
		//~ assertNotNull("banankaka - not found", found);
		//~ assertEquals("banankaka : val4", found->value,val4);
		
		found = find(root,"bassning");
		assertNotNull("bassning - not found", found);
		assertEquals("bassning : val5", found->value,val5);
}
A_Test void testRadixSimpleInsertions() {
		RadixNode * root = create();
		
		assertNotEquals("Create new tree", NULL, root);
		
		char * special_value = "987654321_abcdf";
		char * special_value2 = "lorem_impsum_dolares";
		
		/** Insert Value **/
		insert(root, "apan", special_value);
		
		assertEquals("Should have 1 edge by now", root->num_edges,1);
		
		assertEquals("Edge should point to root now", root->edges[0]->from,root);
		assertNotEquals("Target for edge should not be null!", root->edges[0]->target,NULL);
		assertEquals("Edge should point to node containing inserted value", root->edges[0]->target->value,special_value);
		
		
		insert(root, "kalle", special_value);
		assertEquals("Root should have 2 edges", root->num_edges,2);
		assertEquals("Edge should point to root now", root->edges[1]->from,root);
		
		assertEquals("Edge should point to node containing inserted value", root->edges[1]->target->value,special_value);
		
		
		assertEquals("Edge name should be", 0,strncmp(root->edges[1]->label,"kalle",strlen("kalle")));

		/** Insert Value **/
		insert(root, "kajsa", special_value2);
		
		assertEquals("Root should have 2 edges", root->edges[1]->target->num_edges,2);

		
		//Test for properply handling labels
		assertEquals("Edge name should be 'lle'", 0,strncmp(root->edges[1]->target->edges[0]->label,"lle",strlen("lle")));
		assertEquals("Edge name should be 'jsa' ", 0,strncmp(root->edges[1]->target->edges[1]->label,"jsa",strlen("jsa")));

		//test values
		assertEquals("Valued not stored properly for key 'kalle' '", special_value,root->edges[1]->target->edges[0]->target->value );
		assertEquals("Valued not stored properly for key 'kajsa' ", special_value2,root->edges[1]->target->edges[1]->target->value );

		/** Insert Value **/
		insert(root, "test", special_value);
		
		assertEquals("Should have 3 edge by now", root->num_edges,3);
		
		assertEquals("Should contain label 'test'", 0,strncmp(root->edges[2]->label,"test", strlen("test")));
	
		/** Insert Value **/
		insert(root, "team", special_value);

		//~ fprintf(stderr,"Label: %s\n" , node->edges[0]->label);
		assertEquals("Should have  label 'test'", 0,strncmp(root->edges[2]->label,"test", strlen("te")));

		assertEquals("Should have 1 edge by now", root->edges[2]->target->num_edges,2);

		assertEquals("Should have  label te-'st'", 0,strncmp(root->edges[2]->target->edges[0]->label,"st", strlen("st")));
		assertEquals("Should have  label te-'am'", 0,strncmp(root->edges[2]->target->edges[1]->label,"am", strlen("am")));
		assertNotEquals("Should not have  4 edge by now", root->num_edges,4);
		
		/** Insert Value **/
		insert(root, "toast", special_value);
		assertEquals("Should have  label 't'", 0,strncmp(root->edges[2]->label,"t", strlen("t")));
		assertEquals("Should have  2 edges ", root->edges[2]->target->num_edges,2);
		
		assertEquals("Should have  label t'e'", 0,strncmp(root->edges[2]->target->edges[0]->label,"e", strlen("e")));
		assertEquals("Should have  label t'oast'", 0,strncmp(root->edges[2]->target->edges[1]->label,"oast", strlen("oast")));

		
}


int main(int argc, char *argv[]) {
	runFixture(&RadixTestFixture);
	return 0;
}
