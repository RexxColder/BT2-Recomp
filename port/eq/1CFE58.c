#include "common.h"

extern u8 *D_00387E9C;
extern f32 D_003852F4;

s32 func_001CFE58(s32 arg0) {
    u8 *p;
    s32 ret = 0;

    p = *(u8 **)(D_00387E9C + 0x1400) + arg0 * 20;
    if (*(u8 *)(D_00387E9C + 0x1491) != 0) {
        if (!(*(s32 *)(p + 0xC) & 1)) {
            *(s32 *)(p + 0x0) = arg0;
            *(s32 *)(p + 0xC) = *(s32 *)(p + 0xC) | 1;
            *(f32 *)(p + 0x10) = D_003852F4;
        }
        ret = 1;
    }
    return ret;
}
