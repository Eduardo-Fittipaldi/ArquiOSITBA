#include <Kernel/kspace/include/input_output.h>
#include <Kernel/kspace/include/syscalls_k.h>
#include "Kernel/kspace/include/keyboard_k.h"
#include "naiveConsole.h"

//TODO: Cambiar.

static int ctrlPressed = 0;
static int shiftPressed = 0;
static int altPressed = 0;
static int numLock = 0;
static int mapSize = 90;
//Kernel Keyboard buffer
static unsigned char kBuffer[BUFFER_SIZE] = {0};
static unsigned char readCounter = 0;
static unsigned char writeCounter = 0;

unsigned char getKey(void) {
    if(isEmpty()){
        return 0;
    }
    unsigned char key = kBuffer[readCounter++];
    if(readCounter == BUFFER_SIZE){
        readCounter = 0;
    }
    return key;
}

void storeKey(void){
    byte scanCode = _read_byte(0x60);
    unsigned char key = convertKey(scanCode);
    if(key == 0 ){
        return;
    }
    if(writeCounter == BUFFER_SIZE){
        //If the Buffer is currently at the last character,
        //the start of the buffer is written again.
        writeCounter = 0;
    }
    kBuffer[writeCounter] = key;
    return;
}

char convertKey(byte keyCode){
    // Key Pressed
    if (keyCode >= 0 && keyCode < mapSize) {
        switch(keyCode){
            case 0x1C: // ENTER
                break;
            case 0x0E: //BACKSPACE
                break;
            case 0x2A: //LSHIFT
                shiftPressed ^= 1;
                break;
            case 0x36: //RSHIFT
                shiftPressed ^= 1;
                break;
            case 0x3A: //CAPSLOCK
                shiftPressed ^= 1;
                break;
            case 0x1D: //LCTRL
                ctrlPressed ^= 1;
                break;
            case 0x48: //UP ARROW
                if(shiftPressed){
                }
                break;
            case 0x50: //DOWN ARROW
                if(shiftPressed){
                }
                break;
            case 0x4B: //LEFT ARROW
                if(shiftPressed){
                }
                break;
            case 0x4D: //RIGHT ARROW
                if(shiftPressed){
                }
                break;
            case 0x53: //SUPR
                if(shiftPressed){
                    //delete()
                }
                break;
            default:
                if(shiftPressed){
                    return *SHIFT_KEYS[keyCode];
                } else {
                    return *KEYS[keyCode];
                }
        }
    }// Key Released
    else {
        if (keyCode == 0xB7 || keyCode == 0xAA) {			// L/R Shift
            shiftPressed ^= 1;
        }
        if (keyCode == 157) {							// Ctrl
            ctrlPressed ^= 1;
        }
    }

    return 0;
}

unsigned char isEmpty(void) {
    return kBuffer[readCounter] == 0;
}
