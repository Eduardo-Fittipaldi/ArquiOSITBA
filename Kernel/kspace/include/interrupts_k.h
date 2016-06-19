/*
 * Basado en el template creado por @anizzomc.
 */

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "types.h"

void _cli(void);

void _sti(void);

void picMasterMask(byte mask);
void picSlaveMask(byte mask);

//Termina la ejecución de la cpu.
void haltcpu(void);

void _irq00Handler(void);
void _irq01Handler(void);
void _int80Handler(void);

void setup_idt();

void setup_interrupts();

void setup_IDT_entry (int index, byte selector, qword offset, byte access);

#endif /* INTERRUPS_H */