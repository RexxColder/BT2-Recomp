#include "common.h"

void func_00129C38(void *arg0, void *arg1, void *arg2);
extern s32 func_00194948[] __attribute__((section(".data")));

s32 func_00194E70(void *arg0, void *arg1) {
    void *temp_a2;

    if (arg0 != NULL && *(s32 *)(*(u8 **)((u8 *)arg0 + 0x28)) == (s32)0x00194948 /* class record's first word vs the PS2 address (missing deref + PC address, class 1) */) {
        temp_a2 = *(void **)((u8 *)arg0 + 0x38);
        if (*(s32 *)((u8 *)temp_a2 + 0x60) & 1) {
            func_00129C38((u8 *)temp_a2 + 0x20, arg1, temp_a2);
            return 1;
        }
    }
    return 0;
}
