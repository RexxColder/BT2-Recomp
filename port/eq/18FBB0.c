#include "common.h"

void func_0018F080(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void func_0018FC58(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_003877BC;

s32 func_0018FBB0(u8 *arg0) {
    s32 var_v1;
    u8 *var_s1;

    var_v1 = 0;
    var_s1 = D_003877BC;
loop_1:
    var_v1 += 1;
    if (*(u16 *)(var_s1 + 0xFC) == 0) {
        *(u16 *)(var_s1 + 0xFC) = 1;
        func_0018F080((s32)var_s1, *(s32 *)(arg0 + 4), *(s32 *)(arg0 + 8), (s32)(arg0 + 0x20),
                      (s32)(arg0 + 0x46), *(u8 *)(arg0 + 0x4E), (s32)(arg0 + 0x4F), *(u8 *)(arg0 + 0x50),
                      (*(u16 *)(arg0 + 0x44) >> 10) & 1);
        func_0018FC58((s32)(arg0 + 0x5C), (s32)(arg0 + 0x60), (s32)var_s1);
        return 1;
    }
    var_s1 += 0x110;
    if (var_v1 >= 0x50) {
        return 0;
    }
    goto loop_1;
}
