#include <types.h>
#include <vga_funcs.h>

void next_line(void);

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
    int i;
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
            for(i = 0; i < 4; i++){
                putchar(0,WHITE,BLACK);
            }
            break;
        default:
            video[cursor++] = c;
            video[cursor++] = fmt;
            break;
    }
    if (cursor >= SCREENSIZE) {
        clear_screen();
    }
}

void printnum(int n, char f_color, char b_color){
    int i,aux;
    int count = 0;
    char c;

    if(n < 0){
        putchar('-',f_color,b_color);
        n *= -1;
    }
    aux = n;

    while(aux != 0){
        aux /= 10;
        ++count;
    }

    while(count--){
        aux = n;
        i = count;
        c = '0';

        while(i--){
            aux /= 10;
        }

        c += aux % 10;
        putchar(c, f_color,b_color);
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
    }else if(video[cursor - 2] == 0){
        while (video[cursor - 2] == 0) {
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

    int row_size = COLS*2;
    cursor -= cursor % row_size;
    cursor += row_size;
    return;
}

void print(char* string){
    color_print(string, WHITE, BLACK);
    return;
}

void color_print(char* string, char f_color, char b_color){
    while(*string){
        putchar(*string++,f_color,b_color);
    }
    return;
}
