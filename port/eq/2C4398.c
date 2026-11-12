#include "common.h"

void func_002C00F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002C4470(s32 arg0, s32 arg1, s32 arg2);

s32 func_002C4398(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];
    s32 v0;
    s32 v1;
    s32 s1;

    v0 = 1;
    v1 = *(s32 *)(arg0 + 0x1F90);
    if (v1 != 8) {
        func_002C00F0((s32)arg0, v1, arg1, (s32)sp, 8);
        v0 = 1;
        if (sp[0] != 0) {
            s1 = func_002C4470(sp[0], arg2, arg3);
            if (s1 == 1) {
                if (sp[1] != 0) {
                    ((void (*)(s32, s32))sp[1])((s32)arg0, arg1);
                }
                if (sp[2] != 0) {
                    ((void (*)(s32, s32))sp[2])(sp[3], arg1);
                }
            }
            v0 = s1;
        }
    }
    return v0;
}
