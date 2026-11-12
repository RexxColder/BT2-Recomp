#include "common.h"

/* 0x002F8D38: tail call func_002E9400(a2, a1, a0 + 0x30, a0 + 0x32). */
void func_002E9400(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002F8D38(s32 a0, s32 a1, s32 a2) {
    func_002E9400(a2, a1, a0 + 0x30, a0 + 0x32);
}
