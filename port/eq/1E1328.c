#include "common.h"

#define F32AT(p, off) (*(f32 *)((u8 *)(p) + (off)))

void func_00312680(s32 arg0, s32 arg1, f32 farg0);
void func_001E1550(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0);
void func_001E3AC8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3, s32 s9, f32 farg0);
void func_001E65C8(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_00343258[] __attribute__((section(".data")));
extern u8 D_00343298[] __attribute__((section(".data")));
extern u8 D_00343318[] __attribute__((section(".data")));
extern u8 D_003433A8[] __attribute__((section(".data")));

void func_001E1328(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0) {
    u8 sp[0x70];
    u8 *self;
    u32 base; /* address as an integer (see 266950) */
    u8 *entry;
    s32 s4;
    s32 v;
    f32 f10;
    f32 f14;
    f32 t2;
    f32 t1;

    self = (u8 *)arg0;
    s4 = arg3 & 0xFF;
    func_001E65C8((s32)(sp + 0x10), arg2, *(u8 *)(self + 0x5C));
    f10 = F32AT(sp, 0x10);
    f14 = F32AT(sp, 0x14);
    t2 = 1.0f / f14;
    t1 = (f10 - 1.0f) / f10;

    if (*(u8 *)(self + 0x16E) != 0) {
        v = *(s32 *)(self + 0x170);
        base = 0;
        if (v == 1) {
            base = (u32)D_00343298;
        } else if (v == 0) {
            base = (u32)D_00343258;
        } else if (v == 2) {
            base = (u32)D_003433A8;
        } else if (v == 3) {
            base = (u32)D_00343318;
        }
        if (base != 0) {
            entry = (u8 *)(base + *(s32 *)(self + 0x194) * 16);
            F32AT(sp, 0x60) = F32AT(entry, 0x0);
            F32AT(sp, 0x64) = F32AT(entry, 0x4);
            F32AT(sp, 0x68) = F32AT(entry, 0x8);
            F32AT(sp, 0x6C) = F32AT(entry, 0xC);
        }
    } else {
        F32AT(sp, 0x64) = t2;
        F32AT(sp, 0x6C) = t1;
        F32AT(sp, 0x60) = t2;
        F32AT(sp, 0x68) = t1;
    }

    *(s32 *)(sp + 0x20) = 0;
    F32AT(sp, 0x2C) = 1.0f;
    *(s32 *)(sp + 0x24) = 0;
    *(s32 *)(sp + 0x28) = 0;

    if (*(u8 *)(self + 0x16B) != 0) {
        if (*(u8 *)(self + 0x16C) != 0) {
            func_001E1550((s32)self, arg1, arg2, s4, farg0);
        } else {
            F32AT(sp, 0x3C) = F32AT(sp, 0x64);
            F32AT(sp, 0x40) = F32AT(sp, 0x60);
            F32AT(sp, 0x48) = F32AT(sp, 0x68);
            F32AT(sp, 0x4C) = F32AT(sp, 0x6C);
            F32AT(sp, 0x30) = F32AT(sp, 0x60);
            F32AT(sp, 0x34) = F32AT(sp, 0x64);
            F32AT(sp, 0x38) = F32AT(sp, 0x68);
            F32AT(sp, 0x44) = F32AT(sp, 0x6C);
            func_00312680((s32)(sp + 0x50), (s32)(self + 0x30), farg0);
            func_001E3AC8((s32)(self + 0x10), (s32)(self + 0x60), (s32)(sp + 0x20), (s32)(sp + 0x50),
                          arg1, (s32)(sp + 0x30), (s32)(sp + 0x40), s4, arg2, farg0);
        }
    }
}
