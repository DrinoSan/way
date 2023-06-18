#ifndef way_vm_h
#define way_vm_h

#include "chunk.h"
#include "Value.h"

#define STACK_MAX 256

typedef struct
{
    Chunk* chunk;
    uint8_t* ip;
    Value stack[STACK_MAX];
    Value* stackTop;
} VM;

typedef enum
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIM_ERROR
} InterpretResult;

void initVM();
void freeVM();

InterpretResult interpret(const char* source);

//-----------------------------------------------------------------------------
// Function:  
// @parameter: 
void push(Value value);

//-----------------------------------------------------------------------------
// Function:  
// @parameter: 
Value pop();

#endif
