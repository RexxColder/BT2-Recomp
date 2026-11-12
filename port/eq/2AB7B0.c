#include "common.h"

void func_002A86E8(s32 arg0, s32 arg1, s32 arg2);
void func_002AB6F8(s32 arg0);

void func_002AB7B0(u8 *arg0) {
    s32 sp[8];

    *(s32 *)(arg0 + 0x24) = 0;
    *(s32 *)(arg0 + 0x2C) = 0;
    sp[0] = 0;
    sp[1] = (s32)arg0;
    func_002A86E8((s32)sp, (s32)func_002AB6F8, 0);
}
