#include "RadixTest.h"
#include "AceUnitData.h"	//BS. that this has to be included

#include "RadixTree.h"

A_Test void testRadix() {
		RadixNode * root = create();
		
		assertNotEquals("Create new tree", NULL, root);
		
		char * special_value = "987654321_abcdf";
		insert(root, "apan", special_value);
		
		assertEquals("Should have 1 edge by now", root->num_edges,1);
		
		assertEquals("Edge should point to root now", root->edges[0]->from,root);
		assertNotEquals("Target for edge should not be null!", root->edges[0]->target,NULL);
		assertEquals("Edge should point to node containing inserted value", root->edges[0]->target->value,special_value);
		
		
		insert(root, "kalle", special_value);
		assertEquals("Root should have 2 edges", root->num_edges,2);
		assertEquals("Edge should point to root now", root->edges[1]->from,root);
		
		assertEquals("Edge should point to node containing inserted value", root->edges[1]->target->value,special_value);

}


int main(int argc, char *argv[]) {
	runFixture(&RadixTestFixture);
	return 0;
}
