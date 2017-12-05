#include <stdio.h>
#include <stdlib.h>

#include "clastic.h"

int main(int argc, char **argvs)
{
    if (argc < 4) {
        printf("usage : ./%s <index_name> <type_name> <id>\n", argvs[0]);
        exit(0);
    }
    clastic_t *cls = clastic_init("localhost:9200");
    char result[CLASTIC_DATA_BUFFER];
    int status = clastic_get_by_id(cls, argvs[1], argvs[2], argvs[3], result);
    if (status) {
        printf("Get data from es failed\n");
        exit(-1);
    }
    printf("Data received : %s\n", result);
    return 0;
}
