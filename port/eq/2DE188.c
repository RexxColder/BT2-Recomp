#include "common.h"

void func_002DDD70(s32 arg0, s32 arg1);
s32 func_002E0750(s32 arg0);

void func_002DE188(u8 *arg0, s32 *arg1) {
    if (func_002E0750((s32)arg0) != 0) {
        func_002DDD70(0, (s32)0xFF03020DU);
        return;
    }
    *arg1 = *(s32 *)(arg0 + 0x2A8);
}
