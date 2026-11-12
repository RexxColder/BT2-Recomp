#include "common.h"

s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 func_0014F2B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001513D0(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                   s32 arg6, s32 arg7, s32 st0, s32 st1);

void func_0014C398(s32 arg0, u8 *arg1, void *arg2, s32 arg3) {
    s32 sp14 = arg3 & 0xFF;
    s32 sp18;
    u8 *s1 = *(u8 **)(arg1 + 0x38);
    u8 *s3, *s4, *s7;
    s32 s6, sp1C, s2, v;

    sp18 = *(s32 *)(s1 + 0xB0);
    sp1C = 0;
    for (s6 = 0; s6 < 0x10; s6++, sp1C += 0x110) {
        s3 = *(u8 **)arg2 + sp1C;
        if (*s3 == 0) {
            continue;
        }
        s7 = s1 + 0xB4;
        s4 = s3 + 0x11;
        s2 = 0;
        do {
            if (*s4 != 2) {
                if (sp14 == 0) {
                    v = func_0014EFA8(arg0, (s32)arg2, (s32)s7, s6, s2,
                                      *(s32 *)s1 & 1, *(s32 *)s1 & 4);
                } else {
                    v = func_0014F2B8((s32)arg2, (s32)s7, s6, s2);
                }
                if (*(s32 *)s1 & 0x100) {
                    v = 2;
                }
                if (v != 0) {
                    func_001513D0(*(f32 *)(s1 + 0x18), sp18, (s32)arg2, (s32)s7,
                                  (s32)(s1 + 0x860), (s32)(s1 + 0x80), (s32)(s1 + 0x30),
                                  s6, s2, s2, v);
                }
            }
            s4 += 0x20;
            s2++;
        } while (s2 < *s3);
    }
}
