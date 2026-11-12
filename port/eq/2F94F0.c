#include "common.h"

/* GUESS arity: func_002F9660 gets arg0 and arg1 passed through (both untouched before its call) */
s32 func_002F9660(s32 arg0, s32 arg1);
s32 func_002F95C8(s32 arg0);
extern u8 D_0039D938[] __attribute__((section(".data")));

s32 func_002F94F0(s32 arg0, s32 arg1) {
    s32 s0;
    s32 s2;
    s32 temp_s0;
    u8 *v1;

    func_002F9660(arg0, arg1);
    s2 = ((s32 (*)(void))arg1)();
    s0 = 0;
    if (func_002F95C8(arg0) == 0) {
        v1 = D_0039D938 + 4;
        if (*(s8 *)(D_0039D938 + 4) != 0) {
            do {
                s0 += 1;
                v1 += 0x10;
                if (s0 >= 0x20) {
                    break;
                }
            } while (*(s8 *)v1 != 0);
        }
        if (s0 == 0x20) {
            return 0;
        }
        temp_s0 = s0 * 0x10;
        *(s32 *)(D_0039D938 + temp_s0) = s2;
        memcpy((s32)(D_0039D938 + temp_s0 + 4), arg0, strlen(arg0) + 1);
        return s2;
    }
    return s2;
}
