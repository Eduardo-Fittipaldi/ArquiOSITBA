#ifndef KEYBOARD_K_H
#define KEYBOARD_K_H

#define BUFFER_SIZE 255
#define BETWEEN(x,y,z) (x >= y && x <= z)
#define IS_LETTER(x) (BETWEEN(x,'A','Z')|BETWEEN(x,'a','z'))
#define IS_SPACE(x) (x == ' ')
#define IS_DIGIT(x) (BETWEEN(x,'0','9'))
#define IS_ALPHA(x) (IS_LETTER(x)|IS_DIGIT(x))
#define IS_PUNCT(x) (BETWEEN(x,33,47)|BETWEEN(x,58,64)|BETWEEN(x,91,96)|BETWEEN(x,123,126))
#define IS_CONTROL(x) (BETWEEN(x,0,31) && x != '\b' && x != '\t' && x != '\n')

char getKey(void);
void storeKey(void);
char kbBufferIsEmpty(void);
void printBufferContents(void);
void initializeBuffer(void);

#endif //KEYBOARD_K_H