# C-Hashtable
A hashtable implementation in C.

# Usage

Using hash-table is as simple as you would expect :

```c
#include "htable.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
    Htable table;
    table_init(&table);
    table_set(&table, "myKey", 10);
    
    printf("myKey maps to %d", table_get(&table, "myKey"));

    // don't forget to free the table after use !
    table_free(&table);
    return 0;
}
```

# Spec

This hash-table implementation uses the [FNV-1 hash function](https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1_hash).

By default it maps strings (char *) to integers (int), but you can easily change that to suit your purpose by simply changing this one line: 

```c
// in htable.h, line 13:

#define ITEM_TYPE int
```

changing that macro definition to `char*` for example, lets you map strings to strings :

```c
Htable table;
table_init(&table);
table_set(&table, "a", "hello");
printf("%s\n", table_get(&table, "a")); // "hello"
```