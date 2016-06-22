#include <input_output.h>
#include <syscalls_k.h>
#include <vga_funcs.h>
#include <bga_funcs.h>
#include <test.h>
#include "keyboard_k.h"
#include "naiveConsole.h"
#include "keyboard_scancode.h"

//Internal method declarations
char convertKey(byte);
char proccessControlCode(byte);
char checkControlBit(byte);
void processControlCode(byte);
void initializeBuffer(void);

//Kernel Keyboard buffer variables
static dword controlCharacters;
static char kBuffer[BUFFER_SIZE] = {EMPTY};
static char testBuffer[BUFFER_SIZE] = {0};
static unsigned char readCounter = 0;
static unsigned char writeCounter = 0;


char getKey(void) {
    char key = kBuffer[readCounter];
    if(readCounter == writeCounter || key == EMPTY){
        return 0;
    }
    kBuffer[readCounter++] = (char)EMPTY;
    if(readCounter == BUFFER_SIZE){
        readCounter = 0;
    }

    return key;
}

void storeKey(void){
    char key = convertKey(_read_byte(0x60));
    if(key == NOWRITE){
        return;
    }
    kBuffer[writeCounter++] = key;
    if(writeCounter == BUFFER_SIZE){
        //If the Buffer is currently at the last character,
        //the start of the buffer is written again.
        writeCounter = 0;
    }
    return;
}

char convertKey(byte keyCode){
    char key;
    processControlCode(keyCode);

    if(keyCode < 0){
//        print("KEYCODE < 0\n");
        return NOWRITE;
    }

    if(keyCode >= mapSize) {
//        print("KEYCODE >= MAPSIZE\n");
        return NOWRITE;
    }

    if(checkControlBit(1)){
        key = SHIFT_KEYS[keyCode];
    } else {
        key = KEYS[keyCode];
    }

    if(IS_CONTROL(key)){
//        print("IS_CONTROL\n");
        return NOWRITE;
    }

    if(IS_LETTER(key) && checkControlBit(4)){
        key = (char)('A' + (key - 'a'));
    }

    return key;
}

char kbBufferIsEmpty(void) {
    return kBuffer[readCounter] == EMPTY;
}

/* void processControlNode(byte keyCode)
 * How it works:
 * Every time a CONTROL_CODE value is read, this function is called.
 * What it does is it switches a bit in a variable with 32 bits, depending on wether
 * that specific control key is pressed or not.
 *
 * Bit 0: Ctrl bit
 * Bit 1: Shift bit
 * Bit 2: Alt bit
 * Bit 3: Numlock bit
 * Bit 4: Capslock bit
 * Bit 5-19: Reserved
 * Bit 20-31: F1-F12 bits
 *
 * NOTE: F1-F12 function as switches in this OS.
 */
void processControlCode(byte keyCode){
    switch(keyCode) {
        case CTRL_PRESSED:
            controlCharacters |= 1;
            break;
        case LSHIFT_PRESSED:
            controlCharacters |= (1 << 1);
            controlCharacters ^= (1<<4);
            break;
        case RSHIFT_PRESSED:
            controlCharacters |= (1 << 1);
            controlCharacters ^= (1<<4);
            break;
        case ALT_PRESSED:
            controlCharacters |= (1 << 2);
            break;
        case NUMLCK_PRESSED:
            controlCharacters ^= 1 << 3;
            break;
        case CAPS_PRESSED:
            controlCharacters ^= 1 << 4;
            break;
        case F1_PRESSED:
            printBufferContents();
            controlCharacters ^= 1 << 20;
            break;
        case F2_PRESSED:
            _callerino(SYS_READ, STDIN, (qword)testBuffer, (qword)5);
            controlCharacters ^= 1 << 21;
            break;
        case F3_PRESSED:
            _callerino(SYS_WRITE, STDOUT,(qword)testBuffer,5);
            controlCharacters ^= 1 << 22;
            break;
        case F4_PRESSED:
            BgaSetVideoMode();
//            BgaPaintScreen(100,100,100);
            BgaTest();
            controlCharacters ^= 1 << 23;
            break;
        case F5_PRESSED:
            BgaPaintSquare(300,0xff,0,0);
            BgaPaintSquare(275,0xff,0xff,0);
            controlCharacters ^= 1 << 24;
            break;
        case F6_PRESSED:
            BgaPaintSquare(250,0,0xff,0);
            BgaPaintSquare(225,0,0xff,0xff);
            controlCharacters ^= 1 << 25;
            break;
        case F7_PRESSED:
            BgaPaintSquare(200,0,0,0xff);
            BgaPaintSquare(175,0xff,0,0xff);
            controlCharacters ^= 1 << 26;
            break;
        case F8_PRESSED:
            controlCharacters ^= 1 << 27;
            break;
        case F9_PRESSED:
            controlCharacters ^= 1 << 28;
            break;
        case F10_PRESSED:
            controlCharacters ^= 1 << 29;
            break;
        case F11_PRESSED:
            controlCharacters ^= 1 << 30;
            break;
        case F12_PRESSED:
            controlCharacters ^= 1 << 31;
            break;
        case LSHIFT_RELEASED:
            controlCharacters &= 0xFFFD;
            controlCharacters ^= (1<<4);
            break;
        case RSHIFT_RELEASED:
            controlCharacters &= 0xFFFD;
            controlCharacters ^= (1<<4);
            break;
        case ALT_RELEASED:
            controlCharacters &= 0xFFFB;
            controlCharacters ^= (1<<4);
            break;
        case CTRL_RELEASED:
            controlCharacters &= 0xFFFE;
            controlCharacters ^= (1<<4);
        default:
            return;
    }
}

char checkControlBit(byte bit){
    return (char) ((controlCharacters >> bit) & 1);
}

void printBufferContents(void){
    int i;
    char background;
    for (i = 0; i < BUFFER_SIZE; i++) {
        background = WHITE;
        if(i == readCounter && i == writeCounter){
            background = MAGENTA;
        }else if(i == writeCounter){
            background = RED;
        }else if(i == readCounter){
            background = BLUE;
        }
        if(kBuffer[i] != EMPTY){
            putchar(kBuffer[i], GREEN, background);
        }else{
            putchar('.', GREEN, background);
        }

    }
    putchar(' ',WHITE, GREEN);
    putchar('\n',WHITE, GREEN);
}

void initializeBuffer(void){
    int i;
    for (i = 0; i < BUFFER_SIZE; i++) {
        kBuffer[i] = EMPTY;
    }
}