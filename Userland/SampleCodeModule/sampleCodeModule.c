/* sampleCodeModule.c */
#include <shell.h>
#include <stdio.h>

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


int main() {
	initShell();

	while(1){
		updateShell();
	}
}