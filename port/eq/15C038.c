#include "common.h"

s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_001513D0(f32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10);

void func_0015C038(s32 arg0, u8 *arg1, s32 *arg2) {
    u8 *s1;
    u8 *s4;
    s32 s6;
    s32 s3;
    s32 s2;
    s32 fp;
    s32 flags;
    s32 r;

    s3 = 0;
    fp = 0;
    s1 = *(u8 **)(arg1 + 0x38);
    s6 = *(s32 *)(s1 + 0xA0);
    do {
        s4 = (u8 *)(*arg2 + fp);
        s2 = 0;
        if (*s4 != 0) {
            do {
                if (!(s3 == 6 && s2 == 1) && s3 != 2) {
                    flags = *(s32 *)s1;
                    r = func_0014EFA8(arg0, (s32)arg2, (s32)(s1 + 0xA4), s3, s2, flags & 1, flags & 4);
                    if (r != 0) {
                        func_001513D0(*(f32 *)(s1 + 0x14), s6, (s32)arg2, (s32)(s1 + 0xA4), (s32)(s1 + 0x850),
                                      (s32)(s1 + 0x70), (s32)(s1 + 0x20), s3, s2, s2, r);
                    }
                }
                s2++;
            } while (s2 < *s4);
        }
        s3++;
        fp += 0x110;
    } while (s3 < 0x10);
}
