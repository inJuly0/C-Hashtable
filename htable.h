#pragma once
#include <stddef.h>
#include <stdint.h>

#define ITEM_TYPE int 
#define MAX_LOAD_FACTOR 0.7
#define FNV_PRIME 13

#define GROW_CAP(c) (((c) <= 0) ? 8 : 2 * (c))

typedef struct {
    const char* key;
    ITEM_TYPE item;
} H__item;

typedef struct {
    size_t count;
    size_t cap; 
    H__item* items;
} Htable;

void table_init(Htable* table);
void table_free(Htable* table);
void table_add(Htable* table, const char* key, ITEM_TYPE item);
void table_get(const char* key);