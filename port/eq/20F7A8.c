#include "common.h"

extern u8 *D_00387930;

s32 BtlChar_FrameMod(s32 arg0);
s32 BtlFacade_AreBothInterruptible_20EC60(void);
s32 func_0020A168(s32 arg0);
void func_0020EC98(s32 arg0);
void func_0020F070(void);
void *func_00211288(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00212DD8(s32 arg0, s32 arg1);

s32 func_0020F7A8(s32 arg0) {
    u8 *s1;
    s32 s2;
    s32 s3;
    s32 s0;
    s32 b;
    s32 v;

    s2 = arg0;
    s1 = D_00387930 + 0x60;
    if (s2 != 7) {
        if (s2 < 8) {
            if (s2 != 6) {
                return s2;
            }
            *(s32 *)s1 = 0;
            return 7;
        }
        if (s2 != 8) {
            return s2;
        }
        if (*(s32 *)s1 == 0) {
            s3 = 0;
            s0 = func_0020A168(0);
            b = func_0020A168(1);
            if (b >= s0) {
                s3 = 1;
                if (s0 >= b) {
                    s3 = (BtlChar_FrameMod(2) == 0);
                }
            }
            func_002113C0(func_00211288(s3), 7, 0x8000, 1);
            func_002113C0(func_00211288(s3 == 0), 7, 0x10000, 1);
            func_002113C0(func_00211288(s3), 0x10, 0x80000000, 1);
            func_00212DD8(func_00211288(s3), 0x19);
            v = *(s32 *)(D_00387930 + 8);
            if (!(v & 4)) {
                *(s32 *)(D_00387930 + 8) = v | 4;
                func_002113C0(func_00211288(s3), 0x10, 0x04000000, 1);
            }
            *(s32 *)(s1 + 4) = s3;
        }
        v = *(s32 *)s1 + 1;
        *(s32 *)s1 = v;
        if (BtlFacade_AreBothInterruptible_20EC60() == 0) {
            s2 = 0;
        }
        return s2;
    }
    if (*(s32 *)s1 == 0) {
        func_00212DD8(func_00211288(0), 0x18);
    }
    if (*(s32 *)s1 == 0xF) {
        func_00212DD8(func_00211288(1), 0x18);
    }
    func_0020F070();
    v = *(s32 *)s1 + 1;
    *(s32 *)s1 = v;
    if (v >= 0x4C) {
        *(s32 *)s1 = 0;
        s2 = 8;
    }
    if (BtlFacade_AreBothInterruptible_20EC60() == 0) {
        s2 = 0;
        func_0020EC98(0);
        func_0020EC98(1);
    }
    return s2;
}
