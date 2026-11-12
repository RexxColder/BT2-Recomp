#include "common.h"

extern void *D_003876A0;

s32 func_0010B0A0(s32 arg0);
void func_00114508(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00113860(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00113D80(void *arg0, s32 arg1);
void func_00113B00(void *arg0, s32 arg1, s32 arg2);
void func_001140A8(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void BtlRec_CallFlagged(void *arg0, s32 arg1, s32 arg2);
f32 sinf(f32 arg0);

void func_00110B30(u8 *arg0, s32 arg1) {
    s32 v, k;
    u8 *s0, *s1, *s2;
    f32 m;
    f32 frac;

    v = func_0010B0A0(arg1);
    s2 = (u8 *)(v + 0x3600);
    func_00114508(s2, 2, 0, 3);
    s0 = arg0 + arg1 * 0x750 + 0xD0;
    if (*(s32 *)(s0 + 0x728) >= 3) {
        if (*(s32 *)((u8 *)D_003876A0 + 0xC8) != 2) {
            s1 = (u8 *)(v + 0x3660);
            m = sinf(*(f32 *)(s0 + 0x740)) * -2.0f;
            k = (s32)m;
            frac = m - (f32)k;
            if (frac > 0.5f || (frac == 0.5f && (k & 1))) {
                k++;
            } else if (frac < -0.5f || (frac == -0.5f && (k & 1))) {
                k--;
            }
            func_00113860(v + 0x360C, 0x40, 0x10, 0x50, 0x20, 0x15);
            func_00113D80(s2, 0);
            func_00113B00(s2, k + 2, 0x3D);
            func_00113860(v + 0x366C, 0x40, 0xF, 0x50, 0x1F, 0x15);
            func_00113D80(s1, 0);
            func_00113B00(s1, 2 - k, 0x46);
            *(s32 *)(s2 + 0x60) = *(s32 *)(s2 + 0x60) | 0x60;
        }
    }
    if (arg1 == 1) {
        func_001140A8(s2, 0, 1, 0, 3);
    }
    BtlRec_CallFlagged(s2, 1, 3);
}
