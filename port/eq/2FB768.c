#include "common.h"

s32 func_00306F28(void *a0, s32 a1, s64 a2, s64 a3, s32 a4);
void func_00306FA0();

s32 func_002FB768(void *arg0, s32 arg1, s64 arg2, s64 arg3, s32 arg4) {
    s32 s4;
    s32 v1;

    s4 = 0;
    func_00306F28(arg0, arg1, arg2, arg3, arg4);
    v1 = *(s8 *)((u8 *)arg0 + 2);
    if (v1 == 0 || v1 == 3 || v1 == 9) {
        *(s32 *)((u8 *)arg0 + 0x30) = arg1;
        *(s8 *)((u8 *)arg0 + 1) = 2;
        *(s8 *)((u8 *)arg0 + 2) = 1;
        s4 = 1;
        *(s32 *)((u8 *)arg0 + 0x18) = arg4;
        *(s64 *)((u8 *)arg0 + 0x20) = arg3;
        *(s64 *)((u8 *)arg0 + 0x28) = arg2;
        *(s32 *)((u8 *)arg0 + 4) = 0;
    }
    func_00306FA0();
    return s4;
}
