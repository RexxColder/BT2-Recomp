#include "common.h"

void func_002F9300(s32 arg0);
u8 *func_002F98F0(s32 arg0, s32 arg1, s32 arg2);
void func_002F9B38(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037D980[] __attribute__((section(".data")));
extern u8 D_0037D9D0[] __attribute__((section(".data")));
extern u8 D_0037D9F8[] __attribute__((section(".data")));

s32 func_002FAAA8(s32 arg0) {
    u8 buf[0x260];
    u8 *sp130;
    u8 *var_a0;
    u8 *temp_v0_2;
    s32 (*temp_v0)(s32);

    sp130 = buf + 0x130;
    if (arg0 == 0) {
        var_a0 = D_0037D980;
        goto block_13;
    }
    func_002F9B38((s32)buf, (s32)sp130, arg0);
    if (*(s8 *)sp130 == 0) {
        var_a0 = D_0037D980;
        goto block_13;
    }
    temp_v0_2 = func_002F98F0((s32)buf, (s32)sp130, arg0);
    if (temp_v0_2 == 0) {
        func_002F9300((s32)D_0037D9D0);
    }
    temp_v0 = (s32 (*)(s32))(*(s32 *)(temp_v0_2 + 0x58));
    if (temp_v0 == 0) {
        var_a0 = D_0037D9F8;
block_13:
        func_002F9300((s32)var_a0);
        return -1;
    }
    return temp_v0((s32)sp130);
}
