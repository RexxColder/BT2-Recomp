#include "common.h"

extern s32 D_0036E960[6];

s32 EftShot_TestBits(u8 *arg0, s32 arg1);
s32 EftShot_HasTwoAttrs(u8 *arg0, u64 arg1);
s32 EftShot_GetAttrPair(u8 *arg0, u64 arg1, s32 *arg2, s32 *arg3);
s32 func_00208DE8(u8 *a0, u8 *a1, s32 a2);
void func_00129C28(void *arg0, void *arg1);


s32 func_001962A0(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 tbl[6];
    u8 *s0 = arg1;
    u8 *st;
    u8 *s5;
    u8 *s6;
    s32 t;
    s32 v8 = 0;
    s32 v20 = 1;
    s32 bit;
    s32 flags;

    __builtin_memcpy(tbl, D_0036E960, sizeof(tbl));
    st = s0;
    s5 = s0 + 0x20;
    s6 = s0 + 0x40;

    for (t = 0; t < 6; t++) {
        if (t == 3) {
            *(s32 *)s0 |= 0x40;
            func_00129C28((s0 + 0xE0), (arg2 + 0xB60));
        } else {
            bit = 1 << v8;
            if ((*(s32 *)s0 & bit) != 0) {
                func_00208DE8(arg0, s5, *(s32 *)(st + 0x10));
            } else {
                if (EftShot_TestBits(arg0, tbl[t]) != 0) {
                    *(s32 *)s0 |= bit;
                    if (EftShot_HasTwoAttrs(arg0, tbl[t]) != 0) {
                        *(s32 *)s0 |= 1 << (v8 + 1);
                        EftShot_GetAttrPair(arg0, tbl[t], (s32 *)(st + 0x10), (s32 *)(st + 0x30));
                    } else {
                        *(s32 *)(st + 0x10) = 0;
                    }
                }
                flags = *(s32 *)s0;
                if ((flags & bit) != 0) {
                    func_00208DE8(arg0, s5, *(s32 *)(st + 0x10));
                } else if ((flags & 1) != 0) {
                    func_00208DE8(arg0, s5, *(s32 *)(s0 + 0x10));
                }
            }
            flags = *(s32 *)s0;
            if ((flags & (1 << v20)) != 0) {
                func_00208DE8(arg0, s6, *(s32 *)(st + 0x30));
            } else if ((flags & 1) != 0) {
                func_00208DE8(arg0, s6, *(s32 *)(s0 + 0x10));
            }
        }
        st += 0x40;
        s5 += 0x40;
        s6 += 0x40;
        v8 += 2;
        v20 += 2;
    }
    return 0;
}
