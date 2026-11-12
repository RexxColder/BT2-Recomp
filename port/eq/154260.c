#include "common.h"

s32 func_0014EFA8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
s32 func_0014F2B8(s32 a0, s32 a1, s32 a2, s32 a3);
void func_001513D0(f32 farg0, s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 s8, s32 s9);

void func_00154260(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *s1 = *(u8 **)((u8 *)arg1 + 0x38);
    s32 flags;
    s32 fp;
    s32 sp14;
    s32 sp18;
    s32 s6;
    s32 var_s2;
    s32 v0;
    s32 v1;
    u8 *s4;
    u8 *s3;
    u8 *s7;

    s6 = 0;
    sp14 = arg3 & 0xFF;
    fp = *(s32 *)(s1 + 0xC0);
    sp18 = 0;
    do {
        s4 = *(u8 **)arg2 + sp18;
        var_s2 = 0;
        if (*s4 != 0) {
            s7 = s1 + 0xC4;
            s3 = s4 + 0x10;
            do {
                if ((s3[1] != 4) || (s3[7] & 2)) {
                    flags = *(s32 *)s1;
                    if (sp14 == 0) {
                        v0 = func_0014EFA8(arg0, arg2, (s32)s7, s6, var_s2, flags & 1, flags & 4);
                    } else {
                        v0 = func_0014F2B8(arg2, (s32)s7, s6, var_s2);
                    }
                    v1 = (flags & 0x100) ? 2 : v0;
                    if (v1 != 0) {
                        func_001513D0(*(f32 *)(s1 + 0x18), fp, arg2, (s32)s7, (s32)(s1 + 0x870),
                            (s32)(s1 + 0x90), (s32)(s1 + 0x30), s6, var_s2, var_s2, v1);
                    }
                }
                var_s2 += 1;
                s3 += 0x20;
            } while (var_s2 < (s32)*s4);
        }
        s6 += 1;
        sp18 += 0x110;
    } while (s6 < 0x10);
}
