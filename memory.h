#ifndef CLOX_MEMORY_H
#define CLOX_MEMORY_H

#include "common.h"

/*
 * Macros to aide in interfacing with
 * the generic reallocation function
 */

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_LINES(lines) GROW_CAPACITY(lines)

#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type*)reallocate(pointer, sizeof(type) * (oldCount), \
            sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

void *reallocate(void *pointer, size_t oldSize, size_t newSize);

#endif
