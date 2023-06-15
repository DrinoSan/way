#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]) 
{
    initVM();

    Chunk chunk;
    initChunk(&chunk);


    writeConstant(&chunk, 200, 124); // Second byte is the index of the constant

    writeConstant(&chunk, 11.2, 125);
    //int constant2 = addConstant(&chunk, 11.2); // We write the value 1.2 manually in the chunks constant pool. The return value is the index of the added value
    //writeChunk(&chunk, OP_CONSTANT, 125); // The first byte is the operand
    //writeChunk(&chunk, constant2, 125); // Second byte is the index of the constant

    writeChunk(&chunk, OP_NEGATE,  125);
                                     
    writeChunk(&chunk, OP_RETURN, 125);

    // DisassembleChunk transforms machine code into textual listings of the instructions
    /* disassembleChunk(&chunk, "test chunk"); */
    interpret(&chunk);

    freeVM();
    freeChunk(&chunk);
    return 0;
}
