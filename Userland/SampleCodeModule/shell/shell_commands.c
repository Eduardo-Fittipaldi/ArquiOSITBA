#include <syscalls.h>
#include <shell_commands.h>
#include <string.h>
#include "shell_commands.h"
#include "stdio.h"
#include "video.h"

#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 768

//SierpinskiTriangle source code:
//http://lodev.org/cgtutor/sierpinski.html

static void showcaseCommands();
static void sierpinskiSet(int iter, int x1, int y1, int x2, int y2, int x3, int y3);
static void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);

command_t command_list[COMMANDS_AMOUNT];



int echo(char * arg) {
    printf(arg);
    putchar('\n');

    return 0;
}

int help(char * arg) {

    command_t command;
    int i, found = 0;
    if(!strcmp(arg,"all")){
        showcaseCommands();
        return 0;
    }

    for (i = 0; i < COMMANDS_AMOUNT && !found; i++) {
        command = command_list[i];
        if (!strcmp(arg,command.name)){
            printf("%s\n", command.desc);
            found = 1;
        }
    }

    if (!found) {
        fprintf(STDERR, "Invalid argument: '%s'\n", arg);
        return -1;
    }

    return 0;

}

int fractal(char * arg){
    if(!strcmp(arg,"julia")){
        video();
        juliaSet();
    }
    if(!strcmp(arg,"sierp")){
        int iter = 0 ,x1 = 1,x2 = 2,x3 = 3,y1 = 4,y2 = 5,y3 = 6;
        int args = fscanf(STDFRACTAL, "%d %d %d %d %d %d %d", &iter, &x1, &y1, &x2, &y2, &x3, &y3);

        if(args != 7){
            fprintf(STDERR, "Invalid File Format!\n");
            return -1;
        }
        video();
        sierpinskiSet(iter,x1,y1,x2,y2,x3,y3);
    }
}

static void showcaseCommands(){
    int i;
    command_t command;
    printf("Available commands (Type \"help 'command'\" to learn more):\n");

    for (i = 0; i < COMMANDS_AMOUNT; i++) {
        command = command_list[i];
        printf("%s,", command.name);
    }

    printf("\n");

}

static unsigned int ConvertColors(unsigned char r, unsigned char g, unsigned char b){
    unsigned int final_color = 0;
    final_color |= (r<<(8*2));
    final_color |= (g<<(8*1));
    final_color |= b;
    return final_color;
}


static void HsvToRgb(unsigned char *r, unsigned char *g, unsigned char *b, unsigned char h, unsigned char s, unsigned char v)
{
    unsigned char region, fpart, p, q, t;

    if(s == 0) {
        /* color is grayscale */
        *r = *g = *b = v;
        return;
    }

    /* make hue 0-5 */
    region = h / 43;
    /* find remainder part, make it from 0-255 */
    fpart = (h - (region * 43)) * 6;

    /* calculate temp vars, doing integer multiplication */
    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * fpart) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - fpart)) >> 8))) >> 8;

    /* assign temp vars based on color cone region */
    switch(region) {
        case 0:
            *r = v; *g = t; *b = p; break;
        case 1:
            *r = q; *g = v; *b = p; break;
        case 2:
            *r = p; *g = v; *b = t; break;
        case 3:
            *r = p; *g = q; *b = v; break;
        case 4:
            *r = t; *g = p; *b = v; break;
        default:
            *r = v; *g = p; *b = q; break;
    }

    return;
}

