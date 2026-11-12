#include "common.h"

void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_001513D0(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6,
                   s32 arg7, s32 arg8, s32 arg9);

void func_001A0CA8(s32 arg0, void *arg1) {
    f32 sp10[4];
    s32 sp20;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 s5;
    s32 s6;
    s32 s7;
    s32 ret;
    s32 t4;
    s32 v0;

    s6 = 0;
    s1 = *(s32 *)((u8 *)arg1 + 0x38);
    s7 = *(s32 *)(s1 + 0x30);
    sp20 = 0;
    s5 = *(s32 *)(s1 + 0x34);
    Vec3_Add((s32)sp10, s1 + 0x10, s1 + 0x60);
    sp10[3] = 1.0f;
    do {
        s3 = *(s32 *)s5 + sp20;
        s2 = 0;
        if (*(u8 *)s3 != 0) {
            s4 = s3 + 0x17;
            v0 = *(u8 *)s4;
            do {
                s4 += 0x20;
                if (v0 & 4) {
                    s0 = s1 + 0x70;
                    ret = func_0014EFA8(arg0, s5, s0, s6, s2, *(s32 *)(s1 + 0x40) & 2, 0);
                    t4 = ((*(s32 *)(s1 + 0x40) & 4) == 0) ? ret : 2;
                    if (t4 != 0) {
                        func_001513D0(*(f32 *)(s1 + 0x48), s7, s5, s0, s1 + 0x820, (s32)sp10,
                                      s1 + 0x20, s6, s2, s2, t4);
                    }
                }
                s2 += 1;
                v0 = *(u8 *)s4;
            } while (s2 < *(u8 *)s3);
        }
        s6 += 1;
        sp20 += 0x110;
    } while (s6 < 0x10);
}
