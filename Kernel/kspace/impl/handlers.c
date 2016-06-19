#include <vga_funcs.h>
#include <syscalls_k.h>
#include "handlers.h"
#include "types.h"
#include "keyboard_k.h"

//Called from interrupts.asm
void irqDispatcher(dword irq) {
    switch (irq) {
        case 0:
            int_20();
            break;
        case 1:
            int_21();
            break;
    }
    return;
}

//Timer Tick
void int_20(){
}

//Keyboard Int
void int_21() {
    storeKey();

//    unsigned char c= getKey();
//    if(c){
//        putchar(c,WHITE,BLACK);
//    }
}