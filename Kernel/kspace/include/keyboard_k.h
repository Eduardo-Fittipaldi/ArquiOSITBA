#ifndef KEYBOARD_K_H
#define KEYBOARD_K_H

#define BUFFER_SIZE 10

//Scancode set 1
const char* KEYS[] = {"", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", 				// 00 - 10  (0x00 - 0x0A)
                      "0", "'", "¿", "BACKSPACE", "TAB", "q", "w", "e", "r", "t",		// 11 - 20  (0x0B - 0x14)
                      "y", "u", "i", "o", "p", "`", "+", "ENTER", "LCTRL", "a",			// 21 - 30  (0x15 - 0x1E)
                      "s", "d", "f", "g", "h", "j", "k", "l", "", "{", 					// 31 - 40  (0x1F - 0x27)
                      "|", "LSHIFT", "}", "z", "x", "c", "v", "b", "n", "m",  			// 41 - 50  (0x28 - 0x32)
                      ",", ".", "-", "RSHIFT", "*", "ALT", " ", "CAPSLCK", "F1", "F2",	// 51 - 60  (0x33 - 0x3C)
                      "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "NUMLCK", "SCRLCK", 	// 61 - 70  (0x3D - 0x46)
                      "7", "8", "9", "-", "4", "5", "6", "+", "1", "2",  		        // 71 - 80  (0x47 - 0x50)
                      "3", "0", ".", "", "", "", "F11", "F12", "", ""}; 				// 81 - 90  (0x51 - 0x5B)

const char* SHIFT_KEYS[] = {"", "ESC", "!", "\"", "#", "$", "%", "&", "/", "(", ")", 		// 00 - 10  (0x00 - 0x0A)
                            "=", "?", "¡", "BACKSPACE", "TAB", "Q", "W", "E", "R", "T",	    // 11 - 20  (0x0B - 0x14)
                            "Y", "U", "I", "O", "P", "^", "*", "ENTER", "LCTRL", "A",		// 21 - 30  (0x15 - 0x1E)
                            "S", "D", "F", "G", "H", "J", "K", "L", "", "[", 				// 31 - 40  (0x1F - 0x27)
                            "°", "LSHIFT", "]", "Z", "X", "C", "V", "B", "N", "M",  		// 41 - 50  (0x28 - 0x32)
                            ";", ":", "_", "RSHIFT", "*", "ALT", " ", "CAPSLCK", "F1", "F2",// 51 - 60  (0x33 - 0x3C)
                            "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "NUMLCK", "SCRLCK",// 61 - 70  (0x3D - 0x46)
                            "7", "UARROW", "9", "-", "LARROW", "5", "RARROW", "+", "1", "DARROW",// 71 - 80  (0x47 - 0x51)
                            "3", "0", ".", "", "", "", "F11", "F12", "", ""}; 				// 81 - 90  (0x52 - 0x5C)

unsigned char getKey(void);
void storeKey(void);
unsigned char isEmpty(void);

#endif //KEYBOARD_K_H