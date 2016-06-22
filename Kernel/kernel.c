#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <interrupts_k.h>
#include <vga_funcs.h>
#include <test.h>
#include <syscalls_k.h>
#include <keyboard_k.h>
#include "types.h"
#include "handlers.h"

extern byte text;
extern byte rodata;
extern byte data;
extern byte bss;
extern byte endOfKernelBinary;
extern byte endOfKernel;

static const qword PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const fractalDataModule = (void*)0x500000;

typedef int (*EntryPoint)();

void clearBSS(void * bssAddress, qword bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(qword)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(qword)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		fractalDataModule
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((qword)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((qword)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((qword)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((qword)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}

int main()
{
	ncClear();
	setup_idt();
	initializeBuffer();

	((EntryPoint)sampleCodeModuleAddress)();

	return 0;
}
