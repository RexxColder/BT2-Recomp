#include "common.h"

extern u8 *D_003876A0;
extern u8 *D_00387F2C;

s32 func_00211288(s32 a0);
s32 func_00211310(s32 a0, s32 a1, s32 a2);
void func_002113C0(s32 a0, s32 a1, s32 a2, s32 a3);
void func_00148810(s32 a0);
s32 func_00208228(s32 a0, s32 a1, s32 a2, s32 a3);
s32 func_00208508(s32 a0);
s32 func_0020C6D0(s32 a0, s32 a1, s32 a2, void *a3, s32 a4);
void func_002A86E8(void *a0, s32 a1, s32 a2, s32 a3);
s32 func_00103488(s32 arg0);
s32 func_00103650(s32 arg0);

void func_001043A8(s32 arg0) {
    s32 sp[8];
    s32 s0;
    s32 s1;
    s32 s3;
    s32 v0;
    s32 v1;
    s32 a1;
    s32 a2;
    s32 t0;
    u8 *a3;

    if (func_00211310(func_00211288(arg0), 0xC, 0x20) == 0) {
        return;
    }
    func_00148810(arg0);
    s0 = 0xACBB;
    s1 = func_00208228(arg0, 0, 0, 0);
    s3 = s1 / 9;
    v0 = func_00208508(arg0) + s0;
    sp[0] = 0;
    sp[5] = -1;
    sp[4] = -1;
    sp[3] = v0;
    sp[6] = arg0;
    func_002A86E8(sp, (s32)func_00103488, 0, -1);
    s0 = s1 + s0;
    v0 = s3 * 9;
    sp[0] = 0;
    sp[1] = s0;
    a2 = 0xACC2 + v0;
    v0 = 0xACC1 + v0;
    sp[6] = arg0;
    a1 = arg0 * 0x1D0;
    sp[2] = v0;
    sp[3] = a2;
    a3 = D_003876A0 + a1;
    v0 = *(s32 *)(D_00387F2C + 0x1008) & 1;
    v1 = 0xAC2F + s3;
    t0 = 0xABA3 + s3;
    if (v0 == 0) {
        v1 = t0;
    }
    sp[4] = v1;
    *(s32 *)(a3 + 0x2AC) = s1;
    if (*(s32 *)(D_003876A0 + a1 + 0xE0) < 2) {
        sp[5] = -1;
    } else if (func_0020C6D0(arg0, a1, a2, a3, t0) != 0) {
        sp[5] = -1;
    } else {
        v1 = s3 * 2;
        if (arg0 == 1) {
            v1 = v1 + 1;
        }
        sp[5] = v1 + 0x3CC2;
    }
    func_002A86E8(sp, (s32)func_00103650, 0, 0);
    v0 = func_00211288(arg0);
    func_002113C0(v0, 0xC, 0x20, 0);
}
