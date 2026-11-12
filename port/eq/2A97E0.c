#include "common.h"

s32 func_00284E08(s32 arg0);
void func_00284E68(f32 farg0, s32 arg0, s32 arg1);
s32 func_0029F6F8(s32 arg0);
s32 func_002ACF10(s32 arg0);
extern s32 D_003B2654 __attribute__((section(".data")));

s32 func_002A97E0(void) {
    s32 st;

    st = *(s32 *)((u8 *)&D_003B2654 + 0x50);
    if (st == 1) {
        if (func_00284E08(0) != 0) {
            *(s32 *)((u8 *)&D_003B2654 + 0x50) = 2;
        }
        return 0;
    }
    if (st < 2) {
        if (st != 0) {
            return 0;
        }
        if (func_002ACF10(st) != 0) {
            func_00284E68(1.0f, 0, 0);
            *(s32 *)((u8 *)&D_003B2654 + 0x50) = 1;
            return 0;
        }
        if (func_0029F6F8(*(s32 *)((u8 *)&D_003B2654 + 0x10)) == 0) {
            return 1;
        }
        return 0;
    }
    if (st == 2) {
        return 1;
    }
    return 0;
}
