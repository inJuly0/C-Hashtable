#include "htable.h"


static size_t table__hash(const char* string){
    size_t hash = 1;
    for (int i = 0; string[i]; i++) {
        hash = hash * FNV_PRIME;
        hash = hash ^ string[i];
    }
    return hash;
}

static void table__grow(Htable* table) {
    if (table->count + 1 <= MAX_LOAD_FACTOR * table->cap) return;

    size_t old_cap = table->cap;
    table->cap = GROW_CAP(table->cap);

    size_t new_size = sizeof(H__item) * table->cap;
    table->items = (H__item*)realloc(table->items, new_size);

    for(size_t i = old_cap; i < table->cap; i++){
        table->items[i].key = NULL;
    }
}

void table_init(Htable* table) {
    table->count = 0;
    table->cap = 0;
    table->items = NULL;
}


void table_set(Htable* table, const char* key, ITEM_TYPE value) {
    table__grow(table);
    size_t hash = table__hash(key);
    size_t index = hash % table->cap;
    H__item entry = {key, value};
    
    if (table->items[index].key == NULL){
        // key not present, insert item.
        table->items[index] = entry;
        return;
    }


    H__item* curr_item = &table->items[index];
    H__item* prev_item = NULL;

    while (curr_item != NULL) {
        // if item already exists, then overwrite the value
        if (strcmp(key, curr_item->key) == 0) {
            table->items[index].value = value;
            return;
        }
        prev_item = curr_item;
        curr_item = curr_item->next;
    }

    // if value still not set, add a new item entry

    prev_item->next = (H__item*)malloc(sizeof(H__item));
    prev_item->next->key = key;
    prev_item->next->value = value;
}

ITEM_TYPE table_get(Htable* table, const char* key) {
    size_t index = table__hash(key) % table->cap;
    
    // if the slot only contains a single element,
    // return the head. 
    if (table->items[index].next == NULL)  
        return table->items[index].value;

    H__item* curr_item = &table->items[index];
    H__item* prev_item = NULL;

    while (curr_item != NULL) {
        if (strcmp(key, curr_item->key) == 0) {
            return curr_item->value;
        }

        prev_item = curr_item;
        curr_item = curr_item->next;
    }

    return 0;
}