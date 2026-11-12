#include "common.h"

s32 func_002DCFE8(s32 arg0, s32 arg1, s32 arg2);
void func_002DDD70();
s32 func_002E0750(); /* GUESS arity: a0..a2 pass through (no write before the call) */

void func_002DDEA8(s32 arg0, u8 *arg1, s32 *arg2) {
    s32 var_a1;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v0;

    if (func_002E0750(arg0, arg1, arg2) != 0) {
        func_002DDD70(0, 0xFF03020A, 0xCC);
        return;
    }
    temp_s1 = *(s32 *)(arg1 + 4);
    temp_s0 = *(s32 *)(arg1 + 0);
    temp_v0 = func_002DCFE8(temp_s0, temp_s1, 0xCC);
    var_a1 = 0xFF030305;
    if (temp_v0 == 0) {
        *arg2 = temp_s1;
    } else {
        *arg2 = temp_v0 - temp_s0;
        var_a1 = 0;
    }
    func_002DDD70(arg0, var_a1);
}
