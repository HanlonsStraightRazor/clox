#include "common.h"
#include "chunk.h"
#include "debug.h"

/*
 * For now, just creates a test chunk.
 */
int main(int argc, const char *argv[]) {
    Chunk chunk;
    initChunk(&chunk);
    for (int i = 1; i <= 300; i++) {
        writeConstant(&chunk, (double) i, i);
    }
    writeChunk(&chunk, OP_RETURN, 301);
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);
    return 0;
}
