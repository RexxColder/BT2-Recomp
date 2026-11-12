#include "common.h"

void func_001E1258(f32 farg0, u8 *arg1, s32 arg2, s32 arg3);

void func_001E04C8(u8 *arg0, s32 arg1, f32 farg0) {
    u8 *s0;
    u8 *cur;
    s32 i;

    if (*(u8 *)(arg0 + 0x21DC) != 0) {
        s0 = arg0 + 0x10;
        i = 0;
        if (*(s32 *)(arg0 + 0x1B0) > 0) {
            do {
                cur = s0;
                s0 += 0x1B0;
                i++;
                func_001E1258(farg0, cur, arg1, 0);
            } while (i < *(s32 *)(arg0 + 0x1B0));
        }
    }
}
