#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define LDF(p, off) (*(f32 *)((u8 *)(p) + (off)))

void *memcpy(void *dst, const void *src, u32 n);
s32 func_001F3758(s32 arg0);
void func_0012D3A0(s32 arg0, s32 arg1, s32 arg2);
s32 func_0016F2B0(s32 arg0);
s32 func_00191600(void *arg0);
void func_00191890(s32 arg0, s32 arg1);
void func_001918F8(s32 arg0, s32 arg1);

/* 0x0016F2E8: builds a 0x30-byte request from the object at (func_001F3758(arg0)+0x38 and arg0+0x38) and its
 * fields, submits it with func_00191600, stores the handle at +0x260 of the object from func_0016F2B0 and
 * marks that object active (flag bit 0 of +0). */
void func_0016F2E8(s32 arg0) {
    u8 sp[0x60];
    s32 ret;
    s32 o;
    s32 s4;
    s32 s2;
    s32 s1;
    s32 r;

    ret = func_001F3758(arg0);
    o = LD32(arg0, 0x38);
    s4 = LD32(ret, 0x38);
    s2 = LD32(o, 0xB0);
    func_0012D3A0(o + 0x30, o + 0x70, LD32(s2, 0));
    s1 = func_0016F2B0(o);
    if (s1 == 0) {
        return;
    }

    LD32(sp, 0x38) = o + 0x860;
    LD32(sp, 0x3C) = o + 0x40;
    LD32(sp, 0x48) = 0x19;
    LD32(sp, 0x4C) = 1;
    LD32(sp, 0x30) = s2;
    LD32(sp, 0x34) = s4;
    LD32(sp, 0x40) = o + 0x30;
    LD32(sp, 0x50) = 3;
    LD32(sp, 0x44) = 0;
    LD32(sp, 0x54) = 0;
    LDF(sp, 0x58) = LDF(o, 0x1C);
    LDF(sp, 0x5C) = LDF(o, 0x14);
    memcpy(sp, sp + 0x30, 0x30);

    r = func_00191600(sp);
    LD32(s1, 0x260) = r;
    func_00191890(r, 1);
    func_001918F8(LD32(s1, 0x260), 1);
    LD32(s1, 0) = LD32(s1, 0) | 1;
}
