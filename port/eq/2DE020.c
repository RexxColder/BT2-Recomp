#include "common.h"

/* GUESS arity: the asm sets a0..a2 before these tail/jal calls; ctx.h says fewer */
void func_002DDD70(s32 arg0, s32 arg1, s32 arg2);
s32 func_002E0750(s32 arg0);
void func_002E0A38(s32 arg0, s32 arg1, s32 arg2);

void func_002DE020(s32 arg0) {
    if (func_002E0750(arg0) != 0) {
        func_002DDD70(0, 0xFF030211, 2);
        return;
    }
    *(s32 *)((u8 *)arg0 + 0x408) = 1;
    if (*(s32 *)((u8 *)arg0 + 0x35C) == 2) {
        func_002E0A38(arg0, 0xFF030211, 2);
    }
}
