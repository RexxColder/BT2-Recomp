#include "common.h"

void func_00121050(s32 arg0, s32 arg1, f32 farg0, f32 farg1);
void func_001226F0(s32 arg0, s32 arg1);
extern f32 D_00384104;
extern f32 D_00384108;

void func_00122738(s32 arg0) {
    u8 *temp_s1;

    temp_s1 = (u8 *)(arg0 + 0xFE0);
    func_00121050(arg0, arg0 + 0x1050, D_00384104, D_00384108);
    if (*(s32 *)(temp_s1 + 0x28) & 4) {
        func_001226F0(arg0, 3);
    }
    if (*(s32 *)(temp_s1 + 0x28) & 1) {
        func_001226F0(arg0, 1);
    }
    if (*(s32 *)(temp_s1 + 0x28) & 2) {
        func_001226F0(arg0, 2);
    }
}
