#include <syscalls.h>
#include <syscall_interface.h>

void write(unsigned int channel, const void * source, unsigned int size) {
    _syscall(SYS_WRITE, channel,(qword)source, size);
}

void read(unsigned int channel, const void * dest, unsigned int size) {
    _syscall(SYS_READ,channel,(qword)dest, size);
}

void video(){
    _syscall(SYS_VIDEO, 0, 0, 0);
}

void paintPixel(unsigned int x, unsigned int y, qword color){
    _syscall(SYS_PAINT, x, y, color);
}

