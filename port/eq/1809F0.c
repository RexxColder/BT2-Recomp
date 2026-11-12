#include "common.h"

s32 func_001267E8(s32 arg0, s32 arg1);
void func_00180A40(s32 arg0);

void func_001809F0(u8 *arg0) {
    u8 *p = (u8 *)*(s32 *)(arg0 + 0x38);
    s32 r = func_001267E8(*(s32 *)(p + 0x58), *(u8 *)(p + 0x4C));

    if (r == 0 && (*(s32 *)(p + 0x48) & 1) != 0) {
        func_00180A40((s32)p);
    }
}
