#include "common.h"

void func_00129C38(void *arg0, void *arg1, void *arg2);
extern s32 EftMod1CC_Update[] __attribute__((section(".data")));

s32 func_001CCAC8(void *arg0, void *arg1) {
    void *temp_a2;

    if (arg0 != NULL && **(s32 **)((u8 *)arg0 + 0x28) == 0x001CC770 /* PS2 address of (void *)0x001CC770u */) {
        temp_a2 = *(void **)((u8 *)arg0 + 0x38);
        if (*(s32 *)((u8 *)temp_a2 + 0x40) & 1) {
            func_00129C38((u8 *)temp_a2 + 0x10, arg1, temp_a2);
            return 1;
        }
    }
    return 0;
}
