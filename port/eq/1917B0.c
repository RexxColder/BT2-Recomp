#include "common.h"

s32 func_00129C28(s32 arg0, s32 arg1);
extern u8 func_00191238[] __attribute__((section(".data")));

s32 func_001917B0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_a3;
    s32 var_v0;

    var_v0 = 0;
    if ((arg0 != 0) && (*(s32 *) (*(s32 *) (arg0 + 0x28)) == (s32)0x00191238u)) {
        temp_a3 = *(s32 *) (arg0 + 0x38);
        temp_a0 = *(s32 *) (temp_a3 + 0x30);
        if (temp_a0 & 1) {
            if (arg1 & 0xFF) {
                *(s32 *) (temp_a3 + 0x30) = temp_a0 | 0x200;
                func_00129C28(temp_a3 + 0x50, arg2);
            } else {
                *(s32 *) (temp_a3 + 0x30) = temp_a0 & ~0x200;
            }
            var_v0 = 1;
        }
    }
    return var_v0;
}
