#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1, void *arg2, void *arg3);
void func_002C32B0(s32 *arg0, s32 arg1);
void func_002C32C8(s32 *arg0);

s32 func_002C0A88(s32 arg0, s32 arg1, void *arg2) {
    s32 sp[4];
    u8 *a3;
    u8 *s0;
    u8 *out;
    s32 s0_2;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 s6;
    s32 s7;
    s32 fp;
    s32 k;

    a3 = (u8 *)(arg0 + 0x1310 + arg1 * 0x74);
    if (*(s32 *)(a3 + 4) == 0) {
        return func_002C2FF0(arg0, 0xFF000401, arg2, a3);
    }
    s0 = a3 + 0x10;
    func_002C32B0(sp, arg1);
    s4 = *(s32 *)(s0 + 0x8);
    sp[1] = *(s32 *)(s0 + 0x1C);
    sp[2] = *(s32 *)(s0 + 0x20);
    s3 = *(s32 *)(s0 + 0x2C);
    s1 = *(s32 *)(s0 + 0x28);
    s6 = *(s32 *)(s0 + 0xC);
    s2 = *(s32 *)(s0 + 0x10);
    s7 = *(s32 *)(s0 + 0x14);
    fp = *(s32 *)(s0 + 0x18);
    s0_2 = *(s32 *)(s0 + 0x24);
    func_002C32C8(sp);

    out = (u8 *)arg2;
    *(s32 *)(out + 0x0) = s4;
    *(s32 *)(out + 0x8) = s2;
    *(s32 *)(out + 0x4) = s6;
    *(s32 *)(out + 0x24) = s1;
    *(s32 *)(out + 0x28) = s3;
    if (s3 >= s1) {
        *(s32 *)(out + 0x20) = 0;
        *(s32 *)(out + 0xC) = 0;
        *(s32 *)(out + 0x14) = 0;
        *(s32 *)(out + 0x18) = 0;
        *(s32 *)(out + 0x10) = 0;
        *(s32 *)(out + 0x1C) = 0;
        return 0;
    }
    k = (s6 < 9);
    if (s0_2 >= sp[2]) {
        *(s32 *)(out + 0xC) = sp[1] - s0_2;
        *(s32 *)(out + 0x14) = (k != 0) ? (s7 + s0_2) : (s7 + (s0_2 * 2));
        *(s32 *)(out + 0x18) = (k != 0) ? (fp + s0_2) : (fp + (s0_2 * 2));
        *(s32 *)(out + 0x20) = fp;
        *(s32 *)(out + 0x10) = sp[2];
        *(s32 *)(out + 0x1C) = s7;
    } else {
        *(s32 *)(out + 0xC) = sp[2] - s0_2;
        *(s32 *)(out + 0x14) = (k != 0) ? (s7 + s0_2) : (s7 + (s0_2 * 2));
        *(s32 *)(out + 0x18) = (k != 0) ? (fp + s0_2) : (fp + (s0_2 * 2));
        *(s32 *)(out + 0x20) = 0;
        *(s32 *)(out + 0x10) = 0;
        *(s32 *)(out + 0x1C) = 0;
    }
    return 0;
}
