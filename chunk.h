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

//-----------------------------------------------------------------------------
// Initializes Empty chunk
void initChunk(Chunk* chunk);

//-----------------------------------------------------------------------------
// Frees used memory of chunk, lines and valueArray
void freeChunk(Chunk* chunk);

//-----------------------------------------------------------------------------
// Function to write OP_CODE/Value (Byte) to Chunk
void writeChunk(Chunk* chunk, uint8_t byte, int line);

//-----------------------------------------------------------------------------
// Function to handle index larger than 255
// Uses OP_CONSTANT for indexes lower than 256
// Uses OP_CONST_LONG for indexes larger than 255
void writeConstant(Chunk* chunk, Value value, int line);

//-----------------------------------------------------------------------------
// Function to add Value to chunk->constants pool
int addConstant(Chunk* chunk, Value value);

#endif
