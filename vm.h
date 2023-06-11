#ifndef way_vm_h
#define way_vm_h

#include "chunk.h"

typedef struct
{
    Chunk* chunk;
    uint8_t* ip;
} VM;

typedef enum
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIM_ERROR
} InterpretResult;

void initVM();
void freeVM();

InterpretResult interpret(Chunk* chunk);

#endif
