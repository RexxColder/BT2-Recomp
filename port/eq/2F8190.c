#include "common.h"

s32 func_002EFE20(s32 arg0, s32 arg1);
s32 func_002EFE50(s32 arg0);
s32 func_002EFE68(s32 arg0);
s32 func_002F0388(s32 arg0);
s32 func_002F1510(s32 arg0);
s32 func_002F4DF0(s32 arg0);
s32 memset(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_0034AED8 __attribute__((section(".data")));

void func_002F8190(s32 arg0) {
    u8 *p = (u8 *)arg0;
    s32 sp[4];
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s1;
    u8 *var_s2;
    s32 temp_s0_2;

    temp_s2 = *(s32 *)(p + 0xC);
    temp_s4 = *(s32 *)(p + 0x4);
    temp_s0 = func_002EFE50(temp_s2);
    temp_s3 = func_002EFE68(temp_s2);
    temp_v0 = *(s32 *)(p + 0x48);
    if ((temp_s0 >= ((temp_v0 >= 0x2001) ? 0x2000 : temp_v0)) ||
        (func_002F1510(temp_s4) >= temp_s3) ||
        (func_002F0388(*(s32 *)(p + 0x4)) == 3)) {
        if (*(s8 *)(p + 0x70) == 0) {
            if (*(s8 *)(p + 0x72) == 0) {
                func_002EFE20(temp_s2, 1);
                *(s32 *)(p + 0x9C) = 0;
                *(s32 *)(p + 0xA0) = D_0034AED8;
            }
            *(u8 *)(p + 0x1) = 3;
        }
        *(u8 *)(p + 0x71) = 1;
    }
    if (func_002F0388(*(s32 *)(p + 0x4)) == 3) {
        temp_v0_2 = func_002F4DF0(arg0);
        temp_s3_2 = *(s32 *)(p + 0x48) * temp_v0_2 * 2;
        if (temp_v0_2 > 0) {
            var_s2 = p + 0x18;
            var_s1 = temp_v0_2;
            do {
                temp_s0_2 = *(s32 *)var_s2;
                var_s2 += 4;
                var_s1 -= 1;
                ((void (*)(s32, s32, s32, s32))(*(u32 *)(*(u8 **)temp_s0_2 + 0x18)))(
                    temp_s0_2, 0, temp_s3_2, (s32)sp);
                memset(sp[0], 0, sp[1]);
                ((void (*)(s32, s32, s32))(*(u32 *)(*(u8 **)temp_s0_2 + 0x20)))(
                    temp_s0_2, 1, (s32)sp);
            } while (var_s1 != 0);
        }
    }
}
