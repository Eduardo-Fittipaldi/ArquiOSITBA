#ifndef VGA_FUNCS_H
#define VGA_FUNCS_H

// COLORS
// **USING ANY OF THESE AS FMT WILL RESULT IN A BLACK BACKGROUND WITH COLORED LETTERS**
#define BLACK 			0x00
#define BLUE			0x01
#define GREEN			0x02
#define CYAN			0x03
#define RED				0x04
#define MAGENTA			0x05
#define BROWN			0x06
#define LIGHT_GREY		0x07
#define DARK_GREY		0x08
#define LIGHT_BLUE		0x09
#define LIGHT_GREEN		0x0A
#define LIGHT_CYAN		0x0B
#define LIGHT_RED		0x0C
#define LIGHT_MAGENTA	0x0D
#define LIGHT_BROWN		0x0E
#define WHITE			0x0F

#define DEFAULT_BCKGRND_COLOR BLACK
#define DEFAULT_FRGRND_COLOR WHITE

//VIDEO CONSTANTS
#define ROWS 25
#define COLS 80
#define SCREENSIZE ROWS * COLS * 2

void clear_screen(void);

void putchar(char,char,char);

void delchar(void);

#endif //VGA_FUNCS_H
