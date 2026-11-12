#include "common.h"

s32 func_00129C28(s32 arg0, s32 arg1);
extern s32 D_0038787C;
extern u8 func_001B5400[] __attribute__((section(".data")));

#ifdef __mips__
#define SHOT_IS_UPDATE(p) ((void *)(p) == (void *)func_001B5400)
#else
#define SHOT_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001B5400u)
#endif

void func_001B55C8(u8 *arg0, s32 arg1) {
    if (D_0038787C != 0 && arg0 != NULL) {
        if (SHOT_IS_UPDATE(*(void **)*(u8 **)(arg0 + 0x28)) && !(arg0[0] & 1)) {
            func_00129C28(*(s32 *)(arg0 + 0x38) + 0x40, arg1);
        }
    }
}
