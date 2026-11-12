#include "common.h"

void func_00129C28(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_00191238 __attribute__((section(".data")));

s32 func_00191838(u8 *arg0, s32 arg1) {
    s32 var_v0;
    u8 *temp_a2;

    var_v0 = 0;
    if (arg0 != NULL && *(s32 *)*(u8 **)(arg0 + 0x28) == (s32)0x00191238u) {
        temp_a2 = *(u8 **)(arg0 + 0x38);
        if (*(s32 *)(temp_a2 + 0x30) & 1) {
            func_00129C28((s32)(temp_a2 + 0x40), arg1, (s32)temp_a2, (s32)arg0);
            var_v0 = 1;
        }
    }
    return var_v0;
}
