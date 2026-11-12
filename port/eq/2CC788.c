#include "common.h"

s32 func_002C1180(s32 arg0);
s32 func_002C11E8(s32 arg0);
void func_002CC4A8(s32 arg0, s32 arg1);
s32 func_002DCE50(s32 arg0);
s32 func_002DCFE8(s32 arg0, s32 arg1, s32 arg2);

void func_002CC788(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 sp[8];
    u8 *s1;
    u8 *s3;
    s32 s2;
    s32 s5;
    s32 a2;
    s32 a1;
    s32 a3;
    s32 t;
    s32 r;
    s32 s0;

    s2 = arg2;
    s3 = arg1;
    s5 = 0;
    a2 = 0;
    s1 = *(u8 **)(arg0 + 0x1FC0) + 0x1128;
    *(s32 *)(s1 + 0xC) = *(s32 *)(s1 + 0xC) + *(s32 *)(s1 + 0x4);
    *(s32 *)(s1 + 0x4) = *(s32 *)(s1 + 0x8);
    *(s32 *)(s1 + 0x8) = 0;
    sp[0] = s1[0x10];
    sp[1] = s1[0x11];
    sp[2] = s1[0x12];
    sp[3] = s3[0];
    sp[4] = s3[1];
    sp[5] = s3[2];
    a3 = (s2 < 4);

    while (a2 < ((a3 != 0) ? s2 : 3)) {
        a1 = a2 + 1;
        if (sp[a2] == 0 && sp[a2 + 1] == 0 && sp[a2 + 2] == 1) {
            t = sp[a2 + 3];
            if (t == 0) {
                *(s32 *)(s1 + 0x8) = *(s32 *)(s1 + 0x8) + 1;
                break;
            }
            if (t == 0xB7) {
                s5 = 1;
                break;
            }
        }
        a2 = a1;
    }

    if (s2 < 3) {
        s1[0x10] = sp[s2];
        s1[0x11] = sp[s2 + 1];
        s1[0x12] = sp[s2 + 2];
    } else {
        s1[0x10] = s3[s2 - 3];
        s1[0x11] = s3[s2 - 2];
        s1[0x12] = s3[s2 - 1];
    }

    while (a3 == 0) {
        r = func_002DCFE8((s32)s3, s2, 0x84);
        if (r == 0) {
            break;
        }
        if (!(func_002DCE50(r) & 4)) {
            s5 = 1;
        } else {
            *(s32 *)(s1 + 0x8) = *(s32 *)(s1 + 0x8) + 1;
        }
        s0 = r + 4;
        t = s0 - (s32)s3;
        s3 = (u8 *)(s32)s0;
        s2 -= t;
        a3 = (s2 < 4);
    }

    if (s5 == 1) {
        if (func_002C1180((s32)arg0) == 0) {
            if (func_002C11E8((s32)arg0) == 0) {
                func_002CC4A8((s32)arg0, 1);
            }
        }
    }
}
