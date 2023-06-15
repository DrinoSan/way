#include <stdio.h>

#include "chunk.h"
#include "debug.h"
#include "Value.h"

//-----------------------------------------------------------------------------
void disassembleChunk(Chunk* chunk, const char* name)
{
    printf("== %s ==\n", name);

    for( int offset = 0; offset < chunk->count; )
    {
        offset = disassembleInstruction(chunk, offset);
    }
}

//-----------------------------------------------------------------------------
static int constantInstruction(const char* name, Chunk* chunk, int offset)
{
    uint8_t constant = chunk->code[offset + 1]; // Getting index of the constant in the constants pool
    printf("%-16s %4d '", name, constant); // Printing name of opcode and constant index
    printValue(chunk->constants.values[constant]);

    printf("'\n");

    return offset + 2; // We need to return +2 because the opcode and the operand
}

//-----------------------------------------------------------------------------
static int constantLongInstruction(const char* name, Chunk* chunk, int offset)
{
    uint16_t constant = (uint16_t)(chunk->code[offset + 1] << 8 | chunk->code[offset + 2]); // Getting index of the constant in the constants pool
    printf("%-16s %4d '", name, constant); // Printing name of opcode and constant index
    printValue(chunk->constants.values[constant]);

    printf("'\n");

    return offset + 3; // We need to return +3 because the opcode and the operand
}

//-----------------------------------------------------------------------------
static int simpleInstruction(const char* name, int offset)
{
    printf("%s\n", name);
    return offset + 1;
}

//-----------------------------------------------------------------------------
int disassembleInstruction(Chunk* chunk, int offset)
{
    printf("%04d ", offset);
    if( offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1])
    {
        printf("    | ");
    }
    else
    {
        // Printing line number
        printf("%4d ", chunk->lines[offset]);
    }
    

    uint8_t instruction = chunk->code[offset];
    switch (instruction)
    {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_CONSTANT_LONG:
            return constantLongInstruction("OP_CONSTANT_LONG", chunk, offset);
        case OP_NEGATE:
            return simpleInstruction("OP_NEGATE", offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}
