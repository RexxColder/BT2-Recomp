#include "common.h"

void func_002D6DE0(s32 arg0, s32 arg1, s32 arg2);
s32 func_003063E8(s32 *arg0, u8 *arg1, u8 *arg2, s32 *arg3);
extern u8 D_003798F0[] __attribute__((section(".data")));
extern u8 D_003798F8[] __attribute__((section(".data")));

void func_002BA378(u8 *arg0) {
    s32 sp[8];
    s32 temp_s0;

    temp_s0 = *(s32 *)(arg0 + 0xA8);
    if (*(s32 *)(arg0 + 0x198) == 0) {
        func_002D6DE0(temp_s0, 0, 0);
        return;
    }
    sp[0] = *(s32 *)(arg0 + 0x198);
    sp[1] = *(s32 *)(arg0 + 0x19C);
    if (func_003063E8(sp, D_003798F0, D_003798F8, &sp[4]) == 0) {
        func_002D6DE0(temp_s0, 0, 0);
        return;
    }
    func_002D6DE0(temp_s0, sp[4], sp[5]);
}
