#include "common.h"

s32 func_0026C9F0(s32 arg0, s32 arg1);
s32 func_0026CA00(s32 arg0, s32 arg1);

s32 func_0026CBB0(s32 arg0, u32 arg1) {
    u16 sp2;
    u8 *s2;
    s32 s1;
    u32 a1;
    u8 *v0;

    s1 = 0;
    s2 = (u8 *)func_0026CA00(arg0, 3);
    func_0026C9F0(arg0, 3);
    a1 = 0;
    if (arg1 != 0) {
        do {
            do {
                v0 = s2 + s1;
                s1 += 1;
            } while (*v0 != 0);
            v0 = s2 + s1;
            s1 += 2;
            ((s8 *)&sp2)[0] = (s8)v0[0];
            a1 += 1;
            ((s8 *)&sp2)[1] = (s8)v0[1];
            s1 = s1 + sp2;
        } while (a1 < arg1);
    }
    return (s32)(s2 + s1);
}
