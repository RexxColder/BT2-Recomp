#include "common.h"

void func_001D9B10(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
extern f32 D_003852F8;
extern u8 *D_00387E9C;

s32 func_001CFEB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 mode = arg2 & 0xFF;
    s8 val = (s8)arg3;

    if (D_00387E9C[0x1491] == 0) {
        return 0;
    }
    if (mode == 0) {
        func_001D9B10(1.0f, arg0, arg1, val);
        return 1;
    }
    if (mode == 1) {
        func_001D9B10(D_003852F8, arg0, arg1, val);
        return 1;
    }
    return 1;
}
