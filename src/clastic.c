#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <string.h>
#include <json-c/json.h>

#include "clastic.h"

#define STR_BUFF 2048

typedef enum {
    CLASTIC_METHOD_GET,
    CLASTIC_METHOD_POST,
    CLASTIC_METHOD_DELETE,
    CLASTIC_METHOD_HEAD
} method_t;

struct _clastic_t {
    CURL *curl;
    char url[STR_BUFF];
};

typedef struct {
    char *ptr;
    size_t len;
} string;

size_t _writedata(void *ptr, size_t size, size_t nmemb, void *data);
string *http_send(CURL *curl, const char *query,  method_t method);

string *_init_string(void);
void _free_string(string *s);

clastic_t *clastic_init(const char *url)
{
    clastic_t *cls = (clastic_t *)calloc(1, sizeof(clastic_t));
    cls->curl = curl_easy_init();
    snprintf(cls->url, STR_BUFF, "http://%s", url);
    return cls;
}

void clastic_destroy(clastic_t *cls)
{
    curl_easy_cleanup(cls->curl);
    free(cls);
}

int clastic_index_exist(clastic_t *cls, const char *index)
{
    char query[STR_BUFF];
    snprintf(query, STR_BUFF, "%s/%s", cls->url, index);
    string *result = http_send(cls->curl, query, CLASTIC_METHOD_HEAD);
    int exist = 0;
    if (strstr(result->ptr, "HTTP/1.1 200 OK")) {
        exist = 1;
    }
    _free_string(result);
    return exist;
}

int clastic_create_index(clastic_t *cls, const char *index)
{
    //TODO : create index make function hang
    return 0;
}

int clastic_delete_index(clastic_t *cls, const char *index)
{
    int success = 0;
    char query[STR_BUFF];
    snprintf(query, STR_BUFF, "%s/%s", cls->url, index);

    string *result = http_send(cls->curl, query, CLASTIC_METHOD_DELETE);
    json_object *root = json_tokener_parse(result->ptr);
    if (root) {
        json_object *ack = NULL;
        if (json_object_object_get_ex(root, "acknowledged", &ack)) {
            if (ack) {
                json_bool value = json_object_get_boolean(ack);
                if (value) success = 1;
            }
        }
        json_object_put(root);
    }
    _free_string(result);
    return success;
}

int clastic_get_by_id(clastic_t *cls, const char *index, const char *type, const char *id, char *data)
{
    char query[STR_BUFF];
    snprintf(query, STR_BUFF, "%s/%s/%s/%s", cls->url, index, type, id);
    string *result = http_send(cls->curl, query, CLASTIC_METHOD_GET);
    json_object *root = json_tokener_parse(result->ptr);
    if (root) {
        json_object *source = NULL;
        if (json_object_object_get_ex(root, "_source", &source)) {
            if (source) {
                const char *value = json_object_get_string(source);
                snprintf(data, CLASTIC_DATA_BUFFER, "%s", value);
            }
        }
        json_object_put(root);
    }
    _free_string(result);
    return 0;
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

size_t _writedata(void *ptr, size_t size, size_t nmemb, void *data)
{
    string *s = (string *)data;
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        return 0;
    }
    memcpy(s->ptr + s->len, ptr, size*nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;
    return size*nmemb;
}

string *_init_string()
{
    string *s = (string *)malloc(sizeof(string));
    s->len = 0;
    s->ptr = malloc(s->len + 1);
    s->ptr[0] = '\0';
    return s;
}

void _free_string(string *s)
{
    if (s->ptr) free(s->ptr);
    free(s);
}

string *http_send(CURL *curl, const char *query,  method_t method)
{
    string *s = _init_string();
    curl_easy_reset(curl);
    curl_easy_setopt(curl, CURLOPT_URL, query);
    switch (method) {
        case CLASTIC_METHOD_DELETE:
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
            break;
        case CLASTIC_METHOD_GET:
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
            break;
        case CLASTIC_METHOD_POST:
            curl_easy_setopt(curl, CURLOPT_POST, 1);
            break;
        case CLASTIC_METHOD_HEAD:
            curl_easy_setopt(curl, CURLOPT_HEADER, 1);
            break;
    }
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _writedata);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, s);
    curl_easy_perform(curl);
    return s;
}
