#include "common.h"

s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_001513D0(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);

void func_00157718(s32 arg0, void *arg1, s32 *arg2) {
    s32 off;
    s32 i;
    s32 k;
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s4;
    s32 s7;
    s32 ret;

    i = 0;
    s1 = *(s32 *)((u8 *)arg1 + 0x38);
    s7 = *(s32 *)(s1 + 0xA0);
    off = 0;
    do {
        s4 = *arg2 + off;
        k = 0;
        if (*(u8 *)s4 != 0) {
            s2 = s4 + 0x10;
            do {
                if (((*(u8 *)(s2 + 1) != 2) || (((*(u8 *)s2 + 0xFF) & 0xFF) >= 2)) &&
                    (!(*(s32 *)s1 & 0x100) || (*(u8 *)(s2 + 1) != 4))) {
                    s0 = s1 + 0xA4;
                    ret = func_0014EFA8(arg0, (s32)arg2, s0, i, k, *(s32 *)s1 & 1, *(s32 *)s1 & 4);
                    if (ret != 0) {
                        func_001513D0(*(f32 *)(s1 + 0x1C), s7, (s32)arg2, s0, s1 + 0x850, s1 + 0x70,
                                      s1 + 0x20, i, k, k, ret);
                    }
                }
                k += 1;
                s2 += 0x20;
            } while (k < *(u8 *)s4);
        }
        i += 1;
        off += 0x110;
    } while (i < 0x10);
}
