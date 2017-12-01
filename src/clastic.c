#include <stdio.h>
#include <stdlib.h>
#include "clastic.h"


struct _clastic_t {
};

clastic_t *clastic_init(const char *host)
{
    //TODO
    return NULL;
}

void clastic_destroy(clastic_t *cls)
{
    //TODO
}

int clastic_index_exist(clastic_t *cls, const char *index)
{
    return 0;
    //TODO
}

int clastic_create_index(clastic_t *cls, const char *index)
{
    return 0;
    //TODO
}

int clastic_delete_index(clastic_t *cls, const char *index)
{
    return 0;
    //TODO
}

void clastic_get_by_id(clastic_t *cls, const char *index, const char *type, const char *id, char *data)
{
    //TODO
}

void clastic_get_by_query(clastic_t *cls, const char *index, const char *type, const char *query, char *data)
{
    //TODO
}

void clastic_put(clastic_t *cls, const char *index, const char *type, const char *id, char *data)
{
    //TODO
}

int clastic_count(clastic_t *cls, const char *index, const char *type)
{
    return 0;
    //TODO
}

