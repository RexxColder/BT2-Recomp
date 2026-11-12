#include "common.h"

void func_00101798(void);
void func_002EF218(void);
void func_002F44A0(s32 arg0);
s32 func_002F4590(s32 arg0);
extern s32 D_00387F00[];
extern s32 D_00387F1C;
extern s32 gStgPanBlur;

void func_001012D0(void) {
    s32 idx;
    s32 s0;
    s32 a0v;

    func_00101798();
    func_002F44A0(gStgPanBlur);
    func_002F44A0(D_00387F1C);
    func_002F44A0(D_00387F00[2]);
    a0v = D_00387F00[0];
    s0 = 1;
    idx = 0;
    for (;;) {
        idx += 1;
        s0 -= 1;
        func_002F44A0(a0v);
        if (s0 < 0) {
            break;
        }
        a0v = D_00387F00[idx];
    }
    for (;;) {
        if (func_002F4590(gStgPanBlur) != 0) {
            func_002EF218();
            continue;
        }
        if (func_002F4590(D_00387F1C) != 0) {
            func_002EF218();
            continue;
        }
        if (func_002F4590(D_00387F00[2]) != 0) {
            func_002EF218();
            continue;
        }
        s0 = 0;
        idx = 0;
        while (s0 < 2) {
            a0v = D_00387F00[idx];
            idx += 1;
            if (func_002F4590(a0v) != 0) {
                break;
            }
            s0 += 1;
        }
        if (s0 != 2) {
            func_002EF218();
            continue;
        }
        break;
    }
}
