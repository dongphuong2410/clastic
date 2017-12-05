AM_CFLAGS = -I../include
LDADD = ../src/libclastic.a

if DEBUG
AM_CFLAGS += -ggdb -O0
endif

noinst_PROGRAMS = test_index_exist test_create_index test_get_by_id test_delete_index
test_index_exist_SOURCES = test_index_exist.c
test_create_index_SOURCES = test_create_index.c
test_get_by_id_SOURCES = test_get_by_id.c
test_delete_index_SOURCES = test_delete_index.c
