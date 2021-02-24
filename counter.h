#pragma once
#include "info.h"
#include "parser.h"

#define HT_ISIZE 16
typedef void   (tb_free)(void*, uintptr_t);
typedef int    (tb_cmp)(const void*, const void*);
typedef size_t(tb_hash)(const void*);

typedef struct node {
    struct node* next;
    void* key;
    uintptr_t val;
} slist;

typedef struct {
    slist* p;
    size_t i;
} iter_t;

typedef struct {
    tb_free* pfn_free; //функтор для освобождение памяти
    tb_cmp* pfn_cmp;  //компаратор x == y
    tb_hash* pfn_hash; //хеш-функция
    slist** tabs;
    size_t   cnt;
    size_t   size;
} table_t;

static slist* slist_add(slist** ls, void* key, uintptr_t val);
static void   slist_clear(slist* ls, table_t* tb);
static int    slist_remove(slist** ls, const void* key, table_t* tb);
static slist* slist_find(slist* ls, const void* key, table_t* tb);
static void _table_rebuild(table_t* tb, size_t cnt);
void   table_init(table_t* tb, tb_cmp* cmp, tb_hash* hash, tb_free* pfr);
void   table_clear(table_t* tb);
void   table_remove(table_t* tb, const void* key);
slist* table_find(table_t* tb, const void* key);
slist* table_insert(table_t* tb, void* key, uintptr_t val);
int    iter_each(iter_t* it, table_t* tb, void** key, uintptr_t* val);
void   iter_reset(iter_t* it);

static int cmp_str(const void* a, const void* b);

static size_t hash_str(const void* p);

static void free_str(void* p, uintptr_t v);

table_t dictionary(struct arr tmp);
