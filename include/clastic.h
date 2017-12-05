#ifndef __CLASTIC_H__
#define __CLASTIC_H__

#define CLASTIC_DATA_BUFFER 2048

typedef struct _clastic_t clastic_t;

/**
  * @brief Init and return handler to clastic
  * @param host Elasticsearch server path
  * @return pointer to clastic_t
  */
clastic_t *clastic_init(const char *host);

/**
  * @brief Destroy
  */
void clastic_destroy(clastic_t *cls);

/**
  * @brief Check if index exist
  * @param cls Pointer to clastic_t
  * @param index Index string
  * @return 1 if index exists, or else return 0
  */
int clastic_index_exist(clastic_t *cls, const char *index);

/**
  * @brief Create new index
  * @param cls Pointer to clastic_t
  * @param index Index to be created
  * @return 0 if success
  */
int clastic_create_index(clastic_t *cls, const char *index);

/**
  * @brief Delete an index
  * @param cls Pointer to clastic_t
  * @param index Index to be deleted
  * @return 0 if success
  */
int clastic_delete_index(clastic_t *cls, const char *index);

/**
  * @brief Get and index from id
  * @param[in] index Index
  * @param[in] type Type
  * @param[in] id id
  * @param[out] data Found data, if no data found, data will be set to empty string
  * @return 0 if function ok, return -1 on error
  */
int clastic_get_by_id(clastic_t *cls, const char *index, const char *type, const char *id, char *data);

/**
  * @brief Get and index from query
  * @param[in] index Index
  * @param[in] type Type
  * @param[in] id id
  * @param[out] data Found data (can be multiple record)
  */
void clastic_get_by_query(clastic_t *cls, const char *index, const char *type, const char *query, char *data);

/**
  * @brief Insert data into an index
  * @param[in] index Index
  * @param[in] type Type
  * @param[in] id id
  * @param[in] data Found data
  * @return 0 if success,  -1 if error
  */
int clastic_put(clastic_t *cls, const char *index, const char *type, const char *id, char *data);

/**
  * @brief Count number of documents
  * @param[in] index Index
  * @param[in] type Type
  * @return Number of documents
  */
int clastic_count(clastic_t *cls, const char *index, const char *type);

#endif