void juliaSet() {

    //each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
    double cRe, cIm;           //real and imaginary part of the constant c, determines shape of the Julia Set
    double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
    double zoom=1, moveX=0	, moveY=0; //you can change these to zoom and change position
    //ColorRGB color; //the RGB color value for the pixel
    int maxIterations=128; //after how much iterations the function should stop


    //pick some values for the constant c, this determines the shape of the Julia Set
    cRe = -0.7;
    cIm = 0.27015;

    //begin the program loop

    //draw the fractal
    for(int y = 0; y < DEFAULT_HEIGHT; y++){
        for(int x = 0; x < DEFAULT_WIDTH; x++)
        {
            //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
            newRe = 1.5 * (x - DEFAULT_WIDTH / 2) / (0.5 * zoom * DEFAULT_WIDTH) + moveX;
            newIm = (y - DEFAULT_HEIGHT / 2) / (0.5 * zoom * DEFAULT_HEIGHT) + moveY;
            //i will represent the number of iterations
            int i;
            //start the iteration process
            for(i = 0; i < maxIterations; i++)
            {
                //remember value of previous iteration
                oldRe = newRe;
                oldIm = newIm;
                //the actual iteration, the real and imaginary part are calculated
                newRe = oldRe * oldRe - oldIm * oldIm + cRe;
                newIm = 2 * oldRe * oldIm + cIm;
                //if the point is outside the circle with radius 2: stop
                if((newRe * newRe + newIm * newIm) > 4) break;
            }
            //use color model conversion to get rainbow palette, make brightness black if maxIterations reached
            unsigned char r, g, b;
            HsvToRgb(&r, &g, &b, i % 256, 255, 255 * (i < maxIterations));
            unsigned int color = ConvertColors(r,g,b);

            //draw the pixel
            paintPixel(x, y, color);

        }
    }


}

static void drawSubTriangle(int n, int depth, int x1, int y1, int x2, int y2, int x3, int y3){
    drawLine(x1,y1,x2,y2);
    drawLine(x1,y1,x3,y3);
    drawLine(x2,y2,x3,y3);
    if(n < depth){

        drawSubTriangle
                (
                        n+1, //Number of recursions for the next call increased with 1
                        depth,
                        (x1 + x2) / 2 + (x2 - x3) / 2, //x coordinate of first corner
                        (y1 + y2) / 2 + (y2 - y3) / 2, //y coordinate of first corner
                        (x1 + x2) / 2 + (x1 - x3) / 2, //x coordinate of second corner
                        (y1 + y2) / 2 + (y1 - y3) / 2, //y coordinate of second corner
                        (x1 + x2) / 2, //x coordinate of third corner
                        (y1 + y2) / 2  //y coordinate of third corner
                );
        //Smaller triangle 2
        drawSubTriangle
                (
                        n+1, //Number of recursions for the next call increased with 1
                        depth,
                        (x3 + x2) / 2 + (x2 - x1) / 2, //x coordinate of first corner
                        (y3 + y2) / 2 + (y2 - y1) / 2, //y coordinate of first corner
                        (x3 + x2) / 2 + (x3 - x1) / 2, //x coordinate of second corner
                        (y3 + y2) / 2 + (y3 - y1) / 2, //y coordinate of second corner
                        (x3 + x2) / 2, //x coordinate of third corner
                        (y3 + y2) / 2  //y coordinate of third corner
                );
        //Smaller triangle 3
        drawSubTriangle
                (
                        n+1, //Number of recursions for the next call increased with 1
                        depth,
                        (x1 + x3) / 2 + (x3 - x2) / 2, //x coordinate of first corner
                        (y1 + y3) / 2 + (y3 - y2) / 2, //y coordinate of first corner
                        (x1 + x3) / 2 + (x1 - x2) / 2, //x coordinate of second corner
                        (y1 + y3) / 2 + (y1 - y2) / 2, //y coordinate of second corner
                        (x1 + x3) / 2, //x coordinate of third corner
                        (y1 + y3) / 2  //y coordinate of third corner
                );

    }
}

static void sierpinskiSet(int iter, int x1, int y1, int x2, int y2, int x3, int y3){
    drawLine(x1,y1,x2,y2);
    drawLine(x1,y1,x3,y3);
    drawLine(x2,y2,x3,y3);

    drawSubTriangle(
            1, iter, //This represents the first recursion
            (x1 + x2) / 2, //x coordinate of first corner
            (y1 + y2) / 2, //y coordinate of first corner
            (x1 + x3) / 2, //x coordinate of second corner
            (y1 + y3) / 2, //y coordinate of second corner
            (x2 + x3) / 2, //x coordinate of third corner
            (y2 + y3) / 2  //y coordinate of third corner
    );
}

static void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    drawLine(x1, y1, x2, y2);
    drawLine(x1, y1, x3, y3);
    drawLine(x2, y2, x3, y3);
}