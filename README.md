
# CHIP-8 Emulator in C

A CHIP-8 emulator written in C to explore systems programming,
computer architecture, instruction decoding, and memory management.

This project is being built iteratively, starting with the CPU
and instruction set before adding graphics and keyboard support.

## Current Progress

Implemented:
- 4 KB emulated memory
- 16 general-purpose 8-bit registers (V0–VF)
- 16-bit index register and program counter
- Instruction fetch-decode-execute cycle
- Basic opcode decoding using bitwise operations
- Display framebuffer (64x32 pixels)
- Screen-clearing instruction (00E0)
- Jump (1NNN), register load (6XNN), addition (7XNN),
  and index register (ANNN)
- Basic instruction tests using C assertions

## Planned Features

- [ ] Sprite drawing and collision detection (DXYN)
- [ ] Remaining CHIP-8 instructions
- [ ] ROM loading from files
- [ ] Graphics using raylib
- [ ] Keyboard input
- [ ] Delay and sound timers
- [ ] Compatibility testing with existing CHIP-8 ROMs

## Building

Requires a C11-compatible compiler and Make.

```bash
make
make run
```

The current program runs a small test sequence and verifies
the results using assertions.

## Project Status

Work in progress. The emulator currently executes a subset of
CHIP-8 instructions but cannot run complete ROMs yet.

## References

- https://tobiasvl.github.io/blog/write-a-chip-8-emulator/
- https://chip-8.github.io/links/
