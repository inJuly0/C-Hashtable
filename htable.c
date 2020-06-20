#include "htable.h"


static size_t table__hash(const char* key){

    return 0;
}

static void table__grow(Htable* table){
    if (table->count + 1 <= MAX_LOAD_FACTOR * table->cap) return;

    size_t old_cap = table->cap;
    table->cap = GROW_CAP(table->cap);
    
    size_t old_size = sizeof(ITEM_TYPE) * old_cap;
    size_t new_size = sizeof(ITEM_TYPE) * table->cap;
    table->items = (H__item*)realloc(table->items, old_size, new_size);

}

void table_init(Htable* table){
    table->count = 0;
    table->cap = 0;
    table->items = NULL;
}

void table_add(Htable* table, const char* key, ITEM_TYPE item){
    table__grow(table);
    size_t hash = table__hash(key);
    size_t index = hash % table->cap;
}