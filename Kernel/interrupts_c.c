#include "interrupts_c.h"
#include "types.h"
#include "interrupts.h"
#include "defs.h"


//TODO: Esta bien que este aca?
DESCR_INT *idt = 0x0;	// La IDT ya esta en la posicion 0 //TODO: Aclarar, es la que viene con pure?
IDTR idtr;			// IDTR


void setup_idt() {

    setup_interrupts();

//    idtr.base = 0;
//    idtr.base += (qword) &idt;
//    idtr.limit = sizeof(idt)-1;

    //_lidt (&idtr);

    picMasterMask(0xFC);
    //picSlaveMask(0xFF);

    _sti();
}

void setup_interrupts() {
    setup_IDT_entry (0x20, 0x08, (qword)&_irq00Handler, ACS_INT);
    setup_IDT_entry (0x21, 0x08, (qword)&_irq01Handler, ACS_INT);
}


// Fuente: KernelIDT TP5 y TODO: Pagina idt osdev. Falta hacer & a los bits
void setup_IDT_entry (int index, byte selector, qword offset, byte access) {
    idt[index].offset_l = offset & 0xFFFF;
    idt[index].selector = selector;
    idt[index].zero_1 = 0;
    idt[index].access = access;
    idt[index].offset_m = (offset >> 16) & 0xFFFF;
    idt[index].offset_h = (offset >> 32) & 0xFFFF;
    idt[index].zero_2 = 0;
}
