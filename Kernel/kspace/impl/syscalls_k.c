#include <syscalls_k.h>
#include <types.h>
#include <vga_funcs.h>
#include <vga_funcs.h>
#include <keyboard_k.h>
#include <bga_funcs.h>

static void sys_read_stdin(char * dest, unsigned int size);
static void sys_read_fractal(char * buffer, int len);

void syscallHandler(qword mode, qword arg1, qword arg2, qword arg3){
    switch(mode){
        case SYS_WRITE:
            sys_write(arg1,arg2,arg3);
            break;
        case SYS_READ:
            sys_read(arg1,arg2,arg3);
            break;
        case SYS_VIDEO:
            sys_video(arg1, arg2, arg3);
            break;
        case SYS_PAINT:
            sys_paint(arg1,arg2,arg3);
    }
}

void sys_write(unsigned int channel, char * string, unsigned int size){
    char foreground;
    char background;
    unsigned int curr = 0;

    switch(channel){
        case STDOUT:
            foreground = WHITE;
            background = BLACK;
            break;
        case STDERR:
            foreground = BLACK;
            background = RED;
            break;
        case STDDBG:
            foreground = GREEN;
            background = BLACK;
            break;
        default:
            return;
    }
    while(curr < size && string[curr]){
        putchar(string[curr++],foreground,background);
    }
}

void sys_read(unsigned int channel, char * dest, unsigned int size) {
    switch(channel){
        case STDIN:
            sys_read_stdin(dest,size);
            break;
        case STDFRACTAL:
            sys_read_fractal(dest, size);
            break;
        default:
            return;
    }
    return;
}

static void sys_read_fractal(char * dest, int len) {
    static int read_index = 0;
    char * dir = (char *)(FRACTAL_DATA + read_index);
    *dest = *dir;
    read_index++;
    if (*dir == '\0') {
        read_index = 0;
    }
    return;
}

static void sys_read_RGB(char * dest, int len) {
    static int read_index = 0;
    char * dir = (char *)(FRACTAL_DATA + read_index);
    int i = 0;
    while (i < 3 && *dir != 0) {
        dest[i++] = *dir++;
        read_index++;
    }
    if (*dir == '\0') {
        read_index = 0;
    }
    return;
}

static void sys_read_stdin(char * dest, unsigned int size){
    int i = 0;
    char c;

    while (i < size) {
        c = getKey();
        dest[i++] = c;
    }

    return;
}

void sys_video(qword arg1, qword arg2, qword arg3){
    BgaSetVideoMode();
}

void sys_paint(int x, int y, qword color){
    BgaDrawPixel(x,y,color);
}
