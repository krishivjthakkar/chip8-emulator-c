#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct {
    uint8_t memory[4096];
    uint8_t V[16];
    uint16_t I;
    uint16_t pc;
    uint8_t display[32][64];
} Chip8;

void step(Chip8 *cpu) {
    assert(cpu->pc <= 4094);

    //FETCH: Read two bytes as one instruction
    uint16_t opcode = ((uint16_t)cpu->memory[cpu->pc] << 8) | cpu->memory[cpu->pc + 1];

    cpu->pc += 2;

    //DECODE: Extract parts of the instruction
    uint8_t x = (opcode >> 8) & 0x0F;
    uint8_t nn = opcode & 0xFF;
    uint16_t nnn = opcode & 0x0FFF;

    //EXECUTE
    switch (opcode & 0xF000) {
        case 0x0000:
            if (opcode == 0x00E0) { // Clear the display
                memset(cpu->display, 0, sizeof(cpu->display));
            } else {
                fprintf(stderr, "Unsupported opcode: %04X\n", (unsigned)opcode);
                exit(1);
            }
            break;

        case 0x1000: // Jump to address NNN
            cpu->pc = opcode & 0x0FFF;
            break;
        
        case 0x6000: // Set VX = NN
            cpu->V[x] = nn;
            break;

        case 0x7000: // Add NN to VX
            cpu->V[x] += nn;
            break;

        case 0xA000: // Set I = NNN
            cpu->I = nnn;
            break;

        case 0xD000: // Draw
            fprintf(stderr, "Draw instruction not implemented yet.\n");
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
    cpu.memory[0x205] = 0x06; // Jump to 0x206

    step(&cpu);
    step(&cpu);
    step(&cpu);

    assert(cpu.V[1] == 15);
    assert(cpu.pc == 0x206);

    printf("V1 = %u\n", (unsigned)cpu.V[1]);
    printf("PC = 0x%03X\n", (unsigned)cpu.pc);
    puts("First emulator test passed!");

    // Continue tiny program to test the I register
    cpu.memory[0x206] = 0xA2;
    cpu.memory[0x207] = 0xF0; // I = 0x2F0

    step(&cpu);

    assert(cpu.I == 0x2F0);

    printf("I = 0x%03X\n", (unsigned)cpu.I);
    puts("I register test passed!");

    return 0;

}
