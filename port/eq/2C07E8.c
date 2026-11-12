#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1, void *arg2, void *arg3);
void func_002C32B0(s32 *arg0, s32 arg1);
void func_002C32C8(s32 *arg0, s32 arg1);

s32 func_002C07E8(s32 arg0, s32 arg1, void *arg2) {
    s32 sp[4];
    s32 temp_a1;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_s6;
    s32 temp_s7;
    s32 temp_fp;
    u8 *a3;
    u8 *s0;
    u8 *out;

    a3 = (u8 *)(arg0 + 0x1310 + arg1 * 0x74);
    if (*(s32 *)(a3 + 4) == 0) {
        return func_002C2FF0(arg0, 0xFF000401, arg2, a3);
    }
    s0 = a3 + 0x10;
    func_002C32B0(sp, arg1);
    sp[1] = *(s32 *)(s0 + 0x8);
    temp_a1 = *(s32 *)(s0 + 0x18);
    temp_s3 = *(s32 *)(s0 + 0x2C);
    temp_s4 = *(s32 *)(s0 + 0x1C);
    temp_s1 = *(s32 *)(s0 + 0x28);
    temp_s7 = *(s32 *)(s0 + 0xC);
    temp_s2 = *(s32 *)(s0 + 0x10);
    temp_fp = *(s32 *)(s0 + 0x14);
    temp_s6 = *(s32 *)(s0 + 0x20);
    temp_s0_2 = *(s32 *)(s0 + 0x24);
    func_002C32C8(sp, temp_a1);

    out = (u8 *)arg2;
    *(s32 *)(out + 0x8) = temp_s2;
    *(s32 *)(out + 0x0) = sp[1];
    *(s32 *)(out + 0x4) = temp_s7;
    *(s32 *)(out + 0x24) = temp_s1;
    *(s32 *)(out + 0x28) = temp_s3;

    if (temp_s1 >= temp_s3 + temp_s4) {
        *(s32 *)(out + 0x20) = 0;
        *(s32 *)(out + 0xC) = 0;
        *(s32 *)(out + 0x14) = 0;
        *(s32 *)(out + 0x18) = 0;
        *(s32 *)(out + 0x10) = 0;
        *(s32 *)(out + 0x1C) = 0;
    } else if (temp_s6 >= temp_s0_2) {
        *(s32 *)(out + 0xC) = temp_s4 - temp_s6;
        if (temp_s7 < 9) {
            *(s32 *)(out + 0x14) = temp_fp + temp_s6;
            *(s32 *)(out + 0x18) = temp_a1 + temp_s6;
        } else {
            *(s32 *)(out + 0x14) = temp_fp + (temp_s6 * 2);
            *(s32 *)(out + 0x18) = temp_a1 + (temp_s6 * 2);
        }
        *(s32 *)(out + 0x20) = temp_a1;
        *(s32 *)(out + 0x10) = temp_s0_2;
        *(s32 *)(out + 0x1C) = temp_fp;
    } else {
        *(s32 *)(out + 0xC) = temp_s0_2 - temp_s6;
        if (temp_s7 < 9) {
            *(s32 *)(out + 0x14) = temp_fp + temp_s6;
            *(s32 *)(out + 0x18) = temp_a1 + temp_s6;
        } else {
            *(s32 *)(out + 0x14) = temp_fp + (temp_s6 * 2);
            *(s32 *)(out + 0x18) = temp_a1 + (temp_s6 * 2);
        }
        *(s32 *)(out + 0x20) = 0;
        *(s32 *)(out + 0x10) = 0;
        *(s32 *)(out + 0x1C) = 0;
    }
    return 0;
}
