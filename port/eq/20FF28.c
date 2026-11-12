#include "common.h"

s32 func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_0020FF28(s32 arg0) {
    u8 *p;
    s32 i;
    s32 j;
    u32 k;
    s32 bit;

    p = (u8 *)arg0 + 0x350;
    for (k = 0; k < 0x10; k++) {
        j = 0;
        if (p[-0x10] != 0 || p[0x180] != 0) {
            for (j = 0; j < 8; j++) {
                bit = 1 << j;
                if (p[0] & bit) {
                    func_00297FE0(0x41, (s32)(k * 8) + j, 0, 0, 0);
                    p[0] = (u8)(p[0] & ~bit);
                }
            }
        }
        p += 1;
    }
}
