#ifndef way_chunk_h
#define way_chunk_h

#include "Value.h"
#include "common.h"

typedef enum 
{
    OP_CONSTANT,
    OP_CONSTANT_LONG,
    OP_RETURN,
} OpCode;

typedef struct
{
    int count;
    int capacity;
    uint8_t* code;
    int* lines;
    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
void writeConstant(Chunk* chunk, Value value, int line);
int addConstant(Chunk* chunk, Value value);

#endif
