#include <stdio.h>
#include "memory.h"
#include "value.h"

/*
 * Initializes a value array for storing constants.
 */
void initValueArray(ValueArray *array) {
    array->values = NULL;
    array->capacity = 0;
    array->count = 0;
}

/*
 * Writes a value to the value array.
 */
void writeValueArray(ValueArray *array, Value value) {
    if (array->capacity < array->count + 1) {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value, array->values,
                oldCapacity, array->capacity);
    }
    array->values[array->count] = value;
    array->count++;
}

/*
 * Frees the memory taken up by a value array.
 */
void freeValueArray(ValueArray *array) {
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}

void printValue(Value value) {
    printf("%g", value);
}
