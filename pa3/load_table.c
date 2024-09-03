#include "Version.h"
#if !defined(MYLOADTABLE)
#warning("using solution load_table")
#else
#warning("using my load_table.c")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

#define MAX_LINELEN 100 
#define FILE_OPEN_ERR_MSG "error in load_table while opening file %s\n"
#define DUPLICATE_ID_MSG "load_table duplicate entry: %s\n"
#define INSERTION_ERROR_MSG "load_table could not create node for %s\n"

int load_table(node **htable, unsigned long int tabsz, char *filename) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr, FILE_OPEN_ERR_MSG, filename);
        return -1;
	}

	// TODO: open the file and check that it was successful

	// TODO: loop through the file and read one line at a time using fgets
	// see manual page for fgets for information on parameters
	char buf[MAX_LINELEN + 1]; // input buffer for fgets
	while (fgets(buf, MAX_LINELEN + 1, fp) == buf) {
		char *id = = strtok(buf, " ");
        char *height_str = strtok(NULL, " ");
        char *x_str = strtok(NULL, " ");
        char *y_str = strtok(NULL, "\n");
		unsigned long height = strtoul(height_str, NULL, 10);
        unsigned long x = strtoul(x_str, NULL, 10);
        unsigned long y = strtoul(y_str, NULL, 10);
		unsigned long hash_value = hash(id) % tabsz;
        node *existing_node = node_lookup(htable[hash_value], id);
        if (existing_node != NULL) {
            fprintf(stderr, DUPLICATE_ID_MSG, id);
            continue;
        }

        node *new_node = create_node(id, height, x, y);
        if (new_node == NULL) {
            fprintf(stderr, INSERTION_ERROR_MSG, id);
            continue;
        }
        new_node->next = htable[hash_value];
        htable[hash_value] = new_node;
    }

    fclose(fp);
		// TODO: for each line, use strtok to break it into columns
		// (convert the second, third, and fourth columns to unsigned longs)

		// TODO: get the corresponding chain for this entry
		
		// TODO: check that the node doesn't already exist in table

		// TODO: add non-duplicate node to the front of its chain

	return 0;
}
#endif
