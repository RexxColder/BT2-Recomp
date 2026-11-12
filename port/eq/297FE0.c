#include "common.h"

extern u8 *D_00387ED0;

void func_002976A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_00297F58(s32 arg0, s32 arg1);

void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 flag = 0;
    s32 v0;

    if ((u32)(arg0 - 3) < 2U) {
        if (arg1 < 0x25) {
            flag = 1;
        }
        v0 = func_00297F58(arg2, flag);
    } else {
        v0 = func_00297F58(arg2, 0);
    }
    if (*(s32 *)(D_00387ED0 + 0x64) != arg0) {
        func_002976A0(arg0, arg1, v0, arg3, arg4);
    }
}
