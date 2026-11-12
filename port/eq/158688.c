#include "common.h"

extern s32 D_0036E210[];

s32 EftShot_HasTwoAttrs(u8 *arg0, u64 arg1);
s32 EftShot_GetAttrPair(u8 *arg0, u64 arg1, s32 *arg2, s32 *arg3);
s32 EftShot_GetAttrKind(u8 *arg0, u64 arg1);
s32 func_00208DE8(u8 *a0, u8 *a1, s32 a2);
void func_00129C28(u8 *arg0, u8 *arg1);

/* Per-attribute pass over the 6 records at st + 64*t (t = 0..5): records 0 and 1 take attribute
 * bits from the attr table; record 1 also handles flag 4; later records call 208DE8 when set.
 * Returns 0x1000 when the early-out flag is set on entry, else 0 (the stale v0 of the loop exit). */
s32 func_00158688(u8 *arg0, u8 *arg1, s32 arg2, u8 *arg3) {
    u8 *st = arg1;
    s32 mask = arg2;
    s32 t;
    s32 bit;
    s32 bit2;

    if ((mask & 0x80) != 0) {
        *(s32 *)st |= 0x1000;
    }
    if ((*(s32 *)st & 0x1000) != 0) {
        return 0x1000;
    }

    for (t = 0; t < 6; t++) {
        bit = 1 << (2 * t);
        if ((*(s32 *)st & bit) == 0) {
            if ((mask & D_0036E210[t]) != 0) {
                *(s32 *)st |= bit;
                if (EftShot_HasTwoAttrs(arg0, D_0036E210[t]) != 0) {
                    *(s32 *)st |= 1 << (2 * t + 1);
                    EftShot_GetAttrPair(arg0, D_0036E210[t], (s32 *)(st + 64 * t + 0x10),
                                        (s32 *)(st + 64 * t + 0x30));
                } else {
                    *(s32 *)(st + 64 * t + 0x10) = EftShot_GetAttrKind(arg0, D_0036E210[t]);
                }
            }
        }

        if (t == 1) {
            if ((mask & 4) != 0) {
                *(s32 *)st |= 4;
                *(s32 *)(st + 0x50) = 54;
            }
            if ((*(s32 *)st & 4) != 0) {
                func_00129C28(st + 0x60, arg3);
            }
            continue;
        }

        if ((*(s32 *)st & bit) != 0) {
            func_00208DE8(arg0, st + 64 * t + 0x20, *(s32 *)(st + 64 * t + 0x10));
        } else if ((*(s32 *)st & 1) != 0) {
            func_00208DE8(arg0, st + 64 * t + 0x20, *(s32 *)(st + 0x10));
        }

        bit2 = 1 << (2 * t + 1);
        if ((*(s32 *)st & bit2) != 0) {
            func_00208DE8(arg0, st + 64 * t + 0x40, *(s32 *)(st + 64 * t + 0x30));
        } else if ((*(s32 *)st & 1) != 0) {
            func_00208DE8(arg0, st + 64 * t + 0x40, *(s32 *)(st + 0x10));
        }
    }
    return 0;
}
