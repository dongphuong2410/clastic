#include <stdio.h>
#include <stdlib.h>

#include "clastic.h"

int main(int argc, char **argvs)
{
    if (argc < 5) {
        printf("usage : ./%s <index_name> <type_name> <id> <data>\n", argvs[0]);
        exit(0);
    }
    clastic_t *cls = clastic_init("localhost:9200");
    int status = clastic_put(cls, argvs[1], argvs[2], argvs[3], argvs[4]);
    return 0;
}
