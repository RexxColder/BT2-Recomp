#include "common.h"

s32 func_0026CA00(s32 arg0, s32 arg1);
void func_0026C9F0(s32 arg0, s32 arg1);

s32 func_0026CB18(s32 arg0, u32 arg1) {
    s32 s1;
    s32 s2;
    s32 p;
    s8 b0;
    s8 b1;
    u16 w;
    u32 i;

    s1 = 0;
    s2 = func_0026CA00(arg0, 2);
    func_0026C9F0(arg0, 2);
    i = 0;
    if (arg1 != 0) {
        do {
            p = s2 + s1;
            b0 = *(s8 *)p;
            b1 = *(s8 *)(p + 1);
            s1 += 2;
            w = (u16)((u8)b0 | ((u8)b1 << 8));
            i += 1;
            s1 += w;
        } while (i < arg1);
    }
    return s2 + s1;
}
