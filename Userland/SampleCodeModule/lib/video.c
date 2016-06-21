#include <video.h>
#include "syscalls.h"

int abs(int x){
    if(x < 0 ){
        return -x;
    }
    return x;
}

int sgn(int x) {
    if(x < 0){
        return -1;
    }else if(x > 0){
        return 1;
    }
    return 0;
}

//Line plotting algorithm source:
//http://www.brackeen.com/vga/source/djgpp20/lines.c.html

void drawLine(unsigned int x1,unsigned int y1, unsigned int x2, unsigned int y2){
    int dx,dy,sdx,sdy,px,py,dxabs,dyabs,i;
    float slope;

    dx=x2-x1;      /* the horizontal distance of the line */
    dy=y2-y1;      /* the vertical distance of the line */
    dxabs=abs(dx);
    dyabs=abs(dy);
    sdx=sgn(dx);
    sdy=sgn(dy);
    if (dxabs>=dyabs) /* the line is more horizontal than vertical */
    {
        slope=(float)dy / (float)dx;
        for(i=0;i!=dx;i+=sdx)
        {
            px=i+x1;
            py=slope*i+y1;
            paintPixel(px,py,0x00ffffff);
        }
    }
    else /* the line is more vertical than horizontal */
    {
        slope=(float)dx / (float)dy;
        for(i=0;i!=dy;i+=sdy)
        {
            px=slope*i+x1;
            py=i+y1;
            paintPixel(px,py,0x00ffffff);
        }
    }
}

