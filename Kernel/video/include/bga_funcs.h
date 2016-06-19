#ifndef BGA_FUNCS_H
#define BGA_FUNCS_H


//SOURCE: OSDEV WIKI.
#define VBE_DISPI_TOTAL_VIDEO_MEMORY_MB  16
#define VBE_DISPI_4BPP_PLANE_SHIFT       22

#define VBE_DISPI_BANK_ADDRESS           0xA0000
#define VBE_DISPI_BANK_SIZE_KB           64

#define VBE_DISPI_XRES                  1024
#define VBE_DISPI_YRES                  768
#define VBE_DISPI_BPP_32                0x20

#define VBE_DISPI_IOPORT_INDEX           0x01CE
#define VBE_DISPI_IOPORT_DATA            0x01CF

#define VBE_DISPI_INDEX_ID               0x0
#define VBE_DISPI_INDEX_XRES             0x1
#define VBE_DISPI_INDEX_YRES             0x2
#define VBE_DISPI_INDEX_BPP              0x3
#define VBE_DISPI_INDEX_ENABLE           0x4
#define VBE_DISPI_INDEX_BANK             0x5
#define VBE_DISPI_INDEX_VIRT_WIDTH       0x6
#define VBE_DISPI_INDEX_VIRT_HEIGHT      0x7
#define VBE_DISPI_INDEX_X_OFFSET         0x8
#define VBE_DISPI_INDEX_Y_OFFSET         0x9
#define VBE_DISPI_INDEX_VIDEO_MEMORY_64K 0xa

#define VBE_DISPI_ID5                    0xB0C5

#define VBE_DISPI_DISABLED               0x00
#define VBE_DISPI_ENABLED                0x01
#define VBE_DISPI_GETCAPS                0x02
#define VBE_DISPI_8BIT_DAC               0x20
#define VBE_DISPI_LFB_ENABLED            0x40
#define VBE_DISPI_NOCLEARMEM             0x80

#define VBE_DISPI_LFB_PHYSICAL_ADDRESS   0xFD000000

#define VBE_DISPI_TOTAL_VIDEO_MEMORY_KB  (VBE_DISPI_TOTAL_VIDEO_MEMORY_MB * 1024)
#define VBE_DISPI_TOTAL_VIDEO_MEMORY_BYTES (VBE_DISPI_TOTAL_VIDEO_MEMORY_KB * 1024)

void BgaSetVideoMode(void);
void BgaSwitchVideoMode(void);
void BgaPaintScreen(byte r, byte g, byte b);
void BgaPaintSquare(int size, byte r, byte g, byte b);
void BgaTest();

#endif //BGA_FUNCS_H1
