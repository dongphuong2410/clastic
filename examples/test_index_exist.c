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
    int exist = clastic_index_exist(cls, index_name);
    if (exist) {
        printf("index '%s' exists\n", index_name);
    }
    else {
        printf("index '%s' does not exist\n", index_name);
    }
    return 0;
}
