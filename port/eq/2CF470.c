#include "common.h"

void func_002CF4E8(u8 *arg0, u32 arg1, s64 *arg2, s32 arg3);

s32 func_002CF470(u8 *arg0, s32 arg1, u32 arg2, s64 *arg3) {
    u8 *e = arg0 + 0x1310 + arg1 * 0x74;
    s32 a3;
    s32 t0;
    u32 a1;

    *arg3 = -1;
    t0 = *(s32 *)(e + 0x1C);
    a3 = *(s32 *)(e + 0x18);
    if (*(s32 *)(e + 0x38) != 0) {
        if (arg2 < (u32)(a3 + t0)) {
            a1 = arg2;
        } else {
            a1 = arg2 - t0;
        }
        func_002CF4E8(e + 0x38, a1, arg3, a3);
    }
    return 0;
}
