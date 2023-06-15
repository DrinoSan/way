#include <stdio.h>
#include <stdlib.h>

#include "Value.h"
#include "chunk.h"
#include "memory.h"

//-----------------------------------------------------------------------------
void initChunk(Chunk* chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

//-----------------------------------------------------------------------------
void freeChunk(Chunk* chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

//-----------------------------------------------------------------------------
void writeChunk(Chunk* chunk, uint8_t byte, int line)
{
    if(chunk->capacity < chunk->count + 1)
    {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    ++chunk->count;
}

//-----------------------------------------------------------------------------
void writeConstant(Chunk* chunk, Value value, int line)
{
    uint16_t constIndex = addConstant(chunk, value);

    if( constIndex >= 256 )
    {
        writeChunk(chunk, OP_CONSTANT_LONG, line);

        if(chunk->capacity < chunk->count + 2)
        {
            int oldCapacity = chunk->capacity;
            chunk->capacity = GROW_CAPACITY(oldCapacity);
            chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
            chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
        }

        // Writing uin16 into 2 fields of uin8
        chunk->code[chunk->count] = (uint8_t)(constIndex >> 8); // the >> operator obtains the higher byte of constIndex
        chunk->code[chunk->count + 1] = (uint8_t)(constIndex & 0xFF); //the bitwise AND with 0xFF extracts the lower byte

        // The line number probably needs a update
        chunk->lines[chunk->count] = line;
        chunk->lines[chunk->count + 1] = line;

        chunk->count+=2;
        return;
    }

    // First adding OP_CODE -> OP_CONSTANT which is followed by adding the indec of the value 
    writeChunk(chunk, OP_CONSTANT, line);
    writeChunk(chunk, constIndex, line);
}

//-----------------------------------------------------------------------------
int addConstant(Chunk* chunk, Value value)
{
    writeValueArray(&chunk->constants, value);
    
    return chunk->constants.count - 1; // -1 is important because inside of writeValueArray we increase the count already
}
