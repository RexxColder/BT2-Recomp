#include "common.h"

s32 func_002C67D0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002DCE50(s32 arg0);

s32 func_002C6520(s32 arg0, s32 arg1, u32 arg2) {
    s32 sp[4];
    s32 sp10;
    u32 temp_a0;
    u32 temp_v0;
    u32 temp_v0_2;
    s32 temp_s0;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 var_a1;
    s32 copied;

    sp10 = arg1;
    if (arg2 == 0) {
        return 1;
    }
    temp_a0 = *(u32 *)((u8 *)arg0 + 0);
    if (arg2 == temp_a0) {
        return 1;
    }
    copied = 0;
    if (temp_a0 < arg2) {
        if ((s32)(arg2 - temp_a0) < 4) {
            return 1;
        }
        temp_v0 = temp_a0 + *(u32 *)((u8 *)arg0 + 4);
        if (arg2 < temp_v0) {
            temp_s0 = (s32)(arg2 - temp_v0) + 4;
            if (temp_s0 > 0) {
                if (*(s32 *)((u8 *)arg0 + 0xC) < temp_s0) {
                    return 1;
                }
                memcpy(sp, (void *)arg2, 4 - temp_s0);
                memcpy((u8 *)sp - temp_s0 + 4, (void *)*(u32 *)((u8 *)arg0 + 8), temp_s0);
            } else {
                memcpy(sp, (void *)arg2, 4);
            }
            copied = 1;
        }
    }
    if (!copied) {
        if (arg2 < *(u32 *)((u8 *)arg0 + 8)) {
            return 1;
        }
        temp_v0_2 = *(u32 *)((u8 *)arg0 + 8) + *(s32 *)((u8 *)arg0 + 0xC);
        if (!(arg2 < temp_v0_2)) {
            return 1;
        }
        temp_s0 = (s32)(arg2 - temp_v0_2) + 4;
        if (temp_s0 > 0) {
            return 1;
        }
        memcpy(sp, (void *)arg2, 4);
    }
    temp_v0_3 = func_002DCE50((s32)sp);
    if (temp_v0_3 == 8) {
        if (sp10 & 0x40) {
            var_a1 = 8;
            goto block_32;
        }
        return 0;
    }
    if (temp_v0_3 < 9) {
        if (temp_v0_3 != 4) {
            return 1;
        }
        if (sp10 & 0x48) {
            var_a1 = 4;
            goto block_32;
        }
        return 0;
    }
    if (temp_v0_3 == 0x40) {
        return 0;
    }
    if (temp_v0_3 == 0x80) {
        return 0;
    }
    return 1;
block_32:
    temp_v0_4 = func_002C67D0(arg0, var_a1, (s32)&sp10);
    if (temp_v0_4 == 0) {
        return 1;
    }
    if (temp_v0_4 == arg2) {
        return 1;
    }
    return 0;
}
