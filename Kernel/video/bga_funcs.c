#include <input_output.h>
#include "types.h"
#include "bga_funcs.h"

//SOURCE: OSDEV WIKI. http://wiki.osdev.org/Bochs_VBE_Extensions

static unsigned int width;
static unsigned int height;
static unsigned int bpp;
static dword* lfb_dir = (dword*)VBE_DISPI_LFB_PHYSICAL_ADDRESS;


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

void BgaSetVideoMode()
{
    BgaWriteRegister(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
    BgaWriteRegister(VBE_DISPI_INDEX_XRES, VBE_DISPI_XRES);
    BgaWriteRegister(VBE_DISPI_INDEX_YRES, VBE_DISPI_YRES);
    BgaWriteRegister(VBE_DISPI_INDEX_BPP, VBE_DISPI_BPP_32);
    BgaWriteRegister(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED);
}

void BgaSetBank(unsigned short BankNumber)
{
    BgaWriteRegister(VBE_DISPI_INDEX_BANK, BankNumber);
}

static dword BgaConvertColors(byte r, byte g, byte b){
    dword final_color = 0;
    final_color |= (r<<(8*2));
    final_color |= (g<<(8*1));
    final_color |= b;
    return final_color;
}

void BgaDrawPixel(int x, int y, qword color) {
    int offset = (y*VBE_DISPI_XRES + x);
    lfb_dir[offset] = color;
}

void BgaPaintScreen(byte r, byte g, byte b){
    int i,j;
    for(i = 0 ; i < VBE_DISPI_XRES ; i++){
        for(j = 0 ; j < VBE_DISPI_YRES ; j++) {
            BgaDrawPixel(i, j, BgaConvertColors(r,g,b));
        }
    }
}

void BgaTest(){
    int i,j;
    byte r,g,b;
    dword k;
    for(i = 0, r=0; i < VBE_DISPI_XRES ; i++){
        for(j = 0 ; j < VBE_DISPI_YRES ; j++) {
//            if(k == 0x00FFFFFF){
//                k = 0;
//            }
//            r = k >
            if(r==255){
                r=0;
            }
            BgaDrawPixel(i, j, BgaConvertColors(r,g,b));
            r++;
        }
    }
}

void BgaPaintSquare(int size, byte r, byte g, byte b){
    int i,j;
    for(i = 0; i< size; i++){
        for(j = 0 ; j < size; j++){
            BgaDrawPixel(i,j, BgaConvertColors(r,g,b));
        }
    }
}

//dword pciConfigReadDWord(byte bus, byte slot, byte func, byte offset){
//    dword address;
//    dword lbus = (dword) bus;
//    dword lslot = (dword) slot;
//    dword lfunc = (dword) func;
//    dword tmp = 0;
//
//    address =   (dword)((lbus << 16) | (lslot << 11) |
//                (lfunc << 8) | (offset & 0xfc) | ((dword)0x80000000));
//
//    _write_dword(0xFC8,address);
//
//    tmp = (_read_dword(0xCFC) >> ((offset & 2) * 8));
//
//}
//
//dword pciConfigReadWord(byte bus, byte slot, byte func, byte offset){
//    dword address;
//    dword lbus = (dword) bus;
//    dword lslot = (dword) slot;
//    dword lfunc = (dword) func;
//    word tmp = 0;
//
//    address =   (dword)((lbus << 16) | (lslot << 11) |
//                        (lfunc << 8) | (offset & 0xfc) | ((dword)0x80000000));
//
//    _write_dword(0xFC8,address);
//    tmp = ((_read_dword(0xCFC) >> ((offset & 2) * 8)) & 0xffff);
//
//}