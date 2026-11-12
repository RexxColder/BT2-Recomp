#include "common.h"

u8 *func_0028BAA8(s32 arg0);
s32 func_00100D58(s32 arg0, s32 arg1, s32 arg2);
u8 *func_002B24C8(u8 *arg0, u8 *arg1, s32 *arg2);
void func_0026E7F0(u8 *arg0, u8 *arg1, u8 *arg2);
void func_0026EAE0(u8 *arg0, s32 arg1);
void func_00253E50(s32 arg0);
void func_00253BE8(void);
void func_00253C88(void);
void func_002541B0(void);
void func_00254138(s32 arg0);
s32 func_00101438(s32 arg0);
u8 *func_002AD4E0(void);
u8 *func_002AD588(void);
s32 func_002AD540(void);
u8 *func_002AD630(void);
s32 func_002AD5E8(void);
void Res_RelocateOffsets(u8 **arg0, u8 *arg1, u8 *arg2);
extern u8 *D_003879D0;
extern u8 *D_003876A4;

/* start of the section whose (word-aligned) byte offset is stored at hdr+off */
#define sec(hdr, off) ((hdr) + (*(u32 *)((hdr) + (off)) >> 2 << 2))

s32 func_002542F0(void) {
    u8 *t = 0;
    u8 *g;
    s32 i;
    s32 v;

    g = func_0028BAA8(0x2AC);
    D_003879D0 = g;
    __builtin_memset(g, 0, 0x2AC);
    if (*(s32 *)(D_003879D0 + 0) == 0) {
        func_00100D58(*(s32 *)(D_003876A4 + 4) + 0x11, 0, 1);
        do {
            v = func_00100D58(0, 0, 0);
            *(s32 *)(D_003879D0 + 0) = v;
        } while (v == 0);
    }
    *(u8 **)(D_003879D0 + 4) = func_002B24C8(*(u8 **)(D_003879D0 + 0), 0, 0);

    t = sec(*(u8 **)(D_003879D0 + 4), 0x30);
    Res_RelocateOffsets(&t, t, t);
    *(u8 **)(D_003879D0 + 0x78) = t;

    t = sec(*(u8 **)(D_003879D0 + 4), 0x44);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0x80) = *(s32 *)(t + 0x10);
    *(s32 *)(D_003879D0 + 0x7C) = *(s32 *)(t + 0x10) + 0x40;

    t = sec(*(u8 **)(D_003879D0 + 4), 0x40);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0x84) = *(s32 *)(t + 0x10);

    t = sec(*(u8 **)(D_003879D0 + 4), 0x34);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0xC8) = *(s32 *)(t + 0x10);

    t = sec(*(u8 **)(D_003879D0 + 4), 0x10);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0x88) = *(s32 *)(t + 0x10);

    t = sec(*(u8 **)(D_003879D0 + 4), 0x28);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0x8C) = *(s32 *)(t + 0x10);
    *(s32 *)(D_003879D0 + 0x90) = *(s32 *)(t + 0x10) + 0x40;

    t = sec(*(u8 **)(D_003879D0 + 4), 0x24);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0x9C) = *(s32 *)(t + 0x10);

    t = sec(*(u8 **)(D_003879D0 + 4), 0xC);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0xB0) = *(s32 *)(t + 0x10);
    *(s32 *)(D_003879D0 + 0xD0) = *(s32 *)(t + 0x10) + 0x40;

    t = sec(*(u8 **)(D_003879D0 + 4), 0x8);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0xCC) = *(s32 *)(t + 0x10);

    t = sec(*(u8 **)(D_003879D0 + 4), 0x2C);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0xE8) = *(s32 *)(t + 0x10);

    t = sec(*(u8 **)(D_003879D0 + 4), 0x14);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0xEC) = *(s32 *)(t + 0x10);

    t = sec(*(u8 **)(D_003879D0 + 4), 0x20);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0xF0) = *(s32 *)(t + 0x10);

    t = sec(*(u8 **)(D_003879D0 + 4), 0x18);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0xF8) = *(s32 *)(t + 0x10);

    t = sec(*(u8 **)(D_003879D0 + 4), 0x1C);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0xF4) = *(s32 *)(t + 0x10);
    *(s32 *)(D_003879D0 + 0xFC) = *(s32 *)(t + 0x10);

    t = sec(*(u8 **)(D_003879D0 + 4), 0x6C);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0x100) = *(s32 *)(t + 0x10);

    func_0026E7F0(D_003879D0 + 0x28, sec(*(u8 **)(D_003879D0 + 4), 4), D_003879D0 + 0x7C);
    func_0026EAE0(D_003879D0 + 0x28, 0x3C);

    t = sec(*(u8 **)(D_003879D0 + 4), 0x60);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0x114) = *(s32 *)(t + 0x10);
    *(s32 *)(D_003879D0 + 0x10C) = *(s32 *)(t + 0x10) + 0x40;

    t = sec(*(u8 **)(D_003879D0 + 4), 0x58);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0x110) = *(s32 *)(t + 0x10);

    t = sec(*(u8 **)(D_003879D0 + 4), 0x54);
    Res_RelocateOffsets(&t, t, t);
    *(s32 *)(D_003879D0 + 0x138) = *(s32 *)(t + 0x10);

    func_0026E7F0(D_003879D0 + 0x50, sec(*(u8 **)(D_003879D0 + 4), 0x5C), D_003879D0 + 0x10C);

    *(u8 **)(D_003879D0 + 0x284) = sec(*(u8 **)(D_003879D0 + 4), 0x48) + 4;
    *(s32 *)(D_003879D0 + 0x280) = *(s32 *)sec(*(u8 **)(D_003879D0 + 4), 0x48);

    *(u8 **)(D_003879D0 + 0x18) = func_002B24C8(sec(*(u8 **)(D_003879D0 + 4), 0x3C), 0, 0);

    i = 0;
    do {
        u8 *tab = *(u8 **)(D_003879D0 + 0x18);
        u8 *ent = tab + i * 4;
        i++;
        t = tab + (*(u32 *)(ent + 4) >> 2 << 2);
        Res_RelocateOffsets(&t, t, t);
    } while (i < 0x86);

    i = 0;
    *(u8 **)(D_003879D0 + 0x1C) = sec(*(u8 **)(D_003879D0 + 4), 0x4C);
    *(u8 **)(D_003879D0 + 0x20) = sec(*(u8 **)(D_003879D0 + 4), 0x50);
    *(u8 **)(D_003879D0 + 0x24) = sec(*(u8 **)(D_003879D0 + 4), 0x70);
    *(u8 **)(D_003879D0 + 0x288) = sec(*(u8 **)(D_003879D0 + 4), 0x64) + 4;
    *(u8 **)(D_003879D0 + 0x28C) = sec(*(u8 **)(D_003879D0 + 4), 0x68) + 4;
    *(u8 **)(D_003879D0 + 0x290) = sec(*(u8 **)(D_003879D0 + 4), 0x38);

    *(u8 **)(D_003879D0 + 8) = func_0028BAA8(0x17800);
    *(u8 **)(D_003879D0 + 0xC) = func_0028BAA8(0x17800);
    *(u8 **)(D_003879D0 + 0x10) = func_0028BAA8(0x20560);
    *(u8 **)(D_003879D0 + 0x14) = func_0028BAA8(0x20560);
    *(s32 *)(D_003879D0 + 0x294) = 4;
    *(u32 *)(D_003879D0 + 0x15C) = *(u32 *)(D_003879D0 + 0x15C) | 8;
    *(u8 **)(D_003879D0 + 0x2A4) = func_002AD4E0();
    *(u8 **)(D_003879D0 + 0x2A8) = func_002AD588();
    *(s32 *)(D_003879D0 + 0x19C) = func_002AD540();
    {
        u8 *p = func_002AD630();
        *(s32 *)(D_003879D0 + 0x268) = *(s32 *)(p + 0x10);
    }
    *(s32 *)(D_003879D0 + 0x26C) = func_002AD5E8();

    do {
        func_00253E50(i);
        i++;
    } while (i < 5);
    *(s32 *)(D_003879D0 + 0x274) = 0;
    if (*(s32 *)(D_003879D0 + 0x19C) > 0) {
        s32 off = 0x170;
        i = 0;
        do {
            u8 *src = *(u8 **)(D_003879D0 + 0x2A4) + i * 16;
            i++;
            *(s32 *)(D_003879D0 + off + 4) = *(s32 *)(src + 8);
            *(s32 *)(D_003879D0 + off + 8) = *(s32 *)(*(u8 **)(D_003879D0 + 0x2A4) + (i - 1) * 16 + 8);
            off += 8;
        } while (i < *(s32 *)(D_003879D0 + 0x19C));
    }
    func_00253BE8();
    func_00253C88();
    if (*(s32 *)(D_003879D0 + 0x19C) == 1) {
        func_002541B0();
        func_00254138(0);
        *(s32 *)(D_003879D0 + 0x270) = *(s32 *)(D_003879D0 + 0x270) + 1;
    }
    return func_00101438(0x3E25);
}
