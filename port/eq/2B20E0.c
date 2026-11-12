#include "common.h"

s32 func_00276B00(s32 arg0, u8 *arg1, s32 *arg2);
u8 *func_002B1DD0(s32 arg0);
void func_003126C8(u8 *arg0, u8 *arg1);
extern u8 D_002C3630[] __attribute__((section(".data")));
extern f32 D_0038765C;
extern s32 D_00387E18;
extern s32 D_003B2690 __attribute__((section(".data")));

void func_002B20E0(u8 *arg0) {
    s32 sp[4];
    s32 temp_s0;

    if (D_00387E18 != 0) {
        temp_s0 = *(s32 *)(func_002B1DD0(0) + 0x1C);
        if ((temp_s0 < 0) || (func_00276B00(temp_s0, arg0, sp) <= 0)) {
            func_003126C8(arg0, D_002C3630);
        } else if (D_003B2690 == 0) {
            if (temp_s0 == 0x15) {
                *(f32 *)(arg0 + 4) = D_0038765C;
            }
        }
    }
}
