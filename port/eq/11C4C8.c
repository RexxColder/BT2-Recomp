#include "common.h"

void func_00210000(s32 arg0, s32 arg1);
s32 rand(void);

void func_0011C4C8(s32 arg0) {
    s32 temp_a1;
    s32 var_a1;
    s32 temp_a2;
    s32 temp_v1;

    temp_v1 = *(s32 *)((u8 *)arg0 + 0xC);
    if (temp_v1 == 0) {
        temp_a1 = ((rand() & 2) == 0) ? 0x11 : 0x1B;
        temp_a2 = *(s32 *)((u8 *)arg0 + 0x50);
        if (temp_a2 & 0x200) {
            var_a1 = ((rand() & 2) == 0) ? 0xD : 0xC;
        } else {
            var_a1 = (temp_a2 & 0x400) ? 0x42 : temp_a1;
        }
        func_00210000(arg0 + 0x20, var_a1);
        return;
    }
    if (temp_v1 == 1) {
        func_00210000(arg0 + 0x20, ((rand() & 2) == 0) ? 0x11 : 0x1B);
        return;
    }
}
