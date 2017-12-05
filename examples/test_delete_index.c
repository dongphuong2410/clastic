#include <stdio.h>
#include <stdlib.h>

#include "clastic.h"

int main(int argc, char **argvs)
{
    if (argc < 2) {
        printf("usage : ./%s <index_name>\n", argvs[0]);
        exit(0);
    }
    clastic_t *cls = clastic_init("localhost:9200");
    int deleted = clastic_delete_index(cls, argvs[1]);
    if (deleted) {
        printf("Successfully delete index %s\n", argvs[0]);
    }
    else {
        printf("Error happens\n");
    }
    return 0;
}
