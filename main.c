#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]) 
{
    initVM();

    Chunk chunk;
    initChunk(&chunk);

    /* writeConstant(&chunk, 1.2, 125); */
    //int constant2 = addConstant(&chunk, 11.2); // We write the value 1.2 manually in the chunks constant pool. The return value is the index of the added value
    //writeChunk(&chunk, OP_CONSTANT, 125); // The first byte is the operand
    //writeChunk(&chunk, constant2, 125); // Second byte is the index of the constant

    // Arithmetic test
    // 1.2 + 3.4
    writeConstant(&chunk, 1.2, 123);
    writeConstant(&chunk, 3.4, 123);
    writeChunk(&chunk, OP_ADD, 123);


    // 4.6 (Result from above) / 5.6
    writeConstant(&chunk, 5.6, 123);
    writeChunk(&chunk, OP_DIVIDE, 123);


    // Arithmetic test end

    writeChunk(&chunk, OP_NEGATE,  123);
                                     
    writeChunk(&chunk, OP_RETURN, 123);

    // DisassembleChunk transforms machine code into textual listings of the instructions
    /* disassembleChunk(&chunk, "test chunk"); */
    interpret(&chunk);

    freeVM();
    freeChunk(&chunk);
    return 0;
}
