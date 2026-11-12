#include "common.h"

void func_00129C28(void *arg0, void *arg1);
s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_001513D0(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                   s32 arg6, s32 arg7, s32 st0, s32 st1);

void func_0015A468(s32 arg0, s32 arg1, u8 *arg2, void *arg3) {
    f32 sp10[4];
    s32 sp20 = arg0 & 0xFF;
    s32 var_s6 = 0;
    s32 sp28 = 0;
    s32 s3, r;
    u8 *s1, *fp, *s4, *s2, *s0;
    f32 f20;

    s1 = *(u8 **)(arg2 + 0x38);
    fp = *(u8 **)(s1 + 0x80);
    do {
        s4 = *(u8 **)arg3 + sp28;
        s3 = 0;
        if (s4[0] != 0) {
            s2 = s4 + 0x10;
            do {
                f20 = *(f32 *)(s1 + 0xC);
                func_00129C28(sp10, s1 + 0x50);
                if (sp20 != 0 || !(s2[7] & 4)) {
                    if (s2[0] == 2) {
                        f20 = *(f32 *)(s1 + 0x10);
                    }
                    s0 = s1 + 0x84;
                    r = func_0014EFA8(arg1, (s32)arg3, (s32)s0, var_s6, s3,
                                      *(s32 *)s1 & 1, *(s32 *)s1 & 4);
                    if (r != 0) {
                        func_001513D0(f20, (s32)fp, (s32)arg3, (s32)s0, (s32)(s1 + 0x830),
                                      (s32)sp10, (s32)(s1 + 0x20), var_s6, s3, s3, r);
                    }
                }
                s3 += 1;
                s2 += 0x20;
            } while (s3 < s4[0]);
        }
        var_s6 += 1;
        sp28 += 0x110;
    } while (var_s6 < 0x10);
}
