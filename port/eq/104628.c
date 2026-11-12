#include "common.h"

extern u8 *D_003876A0;
extern u8 *D_00387F2C;
extern void func_00103A90(void);

s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00208228(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3);
void func_00148810(s32 arg0);
void func_002A86E8(s32 *arg0, void *arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_00104628(s32 arg0) {
    s32 sp[8];
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 s1;
    s32 v;
    u8 *p;

    v = func_00211288(arg0);
    if (func_00211310(v, 0xC, 0x8000) != 0) {
        s1 = func_00208228(arg0, &sp20, &sp24, &sp28);
        if (sp24 >= 0) {
            func_00148810(arg0);
        }

        sp[0] = 0;
        sp[1] = 0xACBB + s1;
        if (sp20 >= 0) {
            sp[2] = sp20 * 9 + 0xACC1;
        } else {
            sp[2] = -1;
        }
        if (sp24 >= 0) {
            sp[3] = sp24 * 9 + 0xACC2;
        } else {
            sp[3] = -1;
        }
        if (sp28 >= 0) {
            if ((*(u32 *)(D_00387F2C + 0x1008) & 1) == 0) {
                sp[4] = 0xABA3 + sp28;
            } else {
                sp[4] = 0xAC2F + sp28;
            }
        } else {
            sp[4] = -1;
        }
        sp[6] = arg0;

        p = D_003876A0 + arg0 * 0x1D0;
        *(s32 *)(p + 0x2AC) = s1;
        func_002A86E8(sp, (void *)func_00103A90, 0);
        v = func_00211288(arg0);
        func_002113C0(v, 0xC, 0x8000, 0);
    }
}
