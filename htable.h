#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// the ITEM_TYPE macro defines the type of 
// data this hashtable can contain as values. 
// By default, it's int. Can be changed to anything
// to suit the user's purposes.

#define ITEM_TYPE int 

#define MAX_LOAD_FACTOR 0.7
#define FNV_PRIME 16777619
#define GROW_CAP(c) (((c) <= 0) ? 8 : 2 * (c))

typedef struct H__item {
    const char* key;
    ITEM_TYPE value;
    struct H__item* next;
} H__item;

typedef struct {
    size_t count;
    size_t cap; 
    H__item* items;
} Htable;

void table_init(Htable* table);
void table_free(Htable* table);
void table_set(Htable* table, const char* key, ITEM_TYPE value);
bool table_has(Htable* table, const char* key);
ITEM_TYPE table_get(Htable* table, const char* key);