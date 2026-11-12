#include "common.h"

s32 func_002E0750(s32 arg0, s32 arg1, s32 arg2);
void func_002DDD70(s32 arg0, s32 arg1);

void func_002DE2B0(s32 arg0, s32 *arg1, s32 *arg2) {
    if (func_002E0750(arg0, (s32)arg1, (s32)arg2) != 0) {
        func_002DDD70(0, 0xFF03020E);
        return;
    }
    *arg1 = *(s32 *)(arg0 + 0x2B4);
    *arg2 = *(s32 *)(arg0 + 0x2B8);
}
