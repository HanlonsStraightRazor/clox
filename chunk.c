#include <stdlib.h>
#include "chunk.h"
#include "memory.h"

/*
 * Initializes a chunk of instructions.
 */
void initChunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->currentLine = 0;
    chunk->maxLines = 0;
    chunk->bytes = NULL;
    initValueArray(&chunk->constants);
}

/*
 * Writes an instruction to a chunk.
 */
void writeChunk(Chunk *chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code,
                oldCapacity, chunk->capacity);
    }
    while (chunk->maxLines < line) {
        int oldMaxLines = chunk->maxLines;
        chunk->maxLines = GROW_LINES(oldMaxLines);
        chunk->bytes = GROW_ARRAY(int, chunk->bytes,
                oldMaxLines, chunk->maxLines);
    }
    while (chunk->currentLine < line) {
        chunk->bytes[chunk->currentLine] = 0;
        chunk->currentLine++;
    }
    chunk->code[chunk->count] = byte;
    chunk->bytes[line - 1]++;
    chunk->count++;
}

/*
 * Gets the line of an instruction in a chunk
 * given its offset in number of instructions.
 */
int getLine(Chunk *chunk, int offset) {
    if (offset < 0 || offset >= chunk->count) {
        exit(1);
    }
    int bytes = 0;
    for (int i = 0; i < chunk->currentLine; i++) {
        bytes += chunk->bytes[i];
        if (offset < bytes) {
            return i + 1;
        }
    }
    return -1;
}

/*
 * Writes a constant to a chunk's value array.
 */
void writeConstant(Chunk *chunk, Value value, int line) {
    writeValueArray(&chunk->constants, value);
    int constant = chunk->constants.count - 1;
    if (constant > UINT8_MAX) {
        writeChunk(chunk, OP_CONSTANT_LONG, line);
        writeChunk(chunk, constant >> 16, line);
        writeChunk(chunk, constant >> 8, line);
        writeChunk(chunk, constant, line);
    } else {
        writeChunk(chunk, OP_CONSTANT, line);
        writeChunk(chunk, constant, line);
    }
}

/*
 * Deallocates memory given to a chunk.
 */
void freeChunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->bytes, chunk->maxLines);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}
