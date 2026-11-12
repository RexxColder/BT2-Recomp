#include "common.h"

extern u8 func_001E9428[] __attribute__((section(".data")));

#ifdef __mips__
#define STEAM_IS_UPDATE(p) ((void *)(p) == (void *)func_001E9428)
#else
#define STEAM_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001E9428u)
#endif

void func_001EAF68(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 *t;

    if (arg0 == NULL) {
        return;
    }
    if (!STEAM_IS_UPDATE(*(void **)*(u8 **)(arg0 + 0x28))) {
        return;
    }
    t = *(u8 **)(arg0 + 0x38);
    if ((*(u16 *)(t + 0x124) & 1) == 0) {
        return;
    }
    *(u8 **)(t + 0x128) = arg1;
    *(s32 *)(t + 0x118) = arg2;
    if (*(s32 *)(arg1 + 0x100) >= 2) {
        *(s32 *)(t + 0x11C) = arg2 + 1;
    } else {
        *(s32 *)(t + 0x11C) = arg2;
    }
}
