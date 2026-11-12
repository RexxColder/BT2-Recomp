#include "common.h"

void func_001EB270(void);

#ifdef __mips__
#define LOOP_IS_UPDATE(p) ((void *)(p) == (void *)func_001EB270)
#else
#define LOOP_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001EB270u)
#endif

void func_001EBBC8(s32 arg0, s32 arg1) {
    u8 *temp_a0;
    u16 temp_v1;

    if (arg0 == 0) {
        return;
    }
    if (!LOOP_IS_UPDATE(*(void **)*(u8 **)((u8 *)arg0 + 0x28))) {
        return;
    }
    temp_a0 = *(u8 **)((u8 *)arg0 + 0x38);
    if (temp_a0 == 0) {
        return;
    }
    temp_v1 = *(u16 *)(temp_a0 + 0x60);
    if ((temp_v1 & 1) == 0) {
        return;
    }
    if ((arg1 & 0xFF) != 0) {
        *(u16 *)(temp_a0 + 0x60) = (u16)(temp_v1 | 8);
        return;
    }
    *(u16 *)(temp_a0 + 0x60) = (u16)(temp_v1 & 0xFFF7);
}
