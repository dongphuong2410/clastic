#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <string.h>
#include <json-c/json.h>

#include "clastic.h"

#define STR_BUFF 2048

struct _clastic_t {
    CURL *curl;
    char url[STR_BUFF];
};

typedef struct {
    char *ptr;
    size_t len;
} string;

size_t _index_exist_cb(void *ptr, size_t size, size_t nmemb, void *data);
size_t _writedata(void *ptr, size_t size, size_t nmemb, void *data);
void _init_string(string *s);
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
    int exist = 0;
    snprintf(query, STR_BUFF, "%s/%s", cls->url, index);
    curl_easy_reset(cls->curl);
    curl_easy_setopt(cls->curl, CURLOPT_URL, query);
    curl_easy_setopt(cls->curl, CURLOPT_HEADER, 1);
    curl_easy_setopt(cls->curl, CURLOPT_WRITEFUNCTION, _index_exist_cb);
    curl_easy_setopt(cls->curl, CURLOPT_WRITEDATA, &exist);
    CURLcode res = curl_easy_perform(cls->curl);
    return exist;
}

int clastic_create_index(clastic_t *cls, const char *index)
{
    //TODO: this function has not work, keep hanging
    //char query[STR_BUFF];
    //int data;
    //snprintf(query, STR_BUFF, "%s/%s", cls->url, index);
    //curl_easy_reset(cls->curl);
    //curl_easy_setopt(cls->curl, CURLOPT_URL, query);
    //curl_easy_setopt(cls->curl, CURLOPT_POST, 1);
    //curl_easy_setopt(cls->curl, CURLOPT_WRITEFUNCTION, _create_index_cb);
    //curl_easy_setopt(cls->curl, CURLOPT_WRITEDATA, &data);
    //curl_easy_setopt(cls->curl, CURLOPT_CONNECTTIMEOUT, 1);
    //CURLcode res = curl_easy_perform(cls->curl);
    return 0;
}

int clastic_delete_index(clastic_t *cls, const char *index)
{
    int success = 0;
    string s;
    _init_string(&s);
    char query[STR_BUFF];
    int data;
    snprintf(query, STR_BUFF, "%s/%s", cls->url, index);
    curl_easy_reset(cls->curl);
    curl_easy_setopt(cls->curl, CURLOPT_URL, query);
    curl_easy_setopt(cls->curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_setopt(cls->curl, CURLOPT_WRITEFUNCTION, _writedata);
    curl_easy_setopt(cls->curl, CURLOPT_WRITEDATA, &s);
    CURLcode res = curl_easy_perform(cls->curl);

    json_object *root = json_tokener_parse(s.ptr);
    printf(s.ptr);
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
    _free_string(&s);
    return success;
}

int clastic_get_by_id(clastic_t *cls, const char *index, const char *type, const char *id, char *data)
{
    string s;
    _init_string(&s);
    char query[STR_BUFF];
    snprintf(query, STR_BUFF, "%s/%s/%s/%s", cls->url, index, type, id);
    curl_easy_reset(cls->curl);
    curl_easy_setopt(cls->curl, CURLOPT_URL, query);
    curl_easy_setopt(cls->curl, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(cls->curl, CURLOPT_WRITEFUNCTION, _writedata);
    curl_easy_setopt(cls->curl, CURLOPT_WRITEDATA, &s);
    curl_easy_perform(cls->curl);

    json_object *root = json_tokener_parse(s.ptr);
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
    _free_string(&s);
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

size_t _index_exist_cb(void *ptr, size_t size, size_t nmemb, void *data)
{
    size_t realsize = size * nmemb;
    int *exist = (int *)data;
    if (strstr(ptr, "HTTP/1.1 200 OK")) {
        *exist = 1;
    }
    return size * nmemb;
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

void _init_string(string *s)
{
    s->len = 0;
    s->ptr = malloc(s->len + 1);
    s->ptr[0] = '\0';
}

void _free_string(string *s)
{
    if (s->ptr) free(s->ptr);
}
