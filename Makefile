CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g

chip8: src/main.c
	$(CC) $(CFLAGS) $< -o $@

run: chip8
	./chip8

clean:
	rm -f chip8

.PHONY: run clean