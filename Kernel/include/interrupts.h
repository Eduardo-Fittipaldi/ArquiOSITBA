/*
 * interrups.h
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#ifndef INTERRUPS_H
#define INTERRUPS_H

#include "types.h"

void _cli(void);

void _sti(void);

void picMasterMask(byte mask);

void picSlaveMask(byte mask);

void lidt(IDTR *idtr);

//Termina la ejecución de la cpu.
void haltcpu(void);

void _irq00Handler(void);
void _irq01Handler(void);
void _irq02Handler(void);
void _irq03Handler(void);
void _irq04Handler(void);
void _irq05Handler(void);

void int80Handler();

#endif /* INTERRUPS_H */