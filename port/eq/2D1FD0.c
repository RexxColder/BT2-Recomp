#include "common.h"

void func_002D2030(s32 arg0, s32 arg1, s32 arg2);
void func_002D2098(s32 arg0, s32 arg1, s32 arg2);
void func_002D20E8(s32 arg0, s32 arg1, s32 arg2);

void func_002D1FD0(s32 arg0, u32 arg1) {
    s32 buf[2];

    if (arg1 == 2) {
        func_002D20E8(arg0, (s32)buf, (s32)&buf[1]);
        func_002D2030(arg0, buf[0], buf[1]);
        func_002D2098(arg0, buf[0], buf[1]);
    }
}
