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
    char *index_name = argvs[1];
    int error = clastic_create_index(cls, index_name);
    return 0;
}

