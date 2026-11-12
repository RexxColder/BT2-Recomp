#include "common.h"

#define FLD(p, off) (*(s32 *)((u8 *)(p) + (off)))

void func_002D0E48(u8 *arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_t1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;

    temp_a2 = FLD(arg0, 0x294);
    if (temp_a2 == -5) {
        FLD(arg0, 0x294) = arg1;
        return;
    }
    temp_a3 = arg1 - temp_a2;
    if (temp_a3 != 0) {
        temp_v1 = FLD(arg0, 0x29C);
        temp_v0 = FLD(arg0, 0x2A0);
        temp_t1 = FLD(arg0, 0x298);
        FLD(arg0, 0x294) = arg1;
        FLD(arg0, 0x29C) = (temp_a3 >= temp_v1) ? temp_a3 : temp_v1;
        FLD(arg0, 0x2A0) = (temp_v0 >= temp_a3) ? temp_a3 : temp_v0;
        if ((temp_t1 != 0x7FFFFFFF) && (temp_a3 < temp_t1)) {
            temp_v0_2 = temp_t1 - temp_a3;
            temp_v0_3 = ((temp_v0_2 < 0) ? (temp_v0_2 + 7) : temp_v0_2) >> 3;
            if (temp_v0_3 != 0) {
                FLD(arg0, 0x298) = temp_t1 - temp_v0_3;
                return;
            }
        }
        FLD(arg0, 0x298) = temp_a3;
    }
}
