#include <input_output.h>
#include "types.h"
#include "bga_funcs.h"

static unsigned int width;
static unsigned int height;
static unsigned int bpp;

void BgaWriteRegister(unsigned short IndexValue, unsigned short DataValue)
{
    _write_word(VBE_DISPI_IOPORT_INDEX, IndexValue);
    _write_word(VBE_DISPI_IOPORT_DATA, DataValue);
}

word BgaReadRegister(unsigned short IndexValue)
{
    _write_word(VBE_DISPI_IOPORT_INDEX, IndexValue);
    return _read_word(VBE_DISPI_IOPORT_DATA);
}

dword BgaIsAvailable(void)
{
    return (BgaReadRegister(VBE_DISPI_INDEX_ID) == VBE_DISPI_ID5);
}

void BgaSetVideoMode(unsigned int Width, unsigned int Height, unsigned int BitDepth, int UseLinearFrameBuffer, int ClearVideoMemory)
{
    BgaWriteRegister(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
    BgaWriteRegister(VBE_DISPI_INDEX_XRES, Width);
    BgaWriteRegister(VBE_DISPI_INDEX_YRES, Height);
    BgaWriteRegister(VBE_DISPI_INDEX_BPP, BitDepth);
    BgaWriteRegister(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED |
                                             (UseLinearFrameBuffer ? VBE_DISPI_LFB_ENABLED : 0) |
                                             (ClearVideoMemory ? 0 : VBE_DISPI_NOCLEARMEM));
}

void BgaSetBank(unsigned short BankNumber)
{
    BgaWriteRegister(VBE_DISPI_INDEX_BANK, BankNumber);
}

//void BgaDrawPixel(int x, int y, int r, int g, int b) {
//    unsigned char * linearBuffer = *addressAddress;
//    int pos = x * width * 3 + y * 3;
//
//    linearBuffer[pos++] = b;
//    linearBuffer[pos++] = g;
//    linearBuffer[pos] = r;
//}

dword pciConfigReadDWord(byte bus, byte slot, byte func, byte offset){
    dword address;
    dword lbus = (dword) bus;
    dword lslot = (dword) slot;
    dword lfunc = (dword) func;
    dword tmp = 0;

    address =   (dword)((lbus << 16) | (lslot << 11) |
                (lfunc << 8) | (offset & 0xfc) | ((dword)0x80000000));

    _write_dword(0xFC8,address);

    tmp = (_read_dword(0xCFC) >> ((offset & 2) * 8));

}

dword pciConfigReadWord(byte bus, byte slot, byte func, byte offset){
    dword address;
    dword lbus = (dword) bus;
    dword lslot = (dword) slot;
    dword lfunc = (dword) func;
    word tmp = 0;

    address =   (dword)((lbus << 16) | (lslot << 11) |
                        (lfunc << 8) | (offset & 0xfc) | ((dword)0x80000000));

    _write_dword(0xFC8,address);
    tmp = ((_read_dword(0xCFC) >> ((offset & 2) * 8)) & 0xffff);

}