#include "common.h"

void Rand_Range(void *a0, s32 a1);
s32 func_002B5478(s32 a0);
s32 func_002B54B8(s32 a0);
s32 func_002B5448(s32 a0, s32 a1, s32 a2);
void func_002B53B0(void *a0, void *a1, void *a2);
void func_002B5620(void *a0, void *a1, void *a2);
s32 func_002B5520(void *a0, void *a1, s32 a2, s32 a3);
s32 func_002D2128(s32 a0, s32 *a1);
extern u8 D_00378480[] __attribute__((section(".data")));

void func_002B51D0(void *arg0, void *arg1, void *arg2) {
    s32 sp[9];
    u8 *p0;
    u8 *p1;
    u8 *p2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s3;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_s7;
    s32 temp_fp;
    s32 temp_v0;

    p0 = (u8 *)arg0;
    p1 = (u8 *)arg1;
    p2 = (u8 *)arg2;

    temp_s0 = *(s32 *)(p0 + 0x3C);
    temp_s7 = *(s32 *)(p1 + 0x20);
    sp[1] = func_002B5478(*(s32 *)(p1 + 0x1C));
    sp[2] = *(s32 *)(p1 + 0x0);
    sp[3] = *(s32 *)(p1 + 0x4);
    sp[4] = *(s32 *)(p1 + 0x8);
    sp[5] = *(s32 *)(p1 + 0xC);
    sp[6] = func_002B54B8(*(s32 *)(p1 + 0x10));
    temp_s3 = *(s32 *)(p1 + 0x18);
    temp_s5 = *(s32 *)(p1 + 0x34);
    temp_s6 = *(s32 *)(p1 + 0x30);
    temp_fp = *(s32 *)(p1 + 0x2C);
    sp[7] = *(s32 *)(p1 + 0x24);
    sp[8] = *(s32 *)(p1 + 0x28);
    if (func_002D2128(temp_s0, sp) != 0) {
        Rand_Range(D_00378480, sp[0]);
    }
    temp_s0_2 = func_002B5448(temp_s5, sp[0], temp_s3);
    temp_v0 = func_002B5448(temp_s6, sp[0], temp_s3);

    *(s32 *)(p2 + 0x00) = temp_s7;
    *(s32 *)(p2 + 0x34) = temp_v0;
    *(s32 *)(p2 + 0x08) = sp[1];
    *(s32 *)(p2 + 0x0C) = sp[2];
    *(s32 *)(p2 + 0x10) = sp[3];
    *(s32 *)(p2 + 0x14) = sp[4];
    *(s32 *)(p2 + 0x18) = sp[5];
    *(s32 *)(p2 + 0x20) = sp[0];
    *(s32 *)(p2 + 0x24) = temp_s0_2;
    *(s32 *)(p2 + 0x28) = temp_s5;
    *(s32 *)(p2 + 0x2C) = temp_s3;
    *(s32 *)(p2 + 0x30) = temp_fp;
    *(s32 *)(p2 + 0x38) = temp_s6;
    *(s32 *)(p2 + 0x1C) = sp[6];
    *(s32 *)(p2 + 0x3C) = sp[7];
    *(s32 *)(p2 + 0x40) = sp[8];
    func_002B53B0(arg0, arg1, arg2);
    func_002B5620(arg0, arg1, arg2);
    *(s32 *)(p2 + 0x4C) = func_002B5520(arg0, arg1, *(s32 *)(p2 + 0x88), *(s32 *)(p2 + 0x8C));

    *(s64 *)(p2 + 0x50) = *(s64 *)(p1 + 0x48);
    *(s64 *)(p2 + 0x58) = *(s64 *)(p1 + 0x50);
    *(s64 *)(p2 + 0x60) = *(s64 *)(p1 + 0x58);
    *(s64 *)(p2 + 0x68) = *(s64 *)(p1 + 0x60);
    *(s64 *)(p2 + 0x70) = *(s64 *)(p1 + 0x68);
    *(s64 *)(p2 + 0x78) = *(s64 *)(p1 + 0x70);
    *(s64 *)(p2 + 0x80) = *(s64 *)(p1 + 0x78);
}
