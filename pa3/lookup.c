#include "Version.h"
#if !defined(MYMAIN)
#warning("using solution main")
#else
#warning("using my lookup.c")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "node.h"

#define MIN_TAB_SZ 3
#define DEFAULT_TAB_SZ 1873
#define QUERY_SUCCESS_FORMAT "found tree id=%s, height=%lu, x=%lu, y=%lu\n"
#define QUERY_FAILURE_FORMAT "could not find tree with id=%s\n"

int main(int argc, char **argv) {
	int s_flag;
	unsigned long tabsz;
	s_flag = 0;
	tabsz = DEFAULT_TAB_SZ;
	char *filename = NULL;
	int opt;
	while ((opt = getopt(argc, argv, "st:")) != -1)
	{
		switch (opt)
		{
			case 's':
				s_flag = 1;
				break;
			case 't':
				tabsz = strtoul(optarg, NULL, 10);
				if (tabsz < MIN_TAB_SZ)
				{
					tabsz = DEFAULT_TAB_SZ;
					break;
				}
				else
				{
					break;
				}
			default:
				fprintf(stderr, "Usage: %s [-s] [-t tablesize] filename\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}
	if(optind >= argc)
	{
		fprintf(stderr, "Expected filename after options\n");
		exit(EXIT_FAILURE);
	}
	filename = argv[optind];


	
	// TODO: initialze htable
	// using calloc so all buckets are initialized to NULL
	node **htable = calloc(tabsz, sizeof(node *));
	if (htable == NULL) {
		perror("calloc")
		return EXIT_FAILURE;
	}
	
	
	char *filename = /* TODO: fill in */

	if (load_table(filename, htable, tabsz) != 0) {
		fprintf(stderr, "error in load_table\n");
		free(htable);
		return EXIT_FAILURE;
	}
	
	size_t bufsz = 0;
	char *buf = NULL; 
	int successful_query = 0;
	
	// read one line at a time from stdin, do a lookup for that id
	// 
	ssize_t bytes;
	while ((bytes = getline(&buf, &bufsz, stdin)) > 0) {
		// replace the \n, if it exists (for hashing)
		if (buf[bytes - 1] == '\n') buf[bytes - 1] = '\0';
		node *result = node_lookup(buf, htable, tabsz);
        if (result) {
            printf(QUERY_SUCCESS_FORMAT, result->id, result->height, result->xcoord, result->ycoord);
            successful_query++;
        } else {
            printf(QUERY_FAILURE_FORMAT, buf);
        }
		// TODO: read a line from stdin and perform a lookup
		// if the tree is found, print its x and y to stdout
		// using QUERY_SUCCESS_FORMAT
		//
		// if the tree is not found, print a message to **stdout**
		// using QUERY_FAILURE_FORMAT
		//
		// keep track of the number of successful queries
	}
	printf("%d successful queries\n", successful_query);

	// if -s called then print stats
	if (s_flag) {
		print_info(htable, tabsz);
	}

	// TODO: free all allocated memory associated with the table 
	// using delete_table()
	//
	delete_table(htable, tabsz);
	free(buf);  // free the buffer allocated by getline()
	free(htable); 
	return EXIT_SUCCESS;
}
#endif
