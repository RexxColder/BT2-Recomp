#include "common.h"

s32 func_002A86E8(s32 arg0, s32 arg1, s32 arg2);
void func_00104ED0(s32 arg0);

s32 func_00104FC0(s32 arg0) {
    s32 sp[8];

    sp[0] = 0;
    sp[3] = arg0;
    sp[4] = -1;
    sp[5] = -1;
    func_002A86E8((s32)sp, (s32)func_00104ED0, 0);
    return 0;
}
