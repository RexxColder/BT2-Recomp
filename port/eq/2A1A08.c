#include "common.h"

u32 Font_MeasureLine(s32 arg0, s32 arg1);

s32 func_002A1A08(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v1;
    u32 temp_v0;
    s32 half;

    temp_v1 = *(s32 *)(arg0 + 0x38);
    if (temp_v1 == 1) {
        temp_v0 = Font_MeasureLine(arg0, arg2);
        half = (s32)((temp_v0 >> 31) + temp_v0) >> 1;
        return arg1 - half;
    }
    if (temp_v1 == 2) {
        temp_v0 = Font_MeasureLine(arg0, arg2);
        return arg1 - (s32)temp_v0;
    }
    return arg1;
}
