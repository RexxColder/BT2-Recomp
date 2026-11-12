#include "common.h"

void func_002CFFC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002E0A98(s32 arg0, s32 arg1, s32 arg2);

void func_002CFF38(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = *(s32 *) (arg0 + 0xDC0);
    if (temp_v0 != 0) {
        func_002CFFC0(temp_v0, arg1, arg2, arg3);
        return;
    }
    temp_v0_2 = *(s32 *) (arg0 + 0xDA8);
    if (temp_v0_2 <= 0) {
        *(s32 *) arg2 = 0;
    } else {
        *(s32 *) arg2 = func_002E0A98(arg1, 0x3E8, temp_v0_2);
    }
    *(s32 *) arg3 = 0x3E8;
}
