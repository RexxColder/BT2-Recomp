#include "common.h"

s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_001513D0(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);

void func_00156A60(s32 arg0, void *arg1, s32 *arg2) {
    u8 *s0;
    u8 *s2;
    u8 *s5;
    s32 s6;
    s32 s4;
    s32 fp;
    s32 s1;
    s32 flags;
    s32 r;

    s4 = 0;
    fp = 0;
    s0 = *(u8 **)((u8 *)arg1 + 0x38);
    s6 = *(s32 *)(s0 + 0xB0);
    do {
        s5 = (u8 *)(*arg2 + fp);
        s1 = 0;
        if (*s5 != 0) {
            s2 = s0 + 0xB4;
            do {
                flags = *(s32 *)s0;
                r = func_0014EFA8(arg0, (s32)arg2, (s32)s2, s4, s1, flags & 1, flags & 4);
                if (r != 0) {
                    func_001513D0(*(f32 *)(s0 + 0x1C), s6, (s32)arg2, (s32)s2, (s32)(s0 + 0x860), (s32)(s0 + 0x80), (s32)(s0 + 0x30), s4, s1, s1, r);
                }
                s1 += 1;
            } while (s1 < (s32)*s5);
        }
        s4 += 1;
        fp += 0x110;
    } while (s4 < 0x10);
}
