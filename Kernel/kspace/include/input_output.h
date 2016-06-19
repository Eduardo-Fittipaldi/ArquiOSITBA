#include <types.h>

#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

byte _read_byte(word address);
word _read_word(word address);
dword _read_dword(word address);

void _write_byte(word address, byte data);
void _write_word(word address, word data);
void _write_dword(word address, dword data);

#endif //INPUT_OUTPUT_H
