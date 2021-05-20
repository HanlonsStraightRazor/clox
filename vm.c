#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "memory.h"
#include "vm.h"

VM vm;

static void resetStack() {
    vm.count = 0;
    vm.capacity = 0;
    vm.stack = NULL;
    vm.stackTop = vm.stack;
}

static void freeStack() {
    FREE_ARRAY(Value, vm.stack, vm.capacity);
}

void initVM() {
    resetStack();
}

void freeVM() {
    freeStack();
}

void push(Value value) {
    if (vm.capacity < vm.count + 1) {
        int oldCapacity = vm.capacity;
        vm.capacity = GROW_CAPACITY(oldCapacity);
        vm.stack = GROW_ARRAY(Value, vm.stack, oldCapacity, vm.capacity);
        vm.stackTop = vm.stack + vm.count;
    }
    *vm.stackTop = value;
    vm.stackTop++;
    vm.count++;
}

void setTop(Value value) {
    *(vm.stackTop - 1) = value;
}

Value peek() {
    return *(vm.stackTop - 1);
}

Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsequence-point"

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define READ_CONSTANT_LONG() \
    (vm.chunk->constants.values[(READ_BYTE() << 16) | (READ_BYTE() << 8)  | READ_BYTE()])
#define BINARY_OP(op) \
    do { \
        double b = pop(); \
        setTop(peek() op b); \
    } while (false)

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("          ");
        for (Value *slot = vm.stack; slot < vm.stackTop; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        disassembleInstruction(vm.chunk,
                (int) (vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                push(READ_CONSTANT());
                break;
            }
            case OP_CONSTANT_LONG: {
                push(READ_CONSTANT_LONG());
                break;
            }
            case OP_ADD:        BINARY_OP(+); break;
            case OP_SUBTRACT:   BINARY_OP(-); break;
            case OP_MULTIPLY:   BINARY_OP(*); break;
            case OP_DIVIDE:     BINARY_OP(/); break;
            case OP_NEGATE:     setTop(-peek()); break;
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
#undef READ_CONSTANT_LONG
#undef BINARY_OP
}

#pragma GCC diagnostic pop

InterpretResult interpret(Chunk *chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}
