#include "common.h"

s32 func_002D07B0(s32 arg0, s32 arg1);
s32 func_002BEA60(s32 arg0, s32 arg1);
s32 func_002BEC18(s32 arg0);
s32 func_002C2FF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00304760(s32 arg0, s32 arg1, s32 arg2);
void func_002F4308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002BF088(s32 arg0, s32 arg1);
void func_002BEC98(s32 arg0);
extern u8 func_002BD850[] __attribute__((section(".data")));
extern u8 func_002BD870[] __attribute__((section(".data")));
extern u8 func_002BD890[] __attribute__((section(".data")));
extern u8 func_002BD8B0[] __attribute__((section(".data")));
extern u8 func_002BD8D0[] __attribute__((section(".data")));

s32 func_002BE908(u8 *arg0) {
    u8 *s0;
    u8 *s3;
    u8 *t0;
    s32 v0;
    s32 temp;
    s32 r2;

    s0 = arg0 + 0x35B0;
    s3 = arg0 + 0x35A8;
    v0 = func_002D07B0((s32)arg0, 6);
    if (v0 == 0) {
        return v0;
    }
    *(s32 *)(arg0 + 0x2004) = (s32)s3;
    v0 = func_002BEA60((s32)arg0, (s32)s3);
    if (v0 != 0) {
        return v0;
    }
    r2 = func_002BEC18((s32)s0);
    if (r2 == 0) {
        return func_002C2FF0(0, 0xFF000C04, 0, 0);
    }
    temp = func_00304760(*(s32 *)(s0 + 8), *(s32 *)(arg0 + 0x35B0), *(s32 *)(s0 + 4));
    t0 = arg0 + 0x365C;
    if (temp == 0) {
        return func_002C2FF0(0, 0xFF000C05, (s32)func_002BD8B0, (s32)func_002BD8D0);
    }
    *(s32 *)(s3 + 4) = temp;
    *(s32 *)(s3 + 0) = r2;
    *(s32 *)(arg0 + 0x2114) = (s32)t0;
    *(s32 *)(t0 + 0x14) = (s32)func_002BD8D0;
    *(s32 *)(arg0 + 0x365C) = *(s32 *)(r2 + 0xC);
    *(s32 *)(t0 + 4) = (s32)func_002BD850;
    *(s32 *)(t0 + 8) = (s32)func_002BD870;
    *(s32 *)(t0 + 0xC) = (s32)func_002BD890;
    *(s32 *)(t0 + 0x10) = (s32)func_002BD8B0;
    func_002F4308(r2, temp, (s32)func_002BD8B0, (s32)func_002BD8D0);
    func_002BF088((s32)arg0, 1);
    func_002BEC98((s32)arg0);
    return 0;
}
