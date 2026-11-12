#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define H(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define B(p, off) (*(u8 *)((u8 *)(p) + (off)))

extern u8 D_0037B180[] __attribute__((section(".data")));

void func_002E2230(u8 *arg0) {
    u8 *v1 = arg0 + 0x160;
    u8 *a0 = arg0 + 0x58;
    s32 idx;

    W(a0, 0x40) = 0;
    W(arg0, 0x58) = W(v1, 0x2C4);
    W(a0, 0x04) = W(v1, 0x2C8);
    W(a0, 0x08) = W(v1, 0x2CC);
    W(a0, 0x0C) = W(v1, 0x2D0);
    W(a0, 0x14) = W(v1, 0xDC);
    W(a0, 0x10) = W(v1, 0x10);
    W(a0, 0x1C) = W(v1, 0xBC);
    W(a0, 0x18) = W(v1, 0xE0);
    W(a0, 0x20) = W(v1, 0xC0);
    W(a0, 0x24) = W(v1, 0xC4);
    W(a0, 0x28) = W(v1, 0xC8);
    W(a0, 0x2C) = W(v1, 0xCC);
    W(a0, 0x30) = W(v1, 0x43C);
    W(a0, 0x34) = W(v1, 0x42C);
    W(a0, 0x38) = W(v1, 0x118);
    W(a0, 0x3C) = W(v1, 0x4C);
    W(a0, 0x44) = 1;
    W(a0, 0x48) = W(v1, 0x2D4);
    W(a0, 0x4C) = W(v1, 0x2D8);
    H(a0, 0x50) = H(v1, 0x80);
    H(a0, 0x52) = H(v1, 0x84);
    idx = ((W(v1, 0x48) * 2 + W(v1, 0x134)) * 2) + W(v1, 0x11C);
    B(a0, 0x54) = D_0037B180[idx];
    B(a0, 0x55) = B(v1, 0x13C);
    B(a0, 0x56) = (u8)W(v1, 0x11C);
    B(a0, 0x57) = (u8)W(v1, 0x134);
    B(a0, 0x58) = B(v1, 0x3C4);
    B(a0, 0x59) = B(v1, 0x0C);
    B(a0, 0x5A) = B(v1, 0x20);
    B(a0, 0x5B) = B(v1, 0x64);
    B(a0, 0x5C) = B(v1, 0x68);
    B(a0, 0x5D) = B(v1, 0x44);
    B(a0, 0x5E) = (u8)W(v1, 0x48);
    B(a0, 0x5F) = B(v1, 0x60);
    B(a0, 0x60) = B(v1, 0x6C);
    B(a0, 0x61) = B(v1, 0x70);
    B(a0, 0x62) = B(v1, 0x74);
    B(a0, 0x63) = B(v1, 0x78);
    B(a0, 0x64) = B(v1, 0x7C);
    W(a0, 0x68) = W(v1, 0x4AC);
}
