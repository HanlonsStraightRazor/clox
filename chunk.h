#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include "common.h"
#include "value.h"

/*
 * Valid opcode definitions
 */
typedef enum {
    OP_CONSTANT,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_CONSTANT_LONG,
    OP_RETURN,
} OpCode;

/*
 * Group of instructions
 */
typedef struct {
    int count;
    int capacity;
    uint8_t *code;
    int currentLine;
    int maxLines;
    int *bytes;
    ValueArray constants;
} Chunk;

void initChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
int getLine(Chunk *chunk, int offset);
void writeConstant(Chunk *chunk, Value value, int line);
void freeChunk(Chunk *chunk);

#endif
