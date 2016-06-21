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


//int video(unsigned int width, unsigned int height, unsigned int bpp) {
//    return _syscall(5, width, height, bpp);
//}
//
//int draw(unsigned int x, unsigned int y, uint8_t r, uint8_t g, uint8_t b) {
//    unsigned int color = 0;
//    color += r;
//    color = color << 8;
//    color += g;
//    color = color << 8;
//    color += b;
//    return _syscall(6, x, y, color);
//}

