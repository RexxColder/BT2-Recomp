#include "common.h"

/* 0x00163088: per-slot update of a 6-slot attribute block (arr, 64 bytes per slot).
   tbl[i] = {2,4,8,0x10,0x20,0x40} (copied from D_0036E468). Bit 0x1000 of arr[0] set: return 0x1000 at once.
   Otherwise each slot i: fill from EftShot_* when mask has tbl[i]; then call func_00208DE8 with the slot's
   sub-block; when IsHidden, add 200.0f to the float at +0x24 / +0x44 of the slot. Returns 0. */
s32 BtlCharApi_IsHidden(s32 arg0);
s32 EftShot_HasTwoAttrs(s32 arg0, u64 arg1);
s32 EftShot_GetAttrKind(s32 arg0, u64 arg1);
s32 EftShot_GetAttrPair(s32 arg0, u64 arg1, s32 arg2, s32 arg3);
s32 func_00208DE8(s32 a0, s32 a1, s32 a2);

s32 func_00163088(s32 obj, u32 *arr, u32 mask) {
    static const u32 tbl[6] = {2, 4, 8, 0x10, 0x20, 0x40};
    s32 hidden;
    u32 flags;
    s32 i;

    hidden = BtlCharApi_IsHidden(obj);
    if (mask & 0x80) {
        arr[0] |= 0x1000;
    }
    flags = arr[0];
    if (flags & 0x1000) {
        return (s32)(flags & 0x1000);
    }

    for (i = 0; i < 6; i++) {
        u32 bit0 = 1u << (2 * i);
        u32 bit1 = 1u << (2 * i + 1);
        u8 *base = (u8 *)arr + i * 64;

        if (!(flags & bit0)) {
            if (mask & tbl[i]) {
                arr[0] = flags | bit0;
                if (EftShot_HasTwoAttrs(obj, (s32)tbl[i])) {
                    arr[0] |= bit1;
                    EftShot_GetAttrPair(obj, (s32)tbl[i], (s32)(base + 0x10), (s32)(base + 0x30));
                } else {
                    *(u32 *)(base + 0x10) = (u32)EftShot_GetAttrKind(obj, (s32)tbl[i]);
                }
            }
            flags = arr[0];
        }

        if (flags & bit0) {
            func_00208DE8(obj, (s32)(base + 0x20), (s32)*(u32 *)(base + 0x10));
            if (hidden) {
                *(f32 *)(base + 0x24) = *(f32 *)(base + 0x24) + 200.0f;
            }
        } else if (flags & 1) {
            func_00208DE8(obj, (s32)(base + 0x20), (s32)arr[4]);
            if (hidden) {
                *(f32 *)(base + 0x24) = *(f32 *)(base + 0x24) + 200.0f;
            }
        }

        flags = arr[0];
        if (flags & bit1) {
            func_00208DE8(obj, (s32)(base + 0x40), (s32)*(u32 *)(base + 0x30));
            if (hidden) {
                *(f32 *)(base + 0x44) = *(f32 *)(base + 0x44) + 200.0f;
            }
        } else if (flags & 1) {
            func_00208DE8(obj, (s32)(base + 0x40), (s32)arr[4]);
            if (hidden) {
                *(f32 *)(base + 0x44) = *(f32 *)(base + 0x44) + 200.0f;
            }
        }
        flags = arr[0];
    }
    return 0;
}
