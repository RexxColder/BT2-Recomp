#include "common.h"

#define W32(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern f32 D_00385880;
extern f32 D_00385884;

s32 func_00211270();
u8 *func_00211288(s32 a0);
s32 func_0023EAC0(u8 *a0);
void func_00206958(u8 *a0, s64 a1);
void func_001FBE80(u8 *a0, f32 farg0, f32 farg1);
void BtlChar_Vibrate(u8 *a0, f32 farg0, f32 farg1);
void func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);

void func_001FF818(s32 arg0) {
    s32 i;
    s32 j;
    s32 fp;
    s32 n;
    s32 s0;
    s32 temp;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;

    i = 0;
    n = func_00211270(arg0);
    while (i < n) {
        fp = i + 1;
        j = fp;
        while (j < func_00211270()) {
            s1 = func_00211288(i);
            s2 = func_00211288(j);
            s4 = s1 + 0xBE0;
            j += 1;
            s3 = s2 + 0xBE0;
            if (W32(s4, 0x10) == W32(s2, 0x1534) && W32(s3, 0x10) == W32(s1, 0x1534)) {
                s0 = func_0023EAC0(s1);
                temp = func_0023EAC0(s2);
                if (temp < s0) {
                    W32(s3, 0x10) = -1;
                } else {
                    W32(s4, 0x10) = -1;
                    if (s0 >= temp) {
                        W32(s3, 0x10) = -1;
                        func_00206958(s1, 0x04000000);
                        func_00206958(s2, 0x04000000);
                        func_001FBE80(s1, 2.0f, D_00385880);
                        func_001FBE80(s2, 2.0f, D_00385880);
                        BtlChar_Vibrate(s1, 1.0f, D_00385884);
                        BtlChar_Vibrate(s2, 1.0f, D_00385884);
                        func_002113C0(s1, 0x10, 0x10000000, 1);
                        func_002113C0(s2, 0x10, 0x10000000, 1);
                    }
                }
            }
        }
        n = func_00211270(i);
        i = fp;
    }
}
