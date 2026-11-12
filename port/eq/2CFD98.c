#include "common.h"

s32 func_002C3210(s32 arg0);
s32 func_002C2FF0(s32 arg0, s32 arg1);
void func_002CFD28(s32 arg0, s32 arg1);
void func_002CFE38(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002CFD98(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 sp[4];

    *arg3 = 0;
    if (func_002C3210((s32)arg0) != 0) {
        return func_002C2FF0(0, 0xFF000156);
    }
    func_002CFD28(*(s32 *)(arg0 + 0x36B0), (s32)&sp[0]);
    if (sp[0] != 0) {
        func_002CFE38(*(s32 *)(arg0 + 0x36B0), arg1, arg2, (s32)arg3);
    }
    return 0;
}
