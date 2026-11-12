#include "common.h"

void EftMod1CC_SetTex(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 EftMod1CC_Update[] __attribute__((section(".data")));

s32 func_001CCC68(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_t0;

    if (arg0 != NULL) {
        if (**(s32 **)((u8 *)arg0 + 0x28) == 0x001CC770 /* PS2 address of (void *)0x001CC770u */) {
            temp_t0 = *(void **)((u8 *)arg0 + 0x38);
            if (*(s32 *)((u8 *)temp_t0 + 0x40) & 1) {
                EftMod1CC_SetTex(temp_t0, arg1, arg2, arg3);
                return 1;
            }
        }
    }
    return 0;
}
