#include "Kernel/video/include/bga_funcs.h"

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

void BgaDrawPixel(int x, int y, int r, int g, int b) {
    unsigned char * linearBuffer = *addressAddress;
    int pos = x * width * 3 + y * 3;

    linearBuffer[pos++] = b;
    linearBuffer[pos++] = g;
    linearBuffer[pos] = r;
}