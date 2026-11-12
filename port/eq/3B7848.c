#include "common.h"

/* 0x003B7848: rec = *arg0 + 0xBC*arg1 (a 0xBC-byte record). Does nothing when the word at *(rec+4) has bit 2 set.
 * Otherwise: rec->u16 |= 2; then rec+0x30 (a u16 flags word) gets bits from arg2: bit 1 -> 2, else bit 2 -> 4,
 * else bit 4 -> 8 (only one of these); then bit 8 -> 0x10, else bit 0x10 -> 0x20, else bit 0x20 -> 0x40 (one of these).
 * Finally (base = rec+0x30): f32 at base+0x30 = farg1, base+0x24 = f32 at base+0x1C, base+8 = (f32)arg3,
 * base+0x28 = f32 at base+0x20, base+0x2C = farg0, s32 at base+4 = 0. */
void func_003B7848(u8 **arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1) {
    u8 *rec;
    u8 *base;
    f32 f0;
    f32 f1;
    f32 f2;

    rec = *arg0 + arg1 * 0xBC;
    if (*(s32 *)(*(u8 **)(rec + 4)) & 2) {
        return;
    }

    *(u16 *)rec = *(u16 *)rec | 2;

    base = rec + 0x30;
    if (arg2 & 1) {
        *(u16 *)base = *(u16 *)base | 2;
    } else if (arg2 & 2) {
        *(u16 *)base = *(u16 *)base | 4;
    } else if (arg2 & 4) {
        *(u16 *)base = *(u16 *)base | 8;
    }

    if (arg2 & 8) {
        *(u16 *)base = *(u16 *)base | 0x10;
    } else if (arg2 & 0x10) {
        *(u16 *)base = *(u16 *)base | 0x20;
    } else if (arg2 & 0x20) {
        *(u16 *)base = *(u16 *)base | 0x40;
    }

    f0 = (f32)arg3;
    f1 = *(f32 *)(base + 0x1C);
    f2 = *(f32 *)(base + 0x20);
    *(f32 *)(base + 0x30) = farg1;
    *(f32 *)(base + 0x24) = f1;
    *(f32 *)(base + 0x08) = f0;
    *(f32 *)(base + 0x28) = f2;
    *(f32 *)(base + 0x2C) = farg0;
    *(s32 *)(base + 0x04) = 0;
}
