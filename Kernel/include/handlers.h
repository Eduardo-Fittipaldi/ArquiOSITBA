#ifndef HANDLERS_H
#define HANDLERS_H

#include "types.h"

void irqDispatcher(dword irq);
void int_20();
void int_21();

#endif