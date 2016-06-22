#include <vga_funcs.h>
#include <naiveConsole.h>
#include "types.h"
#include "interrupts_k.h"
#include "defs.h"

DESCR_INT * idt;

void setup_idt() {
    idt = 0;

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


// Source: KernelIDT TP5 y http://wiki.osdev.org/Interrupt_Descriptor_Table
void setup_IDT_entry (int index, byte selector, qword offset, byte access) {
    idt[index].selector = selector;
    idt[index].offset_l = (word)(offset & 0xFFFF);
    idt[index].offset_m = (word)((offset >> 16) & 0xFFFF);
    idt[index].offset_h = (dword)((offset >> 32) & 0xFFFFFFFF);
    idt[index].access = access;
    idt[index].zero_1 = 0;
    idt[index].zero_2 = 0;
}
