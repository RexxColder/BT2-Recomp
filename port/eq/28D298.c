#include "common.h"

/* 0x0028D298: base = *(u8 **)D_00387D70 + (a0->+0x14 << 2);
   func_003126C8(a2, base + (a1->+4 << 4)); func_003126C8(a3, base + (a1->+8 << 4));
   tail func_003126C8(t0, base + (a1->+0xC << 4)). */
extern u8 D_00387D70[];
s32 func_003126C8(s32 arg0, s32 arg1);

s32 func_0028D298(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0) {
    u8 *base;

    base = *(u8 **)D_00387D70 + (*(s32 *)((u8 *)a0 + 0x14) << 2);
    func_003126C8(a2, (s32)(base + (*(s32 *)((u8 *)a1 + 0x4) << 4)));
    func_003126C8(a3, (s32)(base + (*(s32 *)((u8 *)a1 + 0x8) << 4)));
    return func_003126C8(t0, (s32)(base + (*(s32 *)((u8 *)a1 + 0xC) << 4)));
}
