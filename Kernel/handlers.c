#include "handlers.h"
#include "types.h"
#include "naiveConsole.h"
#include "keyboard_c.h"


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
//    ncPrint("asd");
}

//Keyboard Int
void int_21() {
    printKey();
}