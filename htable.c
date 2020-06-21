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


// return a pointer to the item struct that the key is mapped to
static H__item* table__find(Htable* table, const char* key) {
    size_t index = table__hash(key) % table->cap;
    H__item* curr_item = &table->items[index];
    H__item* prev_item = NULL;

    while (curr_item != NULL) {
        if (strcmp(key, curr_item->key) == 0) {
            return curr_item;
        }

        prev_item = curr_item;
        curr_item = curr_item->next;
    }

    return NULL;
}

void table_set(Htable* table, const char* key, ITEM_TYPE value) {
    table__grow(table);
    size_t hash = table__hash(key);
    size_t index = hash % table->cap;
    H__item entry = {key, value, NULL};
    
    if (table->items[index].key == NULL){
        // key not present, insert item.
        table->items[index] = entry;
        table->count++;
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
    table->count++;
}


bool table_has(Htable* table, const char* key) {
    return table__find(table, key)->key != NULL;
}

bool table_remove(Htable* table, const char* key) {
    H__item* item = table__find(table, key);
    if (item != NULL) {
        item->key = NULL; 
        item->value = 0;
        return true;
    }
    return false;
}

ITEM_TYPE table_get(Htable* table, const char* key) {
    H__item* item = table__find(table, key);
    if (item == NULL) return 0;
    return item->value;
}

void table_free(Htable* table){

    for(size_t i = 0; i < table->cap; i++) {
        if (table->items[i].key != NULL) {
            H__item* prev = NULL;
            H__item* curr = &table->items[i];
            while (curr != NULL) {
                prev = curr;
                curr = curr->next;
                free(prev);
            }
        }
    }

    table_init(table);
    free(table->items);
    free(table);
}