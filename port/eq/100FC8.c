#include "common.h"

s32 func_002EB9B0(s32 arg0, s32 arg1);
void func_002EBB08(s32 arg0);
s32 func_002EC0C8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002EC990(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_00387688;
extern s32 D_0038768C;
extern s32 D_00387690;
extern s32 D_00387694;
extern s32 D_00387698;
extern s32 D_0038769C;
extern s32 D_00387F80[] __attribute__((section(".data")));
extern s32 D_00387F20[];

s32 func_00100FC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 va1;
    s32 va2;
    s32 va3;
    s32 i;
    s32 a2v;
    s32 t0;
    s32 t1;
    s32 s0;
    s32 s1;
    s32 a0c;
    s32 v;

    va1 = arg1;
    va2 = arg2;
    va3 = arg3;
    if (arg0 != 0) {
        i = D_00387698;
        va3 = -1;
        va2 = (s32)&D_00387F80[i];
        va1 = (s32)&D_00387F80[i + 1];
        D_00387F80[i] = -1;
        D_00387698 = i + 3;
        D_00387F80[i + 1] = -1;
        D_00387F80[i + 2] = -1;
        D_0038769C = 1;
        D_00387688 = 0;
        D_00387698 = 0;
    }

    if (D_00387688 == 1) {
        goto block_15;
    }
    if (D_00387688 < 2) {
        if (D_00387688 != 0) {
            return 0;
        }
        /* state 0: pick the first two table entries */
        i = D_00387698;
        a2v = D_00387F80[i + 2];
        t0 = D_00387F80[i];
        t1 = D_00387F80[i + 1];
        a0c = (a2v < 0x33B2);
        D_00387698 = i + 3;
        D_00387690 = t0;
        D_00387694 = t1;
        s0 = (a0c == 0) ? (a2v - 0x33B2) : a2v;
        s1 = (a0c != 0) ? 0 : 4;
        do {
            v = func_002EB9B0(D_00387F20[s1 >> 2], s0);
            D_0038768C = v;
        } while (v == 0);
        D_00387688 += 1;
        goto block_15;
    }
    if (D_00387688 == 2) {
        if (func_002EC990(D_0038768C, va1, va2, va3) == 3) {
            func_002EBB08(D_0038768C);
            D_0038768C = 0;
            if (D_00387F80[D_00387698] != -1) {
                D_00387688 = 0;
            } else {
                D_00387688 += 1;
            }
        }
        return 0;
    }
    if (D_00387688 == 3) {
        D_0038769C = 2;
        return 1;
    }
    return 0;

block_15:
    if (func_002EC0C8(D_0038768C, D_00387690, D_00387694) != D_00387690) {
        D_00387688 = 0;
    } else {
        D_00387688 += 1;
    }
    return 0;
}
