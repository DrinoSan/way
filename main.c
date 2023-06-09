#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) 
{
    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2); // We write the value 1.2 manually in the chunks constant pool. The return value is the index of the added value
    writeChunk(&chunk, OP_CONSTANT, 123); // The first byte is the operand
    writeChunk(&chunk, constant, 123); // Second byte is the index of the constant

    int constantLong = addConstant(&chunk, 33.2); // We write the value 1.2 manually in the chunks constant pool. The return value is the index of the added value
    writeChunk(&chunk, OP_CONSTANT_LONG, 124); // The first byte is the operand
    writeConstant(&chunk, constantLong, 124); // Second byte is the index of the constant

    int constant2 = addConstant(&chunk, 11.2); // We write the value 1.2 manually in the chunks constant pool. The return value is the index of the added value
    writeChunk(&chunk, OP_CONSTANT, 125); // The first byte is the operand
    writeChunk(&chunk, constant2, 125); // Second byte is the index of the constant
                                       //
    writeChunk(&chunk, OP_RETURN, 125);

    // DisassembleChunk transforms machine code into textual listings of the instructions
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);
    return 0;
}
