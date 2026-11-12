#include "common.h"

u8 *func_00261060(s32 arg0, s32 arg1);
extern s32 D_003B2654 __attribute__((section(".data")));

void func_00261180(s32 arg0, s32 arg1) {
    s32 a0;
    s32 a1;
    u8 *obj;

    a0 = arg0 & 0xFFFF;
    a1 = arg1 & 0xFF;
    if (!(D_003B2654 & 0x100)) {
        obj = func_00261060(a0, a1);
        if (a1 != 0) {
            *(s32 *)(obj + 0xAF0) = *(s32 *)(obj + 0xAF0) | 2;
        } else {
            *(s32 *)(obj + 0xAF0) = *(s32 *)(obj + 0xAF0) & ~2;
        }
    }
}
