#ifndef INTERRUPS_C_H
#define INTERRUPS_C_H

#include "types.h"

void setup_idt();

void setup_interrupts();

void setup_IDT_entry (int index, byte selector, qword offset, byte access);

#endif /* INTERRUPS_C_H */