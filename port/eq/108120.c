#include "common.h"

s32 func_00106A00(s32 arg0, s32 arg1);
s32 func_00106AC0(s32 arg0, s32 arg1);

s32 func_00108120(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 a0;
    s32 addr;

    temp_v0 = func_00106A00(arg0, arg1);
    if (temp_v0 == 0) {
        return 0;
    }
    if (*(s32 *)(temp_v0 + 0x8) == 0) {
        return 0;
    }
    a0 = func_00106AC0(arg0, arg1);
    if (a0 == 0) {
        return 0;
    }
    addr = *(s32 *)(a0 + 0x0) + *(s32 *)(a0 + 0x14) * 32;
    return *(s32 *)(addr + 4) == arg1;
}
