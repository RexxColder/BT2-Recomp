#include "common.h"

void *memset(void *s, s32 c, u32 n);

void func_0025FE58(s32 arg0, s32 arg1) {
    s32 temp_a3;

    temp_a3 = arg0 + 0xBD0;
    *(s32 *)(temp_a3 + 0x28) = *(s32 *)(arg0 + arg1 * 4 + 0x60);
    if (*(s32 *)(temp_a3 + 0x28) != 0) {
        *(s16 *)(temp_a3 + 0x04) = (s16)arg1;
        *(s32 *)(temp_a3 + 0x10) = 0;
        *(s32 *)(temp_a3 + 0x14) = 0;
        *(f32 *)(temp_a3 + 0x08) = (f32)*(u16 *)(*(s32 *)(temp_a3 + 0x28) + 2);
        memset((void *)(temp_a3 + 0x30), 0, 0x8E);
    }
}
