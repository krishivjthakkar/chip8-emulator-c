#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    uint8_t memory[4096];
    uint8_t V[16];
    uint16_t I;
    uint16_t pc;
} Chip8;

void step(Chip8 *cpu) {
    assert(cpu->pc <= 4094);

    //FETCH: Read two bytes as one instruction
    uint16_t opcode = ((uint16_t)cpu->memory[cpu->pc] << 8) | cpu->memory[cpu->pc + 1];

    cpu->pc += 2;

    //DECODE: Extract parts of the instruction
    uint8_t x = (opcode >> 8) & 0x0F;
    uint8_t nn = opcode & 0xFF;

    //EXECUTE
    switch (opcode & 0xF000) {
        case 0x1000: // Jump to address NNN
            cpu->pc = opcode & 0x0FFF;
            break;
        
        case 0x6000: // Set VX = NN
            cpu->V[x] = nn;
            break;

        case 0x7000: // Add NN to VX
            cpu->V[x] += nn;
            break;

        default: 
            fprintf(stderr, "Unknown opcode: 0x%04X\n", (unsigned)opcode);
            exit(1);
    }
}

int main(void) {
    Chip8 cpu = {0};
    cpu.pc = 0x200;

    // A tiny program stored directly in memory
    cpu.memory[0x200] = 0x61;
    cpu.memory[0x201] = 0x0A; // V1 = 10

    cpu.memory[0x202] = 0x71;
    cpu.memory[0x203] = 0x05; // V1 += 5

    cpu.memory[0x204] = 0x12;
    cpu.memory[0x205] = 0x04; // Jump to 0x204

    step(&cpu);
    step(&cpu);
    step(&cpu);

    assert(cpu.V[1] == 15);
    assert(cpu.pc == 0x204);

    printf("V1 = %u\n", (unsigned)cpu.V[1]);
    printf("PC = 0x%03X\n", (unsigned)cpu.pc);
    puts("First emulator test passed!");

    return 0;

}
