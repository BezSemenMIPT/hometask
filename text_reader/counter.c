#include "counter.h"


static int cmp_str(const void* a, const void* b) { return strcmp((const char*)a, (const char*)b) == 0; }

static size_t hash_str(const void* p) { //���-������� ��� �����
    const char* s = (const char*)p;
    size_t k = 0;
    for (; *s; ++s)
        k += k ^ (size_t)*s;
    return k;
}

//��� �������
table_t dictionary(struct arr tmp) {
    table_t  tb;
    slist* p;
    table_init(&tb, &cmp_str, &hash_str, NULL);
    for(int i=0;i<tmp.argc;i++){
        p=table_insert(&tb, tmp.argv[i], 0);
	if(p!=NULL) ++p->val;
	//free(tmp.argv[i]);
    }
    return tb;
}

static void free_str(void* p, uintptr_t v) {
    if (p != NULL)
        free(p);
}

//�������������
void table_init(table_t* tb, tb_cmp* cmp, tb_hash* hash, tb_free* pfr) {
    tb->pfn_cmp = cmp;
    tb->pfn_hash = hash;
    tb->pfn_free = pfr;
    tb->tabs = NULL;
    tb->cnt = tb->size = 0;
}

//�������
slist* table_insert(table_t* tb, void* key, uintptr_t val) {
    size_t n, i;
    slist* p, ** t;
    if (tb->tabs != NULL) {
        if ((p = slist_find(tb->tabs[(*tb->pfn_hash)(key) % tb->size], key, tb)) != NULL)
            return p;
    }

    if (tb->tabs == NULL) {
        n = HT_ISIZE;
        tb->tabs = (slist**)malloc(n * sizeof(slist*));
        if (tb->tabs == NULL)
            return NULL;

        tb->size = n;
        for (i = 0; i < tb->size; ++i)
            tb->tabs[i] = NULL;

    }
    else if ((tb->cnt >> 2) > tb->size) {
        n = tb->cnt << 1;
        t = (slist**)realloc(tb->tabs, n * sizeof(slist*));
        if (t == NULL)
            return NULL;
        tb->tabs = t;

        i = tb->size;
        tb->size = n;
        _table_rebuild(tb, i);
    }

    p = slist_add(&tb->tabs[(*tb->pfn_hash)(key) % tb->size], key, val);
    if (p != NULL)
        ++tb->cnt;
    return p;
}

//�������� ���� �������
void table_clear(table_t* tb) {
    size_t i;
    if (tb->tabs != NULL) {
        for (i = 0; i < tb->size; ++i)
            slist_clear(tb->tabs[i], tb);
        free(tb->tabs);
        tb->tabs = NULL;
        tb->cnt = tb->size = 0;
    }
}

//�������� �� �����
void table_remove(table_t* tb, const void* key) {
    if (tb->tabs != NULL) {
        if (slist_remove(&tb->tabs[(*tb->pfn_hash)(key) % tb->size], key, tb))
            --tb->cnt;
    }
}

//����� �������� �� �����
slist* table_find(table_t* tb, const void* key) {
    if (tb->tabs != NULL)
        return slist_find(tb->tabs[(*tb->pfn_hash)(key) % tb->size], key, tb);
    return NULL;
}

//����������� �������
static void _table_rebuild(table_t* tb, size_t cnt) {
    slist* x, * y, * p;
    size_t i, k;
    for (i = cnt; i < tb->size; ++i)
        tb->tabs[i] = NULL;

    for (i = 0; i < cnt; ++i) {
        for (x = y = tb->tabs[i]; y != NULL; ) {

            k = (*tb->pfn_hash)(y->key) % tb->size;
            if (k != i) {
                p = y;
                if (y == tb->tabs[i])
                    y = tb->tabs[i] = tb->tabs[i]->next;
                else
                    y = x->next = y->next;

                p->next = tb->tabs[k];
                tb->tabs[k] = p;
            }
            else {
                x = y;
                y = y->next;
            }
        }
    }
}

//������� � ������
static slist* slist_add(slist** ls, void* key, uintptr_t val) {
    slist* p = (slist*)malloc(sizeof(slist));
    if (p != NULL) {
        p->key = key;
        p->val = val;
        p->next = *ls;
        *ls = p;
    }
    return p;
}

//�������� ���� ����� ������
static void slist_clear(slist* ls, table_t* tb) {
    slist* t;
    while (ls != NULL) {
        t = ls;
        ls = ls->next;
        if (tb->pfn_free != NULL)
            (*tb->pfn_free)(t->key, t->val);
        free(t);
    }
}

//�������� ���� �� �����
static int slist_remove(slist** ls, const void* key, table_t* tb) {
    slist* p = *ls;
    while (p != NULL) {
        if ((*tb->pfn_cmp)(key, p->key)) {
            *ls = p->next;
            if (tb->pfn_free != NULL)
                (*tb->pfn_free)(p->key, p->val);
            free(p);
            return 1;
        }
        ls = &p->next;
        p = p->next;
    }
    return 0;
}

//�������� �����
static slist* slist_find(slist* p, const void* key, table_t* tb) {
    for (; p != NULL; p = p->next) {
        if ((*tb->pfn_cmp)(key, p->key))
            break;
    }
    return p;
}

void iter_reset(iter_t* it) {
    it->i = 0;
    it->p = NULL;
}

int iter_each(iter_t* it, table_t* tb, void** key, uintptr_t* val) {
    if (it->p != NULL) {
        if ((it->p = it->p->next) != NULL) {
            *key = it->p->key;
            *val = it->p->val;
            return 1;
        }
        ++it->i;
    }

    for (; it->i < tb->size; ++it->i) {
        if (tb->tabs[it->i] != NULL) {
            *key = tb->tabs[it->i]->key;
            *val = tb->tabs[it->i]->val;
            it->p = tb->tabs[it->i];
            return 1;
        }
    }
    return 0;
}
