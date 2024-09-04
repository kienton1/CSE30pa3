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
    int s_flag = 0;
    unsigned long tabsz = DEFAULT_TAB_SZ;
    char *filename = NULL;
    int opt;

    while ((opt = getopt(argc, argv, "st:")) != -1) {
        switch (opt) {
            case 's':
                s_flag = 1;
                break;
            case 't':
                tabsz = strtoul(optarg, NULL, 10);
                if (tabsz < MIN_TAB_SZ) {
                    tabsz = DEFAULT_TAB_SZ;
                }
                break;
            default:
                fprintf(stderr, "Usage: %s [-s] [-t tablesize] filename\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Expected filename after options\n");
        return 1;
    }

    filename = argv[optind];

    node **htable = calloc(tabsz, sizeof(node *));
    if (htable == NULL) {
        fprintf(stderr, "calloc failed: unable to allocate memory for htable\n");
        return 1;
    }

    if (load_table(htable, tabsz, filename) != 0) {
        fprintf(stderr, "error in load_table\n");
        free(htable);
        return 1;
    }

    size_t bufsz = 0;
    char *buf = NULL; 
    int successful_query = 0;
    ssize_t bytes;

    while ((bytes = getline(&buf, &bufsz, stdin)) > 0) {
        if (bytes > 0 && buf[bytes - 1] == '\n') {
            buf[bytes - 1] = '\0';
        }
        unsigned long index = hash(buf) % tabsz;
        node *result = node_lookup(htable[index], buf);
        if (result) {
            printf(QUERY_SUCCESS_FORMAT, result->id, result->height, result->xcoord, result->ycoord);
            successful_query++;
        } else {
            printf(QUERY_FAILURE_FORMAT, buf);
        }
    }

    printf("%d successful queries\n", successful_query);

    if (s_flag) {
        print_info(htable, tabsz);
    }

    delete_table(htable, tabsz);
    free(buf);
    free(htable);

    return 0;
}
#endif
