#include "Version.h"

#if defined(MYINSTNODE_S)
#warning("using my insert_node.S")
#else
#warning("using my Cinsert_node.c")

#include <stdlib.h>
#include <string.h>
#include "node.h"

node *insert_node(char *id, unsigned long height, unsigned long x, unsigned long y, node *front) {
	(void) front; // suppress unused variable warnings
	(void) id; // TODO: delete these once you start implementing insert_node
	(void) height;
	(void) x;
	(void) y;
	
	// TODO: create a node, copy in the parameter fields
	// make sure that you do a deep copy
	
	// TODO: link the new node into the chain 

	// TODO: return the new head of the chain if the function succeeded
	
	return NULL; // TODO: replace this once you implement
}
#endif
