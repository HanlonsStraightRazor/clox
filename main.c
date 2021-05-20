#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

/*
 * For now, just creates a test chunk.
 */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, const char *argv[]) {
    initVM();

    Chunk chunk;
    initChunk(&chunk);

    writeConstant(&chunk, 1.2, 123);
    writeConstant(&chunk, 3.4, 123);
    writeChunk(&chunk, OP_ADD, 123);
    writeConstant(&chunk, 5.6, 123);
    writeChunk(&chunk, OP_DIVIDE, 123);
    writeChunk(&chunk, OP_NEGATE, 123);
    writeChunk(&chunk, OP_RETURN, 123);

    interpret(&chunk);

    freeVM();
    freeChunk(&chunk);
    return 0;
}

#pragma GCC diagnostic pop
