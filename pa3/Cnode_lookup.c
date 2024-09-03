#include "Version.h"

#if defined(MYNODELOOKUP_S)
#warning("using my node_lookup.S")
#else
#warning("using my Cnode_lookup.c")

#include <string.h>
#include "node.h"

node *node_lookup(node *front, char *id) {
	// TODO: step through the chain pointed to by front
	// use function like strcmp to compare the id to the current node
	// if found return a pointer to the node, else return NULL
	
	(void) front; // suppress unused variable warnings 
	(void) id; // TODO: delete these when you start implementation 

	return NULL; // TODO: fix this when you start implementation
}
#endif
