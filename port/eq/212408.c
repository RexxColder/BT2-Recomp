#include "common.h"

s32 func_002413C0(u8 *obj, s32 idx, s32 flag);
s32 func_002412A0(u8 *obj, s32 idx, s32 flag);
s32 func_00211310(u8 *obj, s32 a1, s32 a2);
u32 func_002411E0(u8 *obj, s32 idx);
f32 func_00241B20(u8 *obj, s32 idx);

/* 0x00212408: computes a modified damage/strength value: base from 2413C0/2412A0 (by `alt`), -40% or +20% by state
 * flags, scaled by obj+0xAC4 when bit 0x40000 is set, then by obj+0xA30 * (241B20 - 1). */
s32 func_00212408(u8 *obj, s32 idx, u8 alt, u8 flag) {
    s32 val;
    f32 m;
    f32 base;

    if (alt != 0) {
        val = func_002413C0(obj, idx, flag);
    } else {
        val = func_002412A0(obj, idx, flag);
    }
    if (func_00211310(obj, 7, 0x20000) != 0) {
        val = val - (val * 4) / 10;
    } else if (func_00211310(obj, 0, 0x800) != 0 && idx != 4) {
        val = val + val / 5;
    }
    if ((func_002411E0(obj, idx) & 0x40000) != 0) {
        m = *(f32 *)(obj + 0xAC4);
        if (0.0f < m) {
            val = (s32)((f32)val * ((m - 1.0f) * 0.5f + 1.0f));
        }
    }
    base = (f32)val;
    return (s32)(base + base * (*(f32 *)(obj + 0xA30) * (func_00241B20(obj, idx) - 1.0f)));
}
