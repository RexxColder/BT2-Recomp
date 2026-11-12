#include "common.h"

s32 func_0011E1C8(s32 arg0);
void func_001231A0(s32 arg0, s32 arg1);
s32 func_001232F0(s32 arg0);
void func_00123380(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0);
s32 func_00123478(s32 arg0);
f32 func_001234B8(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
void func_00123530(s32 arg0, s32 arg1);
s32 func_002745F8(s32 arg0);
void ColSeg_Set(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_003876FC;

s32 func_00123D58(s32 arg0) {
    u8 sp[0x20];
    u8 *a = (u8 *)arg0;
    u8 *s0 = a + 0x160;
    u8 *s5 = *(u8 **)(D_003876FC + 0x10);
    u8 *s6, *s7;
    s32 s1, s2, s3, v, cnt, a1, flags;
    f32 f12, f0;
    u8 *sub;
    s32 slot;

    if (*(s32 *)(s0 + 0x34) == 0) return 0;
    switch (*(u32 *)(s0 + 0x30)) {
    case 0:
        func_001231A0(arg0, (s32)s0);
        *(s32 *)(s0 + 0x38) = 0;
        *(s32 *)(s0 + 0x20) = -1;
        *(s32 *)(s0 + 0x30) += 1;
        /* fallthrough */
    case 1:
        sub = s0;
        slot = 0x20;
        goto srch;
    case 2:
        func_001231A0(arg0, (s32)(s0 + 0x10));
        *(s32 *)(s0 + 0x38) = 0;
        *(s32 *)(s0 + 0x24) = -1;
        *(s32 *)(s0 + 0x30) += 1;
        /* fallthrough */
    case 3:
        sub = s0 + 0x10;
        slot = 0x24;
    srch:
        s3 = 0;
        while (s3 < 4) {
            s32 idx = *(s32 *)(s0 + 0x38);
            s1 = *(s32 *)(s0 + 0xC + idx * 4 + 0xA30);
            ColSeg_Set((s32)sp, (s32)sub, *(s32 *)(s5 + 0x48) + (s1 << 4));
            if (func_0011E1C8((s32)sp) == 0) {
                *(s32 *)(s0 + slot) = s1;
                break;
            }
            s3++;
            *(s32 *)(s0 + 0x38) += 1;
        }
        if (*(s32 *)(s0 + 0x38) >= 0x10) {
            *(s32 *)(s0 + slot) = *(s32 *)(s0 + 0xA3C);
        }
        v = *(s32 *)(s0 + slot);
        if (v < 0) return v;
        *(s32 *)(s0 + 0x30) += 1;
        return *(s32 *)(s0 + 0x30);
    case 4:
        func_00123380(arg0, s0[0x20], 0xFF, -1, 0.0f);
        break;
    default:
        return *(s32 *)(s0 + 0x34);
    }
    for (;;) {
        s2 = func_001232F0(arg0);
        if (s2 != 0) return s2;
        s1 = func_00123478(arg0);
        if (s1 == 0xFF) return s1 * 8;
        s7 = s0 + s1 * 8 + 0x3C;
        if (s1 == *(s32 *)(s0 + 0x24)) {
            *(s32 *)(s0 + 0x34) = 0;
            func_00123530(arg0, s1);
            return 0;
        }
        s6 = s0 + 0xC;
        s6[s1 + 0x930] |= 2;
        s3 = 0;
        cnt = *(s32 *)(s5 + 0xC);
        if (!(s2 < cnt)) continue;
        while (s3 < cnt) {
            a1 = s1 * cnt + s3;
            s2 = (*(u8 **)(s5 + 0x6C))[a1];
            if (s2 != 0xFF) {
                flags = s6[s2 + 0x930];
                if (!(flags & 1) && !(flags & 2)) {
                    s32 a0v = (s8)(*(u8 **)(s5 + 0x70))[a1];
                    f12 = *(f32 *)(s7 + 4);
                    if (a0v >= 0 && func_002745F8(a0v) == 0) {
                        cnt = *(s32 *)(s5 + 0xC);
                    } else {
                        f12 = *(f32 *)(s7 + 4);
                        f0 = func_001234B8(arg0, s1, s3, f12);
                        func_00123380(arg0, s2, s1, (s8)s3, f0);
                        cnt = *(s32 *)(s5 + 0xC);
                    }
                }
            }
            s3++;
        }
    }
}
