#include "common.h"

s32 func_002CABA0(s32 arg0, s32 arg1);

#define W32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define W16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define W64(p, o) (*(s64 *)((u8 *)(p) + (o)))

void func_002CA4A0(s32 arg0, s32 arg1, s32 arg2) {
    u8 *src = (u8 *)arg1;
    s32 *slot = (s32 *)(s32)func_002CABA0(arg0, arg1);
    u8 *dst = (u8 *)slot;
    u8 *d;
    s32 s1;
    s32 a3;

    s1 = W32(arg0, 0x1FC0);
    W32(dst, 0) = 1;
    d = dst + 8;
    W32(d, 0x10) = W32(src, 0x74);
    W32(d, 0x0) = W32(src, 0x5C);
    W32(d, 0x4) = W32(src, 0x60);
    W32(d, 0x8) = W32(src, 0x64);
    W32(d, 0xC) = W32(src, 0x68);
    W32(s1, 0x70) = arg1;
    W32(d, 0x1C) = W32(arg0, 0x38);
    W32(d, 0x20) = W32(src, 0x8);
    W32(d, 0x38) = W32(src, 0x54);
    W32(d, 0x14) = W32(src, 0x38);
    *(s32 *)arg2 = (s32)d;
    W32(d, 0x18) = W32(src, 0x3C);
    a3 = W32(src, 0x9C);
    W32(d, 0x3C) = a3;
    W32(d, 0x40) = W32(src, 0xA0);
    W32(d, 0x24) = W32(src, 0x40);
    W32(d, 0x28) = W32(src, 0x44);
    W32(d, 0x2C) = W32(src, 0x48);
    W32(d, 0x30) = W32(src, 0x4C);
    W32(d, 0x34) = W32(src, 0x50);
    W32(d, 0x48) = (a3 != 0) ? 1 : 2;
    W64(d, 0x50) = W64(src, 0xE0);
    W32(d, 0x58) = W32(src, 0x94);
    W32(d, 0x5C) = W32(src, 0x98);
    W32(d, 0x60) = W32(src, 0xA4);
    W32(d, 0x64) = W32(src, 0xA8);
    W16(d, 0x68) = W16(src, 0xAC);
    W16(d, 0x6A) = W16(src, 0xAE);
    W8(d, 0x6C) = W8(src, 0xB1);
    W8(d, 0x6D) = W8(src, 0xB2);
    W8(d, 0x6E) = W8(src, 0xB3);
    W8(d, 0x6F) = W8(src, 0xB5);
    W8(d, 0x70) = W8(src, 0xB6);
    W8(d, 0x71) = W8(src, 0xB7);
    W8(d, 0x72) = W8(src, 0xB8);
    W8(d, 0x73) = W8(src, 0xB9);
    W8(d, 0x74) = W8(src, 0xBA);
    W8(d, 0x75) = W8(src, 0xBB);
    W8(d, 0x76) = W8(src, 0xBC);
    W8(d, 0x77) = W8(src, 0xBD);
    W8(d, 0x78) = W8(src, 0xBE);
    W8(d, 0x79) = W8(src, 0xBF);
    W8(d, 0x7A) = W8(src, 0xC0);
}
