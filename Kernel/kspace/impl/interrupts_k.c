#include "types.h"
#include "Kernel/kspace/include/interrupts_k.h"
#include "defs.h"

DESCR_INT * idt;

void setup_idt() {

    setup_interrupts();
    picMasterMask(0xFC);
    picSlaveMask(0xFF);

    _sti();
}

void setup_interrupts() {
    setup_IDT_entry (0x20, 0x08, (qword)&_irq00Handler, ACS_INT);
    setup_IDT_entry (0x21, 0x08, (qword)&_irq01Handler, ACS_INT);
    setup_IDT_entry (0x80, 0x08, (qword)&_int80Handler, ACS_INT);
}


// Source: KernelIDT TP5 y TODO: Pagina IDT osdev. Falta hacer & a los bits
void setup_IDT_entry (int index, byte selector, qword offset, byte access) {
    idt[index].selector = selector;
    idt[index].access = access;
    idt[index].offset_l = offset & 0xFFFF;
    idt[index].offset_m = (offset >> 16) & 0xFFFF;
    idt[index].offset_h = (offset >> 32) & 0xFFFF;
    idt[index].zero_1 = 0;
    idt[index].zero_2 = 0;
}
