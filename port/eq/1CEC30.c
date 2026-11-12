#include "common.h"

void func_001D8AE8(s32 arg0, s32 arg1, f32 farg0, f32 farg1);
extern f32 D_0038527C;
extern f32 D_00385280;
extern u8 *D_00387E9C;

s32 func_001CEC30(s32 arg0, s32 arg1, s32 arg2) {
    u32 temp_a2 = arg2 & 0xFF;

    if (*(u8 *)(D_00387E9C + 0x1491) == 0) {
        return 0;
    }
    if (temp_a2 == 1) {
        func_001D8AE8(arg0, arg1, D_00385280, 1.0f);
        return 1;
    }
    if (temp_a2 == 0) {
        func_001D8AE8(arg0, arg1, D_0038527C, 1.0f);
        return 1;
    }
    if (temp_a2 == 2) {
        func_001D8AE8(arg0, arg1, 1.0f, 1.0f);
        return 1;
    }
    return 1;
}
