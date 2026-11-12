#include "common.h"

extern u8 *D_003876A0;
extern u8 *D_00387930;

s32 func_00211270();
u8 *func_00211288(s32 arg0);
void func_0020FF28(u8 *arg0);
s32 func_0020A658(s32 arg0);
void func_0020FCB0(u8 *arg0);
void func_00210110(u8 *arg0);
void func_00210670(u8 *arg0);
void func_00210360(u8 *arg0);
void func_00210410(u8 *arg0);
void func_00212DE0(u8 *arg0);
void func_00213050(u8 *arg0);
void func_002130B0(u8 *arg0);
void func_00213310(u8 *arg0);
void func_002134D0(u8 *arg0);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
void func_001F91C8(u8 *arg0);
u8 *BtlMember_GetActiveGauge(u8 *arg0);
void func_001F93C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00203C58(u8 *arg0, s64 arg1);
s32 func_001F6F48();

s32 func_001F8420(s32 arg0) {
    u8 *gl;
    u8 *s0;
    u8 *gl2;
    u8 *r;
    s32 s1;
    s32 c;
    s32 v;

    gl = D_003876A0;
    s1 = 0;
    if ((*(u64 *)(gl + 0x4D8) & 0x100) != 0) {
        c = func_00211270(arg0);
        while (s1 < c) {
            r = func_00211288(s1);
            s1 = s1 + 1;
            func_0020FF28(r);
            c = func_00211270();
        }
        return 0;
    }
    if ((*(u64 *)(gl + 0x4D8) & 0x2000) != 0) {
        c = func_00211270(arg0);
        while (s1 < c) {
            r = func_00211288(s1);
            s1 = s1 + 1;
            func_0020FF28(r);
            c = func_00211270();
        }
        return 0;
    }

    c = func_00211270(arg0);
    while (s1 < c) {
        if (func_0020A658(s1) != 0) {
            r = func_00211288(s1);
            func_0020FF28(r);
            s1 = s1 + 1;
        } else {
            s0 = func_00211288(s1);
            func_0020FCB0(s0);
            func_00210110(s0);
            func_00210670(s0);
            func_00210360(s0);
            func_00210410(s0);
            func_00212DE0(s0);
            func_00213050(s0);
            func_002130B0(s0);
            func_00213310(s0);
            func_002134D0(s0);
            v = func_00211310(s0, 6, 8);
            gl2 = *(u8 **)(s0 + 0x1530);
            if (v != 0 || *(s32 *)(s0 + 0xB78) > 0) {
                *(u32 *)(gl2 + 0xAF0) = *(u32 *)(gl2 + 0xAF0) | 0x2000000;
            } else {
                *(u32 *)(gl2 + 0xAF0) = *(u32 *)(gl2 + 0xAF0) & 0xFDFFFFFF;
            }
            func_001F91C8(s0);
            if (*(u8 *)(BtlMember_GetActiveGauge(s0) + 0x2C) != 0) {
                *(u8 *)(*(u8 **)(s0 + 0x1530) + 0xE5C) = 1;
                func_001F93C0(s0, 0, -10, 1);
                func_001F93C0(s0, 1, -10, 1);
                func_001F93C0(s0, 2, -10, 1);
                func_001F93C0(s0, 3, -10, 1);
            } else {
                *(u8 *)(*(u8 **)(s0 + 0x1530) + 0xE5C) = 0;
            }
            if ((*(u32 *)(D_00387930 + 8) & 8) != 0) {
                func_001F93C0(s0, 2, -20, 1);
            }
            v = func_00211310(s0, 9, 0x20000000);
            gl2 = *(u8 **)(s0 + 0x1530);
            if (v != 0) {
                *(u32 *)(gl2 + 0xAF0) = *(u32 *)(gl2 + 0xAF0) | 0x8000000;
            } else {
                *(u32 *)(gl2 + 0xAF0) = *(u32 *)(gl2 + 0xAF0) & 0xF7FFFFFF;
            }
            if (func_00203C58(s0, 0x40000000000LL) != 0) {
                gl2 = *(u8 **)(s0 + 0x1530);
                *(u32 *)(gl2 + 0xAF0) = *(u32 *)(gl2 + 0xAF0) | 0x80;
            } else {
                gl2 = *(u8 **)(s0 + 0x1530);
                *(u32 *)(gl2 + 0xAF0) = *(u32 *)(gl2 + 0xAF0) & 0xFFFFFF7F;
            }
            s1 = s1 + 1;
        }
        c = func_00211270();
    }
    return func_001F6F48();
}
