#ifndef KEYBOARD_SCANCODE_MAP_H
#define KEYBOARD_SCANCODE_MAP_H

#define SC_IS_LETTER(x) (BETWEEN(x,16,25)|BETWEEN(x,30,38)|BETWEEN(x,44,50))
#define SC_IS_DIGIT(x) (BETWEEN(x,2,11)|BETWEEN(x,71,73)|BETWEEN(x,75,78)|BETWEEN(x,79,82))
#define SC_IS_SPACE(x) (x == 57)
#define SC_IS_ALPHA(x) (SC_IS_LETTER(x)|SC_IS_DIGIT(x)|SC_IS_SPACE(x))
#define SC_IS_CONTROL(x) (!SC_IS_ALPHA(x))

#define EMPTY -1 //Any negative value will do
#define NOWRITE -2

//ASCII VALUES
#define CONTROL_CODE 1
#define ESC 27
#define TAB '\t'
#define BACKSPACE '\b'
#define ENTER '\n'
#define LSHIFT CONTROL_CODE
#define RSHIFT CONTROL_CODE
#define CTRL CONTROL_CODE
#define CAPSLCK CONTROL_CODE
#define NUMLCK CONTROL_CODE
#define SCRLCK 0
#define ALT CONTROL_CODE
#define F1 CONTROL_CODE
#define F2 CONTROL_CODE
#define F3 CONTROL_CODE
#define F4 CONTROL_CODE
#define F5 CONTROL_CODE
#define F6 CONTROL_CODE
#define F7 CONTROL_CODE
#define F8 CONTROL_CODE
#define F9 CONTROL_CODE
#define F10 CONTROL_CODE
#define F11 CONTROL_CODE
#define F12 CONTROL_CODE
#define UA 17
#define DA 18
#define LA 19
#define RA 18
#define SUPR 127

//SCANCODES
#define ENTER_PRESSED 0x1C
#define BACKSPACE_PRESSED 0x0E
#define LSHIFT_PRESSED 0x2A
#define LSHIFT_RELEASED 0xB7
#define RSHIFT_PRESSED 0x36
#define RSHIFT_RELEASED 0xAA
#define CAPS_PRESSED 0x3A
#define NUMLCK_PRESSED 0x45
#define CTRL_PRESSED 0x1D
#define CTRL_RELEASED 0x9D
#define ALT_PRESSED 0x38
#define ALT_RELEASED 0xB8
#define UARROW_PRESSED 0x48
#define DARROW_PRESSED 0x50
#define LARROW_PRESSED 0x4B
#define RARROW_PRESSED 0x4D
#define SUPR_PRESSED 0x53
#define F1_PRESSED 0x3B
#define F2_PRESSED 0x3C
#define F3_PRESSED 0x3D
#define F4_PRESSED 0x3E
#define F5_PRESSED 0x3F
#define F6_PRESSED 0x40
#define F7_PRESSED 0x41
#define F8_PRESSED 0x42
#define F9_PRESSED 0x43
#define F10_PRESSED 0x44
#define F11_PRESSED 0x58
#define F12_PRESSED 0x59

static int mapSize = 90;

//Scancode set 1
char KEYS[] = {0, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', 				// 00 - 10  (0x00 - 0x0A)
                      '0', '\'', '=', BACKSPACE, TAB, 'q', 'w', 'e', 'r', 't',		// 11 - 20  (0x0B - 0x14)
                      'y', 'u', 'i', 'o', 'p', '`', '+', ENTER, CTRL, 'a',			// 21 - 30  (0x15 - 0x1E)
                      's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 0, '{', 		        // 31 - 40  (0x1F - 0x27)
                      '|', LSHIFT, '}', 'z', 'x', 'c', 'v', 'b', 'n', 'm',  		// 41 - 50  (0x28 - 0x32)
                      ',', '.', '-', RSHIFT, '*', ALT, ' ', CAPSLCK, F1, F2,	    // 51 - 60  (0x33 - 0x3C)
                      F3, F4, F5, F6, F7, F8, F9, F10, NUMLCK, SCRLCK, 	            // 61 - 70  (0x3D - 0x46)
                      '7', '8', '9', '-', '4', '5', '6', '+', '1', '2',  		    // 71 - 80  (0x47 - 0x50)
                      '3', '0', '.',0,0,0, F11, F12,0,0}; 				            // 81 - 90  (0x51 - 0x5B)

char SHIFT_KEYS[] = {0, ESC, '!', '"', '#', '$', '%', '&', '/', '(', ')', 		        // 00 - 10  (0x00 - 0x0A)
                            '=', '?', '=', BACKSPACE, TAB, 'q', 'w', 'e', 'r', 't',	    // 11 - 20  (0x0B - 0x14)
                            'y', 'u', 'i', 'o', 'p', '^', '*', ENTER, CTRL, 'a',		// 21 - 30  (0x15 - 0x1E)
                            's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 0, '[', 	        // 31 - 40  (0x1F - 0x27)
                            '`', LSHIFT, ']', 'z', 'x', 'c', 'v', 'b', 'n', 'm',  		// 41 - 50  (0x28 - 0x32)
                            ';', ':', '_', RSHIFT, '*', ALT, ' ', CAPSLCK, F1, F2,      // 51 - 60  (0x33 - 0x3C)
                            F3, F4, F5, F6, F7, F8, F9, F10, NUMLCK, SCRLCK,            // 61 - 70  (0x3D - 0x46)
                            '7', UA, '9', '-', LA, '5', RA, '+', '1', DA,               // 71 - 80  (0x47 - 0x50)
                            '3', '0', SUPR,0,0,0, F11, F12,0,0}; 				        // 81 - 90  (0x51 - 0x5A)

#endif //KEYBOARD_SCANCODE_MAP_H
