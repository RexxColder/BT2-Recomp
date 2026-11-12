#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C3210(s32 arg0);
u8 *func_002CAB18(s32 arg0, s32 arg1);

void func_002CAA70(u8 *arg0, s32 arg1) {
    s32 temp_v0_2;
    u8 *temp_v0;

    if (func_002C3210((s32)arg0) != 0) {
        func_002C2FF0(0, 0xFF000189, 0);
        return;
    }
    temp_v0 = func_002CAB18((s32)arg0, arg1);
    if (temp_v0 == NULL) {
        func_002C2FF0((s32)arg0, 0xFF000F31, 0);
    } else {
        temp_v0_2 = *(s32 *)(temp_v0 + 4) - 1;
        *(s32 *)(temp_v0 + 4) = (temp_v0_2 < 0) ? 0 : temp_v0_2;
    }
    *(s32 *)(arg0 + 0x980) = *(s32 *)(arg0 + 0x980) - 1;
}
