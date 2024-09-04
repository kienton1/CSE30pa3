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

int load_table(node **htable, unsigned long int tabsz, char *filename) 
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, FILE_OPEN_ERR_MSG, filename);
        return -1;
    }

    char buf[MAX_LINELEN + 1]; // input buffer for fgets
    while (fgets(buf, MAX_LINELEN + 1, fp) != NULL) 
    {
        char *id = strtok(buf, ",");
        char *height_str = strtok(NULL, ",");
        char *x_str = strtok(NULL, ",");
        char *y_str = strtok(NULL, "\n");

        if (id == NULL || height_str == NULL || x_str == NULL || y_str == NULL) {
            fprintf(stderr, "Malformed line in file: %s", buf);
            continue;
        }

        unsigned long height = strtoul(height_str, NULL, 10);
        unsigned long x = strtoul(x_str, NULL, 10);
        unsigned long y = strtoul(y_str, NULL, 10);
        unsigned long hash_value = hash(id) % tabsz;
        node *existing_node = node_lookup(htable[hash_value], id);

        if (existing_node != NULL) 
        {
            fprintf(stderr, DUPLICATE_ID_MSG, id);
            continue;
        }

        node *new_node = insert_node(id, height, x, y, htable[hash_value]);
        if (new_node == NULL) 
        {
            fprintf(stderr, INSERTION_ERROR_MSG, id);
            continue;
        }

        new_node->next = htable[hash_value];
        htable[hash_value] = new_node;
    }

    fclose(fp);
    return 0;
}
#endif
