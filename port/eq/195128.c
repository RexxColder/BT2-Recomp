#include "common.h"

void func_00191BC8(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_00194948[] __attribute__((section(".data")));

s32 func_00195128(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_t0;

    if (arg0 != NULL) {
        if (*(s32 *)(*(u8 **)((u8 *)arg0 + 0x28)) == (s32)0x00194948 /* class record's first word vs the PS2 address (missing deref + PC address, class 1) */) {
            temp_t0 = *(void **)((u8 *)arg0 + 0x38);
            if (*(s32 *)((u8 *)temp_t0 + 0x60) & 1) {
                func_00191BC8(temp_t0, arg1, arg2, arg3);
                return 1;
            }
        }
    }
    return 0;
}
