#include <Kernel/include/types.h>
#include "Kernel/video/include/vga_funcs.h"

byte * video = (byte *) 0xB8000;
unsigned int cursor = 0;

void clear_screen(void){
    unsigned int i = 0;

    while (i < SCREENSIZE) {
        video[i++] = ' ';
        video[i++] = BLACK;
        cursor = 0;
    }
}

void putchar(char c, char f_color, char b_color){
    if (cursor >= SCREENSIZE) {
        clear_screen();
    }
    // most significant 4 bits are background color, the other 4 are foreground color.
    char fmt = b_color << 4 | f_color;
    switch(c){
        case '\n':
            next_line();
            break;
        case '\b':
            delchar();
            break;
        case '\t':
            //TODO: implementar tabs
            break;
        default:
            video[cursor++] = c;
            video[cursor++] = fmt;
            break;
    }
}

void delchar(void){
    //if the cursor is at the start of the screen, do nothing.
    if (cursor == 0) {
        return;
    }
    // check if the cursor is at the start of a line.
    if ((cursor / 2) % COLS == 0 && video[cursor - 2] == ' ') {
        while (video[cursor - 2] == ' ') {
            cursor -= 2;
        }
    }
    // else, delete the previous character from the screen and reduce cursor by 2;
    else {
        video[--cursor] = BLACK;
        video[--cursor] = ' ';
    }
}

void next_line(void){
    // cursor/COLS is the number of the current line, so adding one to that gives us the next line.
    cursor = ((cursor/COLS) + 1) * COLS;
    return;
}