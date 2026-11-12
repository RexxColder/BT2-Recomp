#include "common.h"

extern void *D_00346BD8 __attribute__((section(".data")));
extern void *D_00346BDC __attribute__((section(".data")));
extern s32 D_0038BC08 __attribute__((section(".data")));
extern s32 D_0038BBC8[] __attribute__((section(".data")));
extern u8 D_0038BC10[] __attribute__((section(".data")));
extern u8 D_00378890[] __attribute__((section(".data")));
extern u8 D_003788F0[] __attribute__((section(".data")));
extern u8 D_00378A88[] __attribute__((section(".data")));
extern u8 D_00378948[] __attribute__((section(".data")));
extern u8 D_003789B8[] __attribute__((section(".data")));
extern u8 D_00378A40[] __attribute__((section(".data")));
extern u8 D_00378878[] __attribute__((section(".data")));
extern u8 D_00378860[] __attribute__((section(".data")));

void *func_002B7CB8(void *arg0);
void *func_002CC0F0(void *arg0);
void func_00325830(void *arg0, void *arg1, s32 arg2);
void *strncat(void *arg0, void *arg1, s32 arg2);
s32 Rand_Range(void *arg0);

s32 func_002B6818(void *arg0, s32 arg1) {
    void *s2;
    void *s3;
    s32 idx;

    s3 = NULL;
    if (arg0 == NULL) {
        D_00346BD8 = NULL;
        s2 = NULL;
        D_00346BDC = NULL;
    } else {
        s2 = func_002B7CB8(arg0);
        D_00346BD8 = arg0;
        D_00346BDC = s2;
    }

    if (arg1 != 0) {
        idx = D_0038BC08;
        D_0038BBC8[idx] = arg1;
        if (idx < 0xF) {
            D_0038BC08 = idx + 1;
        }
    }

    if (arg1 > (s32)0xFF000F18) {
        if (arg1 == (s32)0xFF000F40) {
            func_00325830(D_0038BC10, D_00378878, (s32)0xFF000F40);
            if (s2 != NULL) {
                s3 = func_002CC0F0(s2);
            }
            if (s3 != NULL) {
                strncat(D_0038BC10, s3, 0xE9);
            }
        } else if (arg1 > (s32)0xFF000F40) {
            if (arg1 < -1) {
                if (arg1 < -3) {
                    func_00325830(D_0038BC10, D_00378A88, arg1);
                } else {
                    func_00325830(D_0038BC10, D_00378860, arg1);
                }
            } else {
                func_00325830(D_0038BC10, D_00378A88, arg1);
            }
        } else {
            if (arg1 == (s32)0xFF000F1C) {
                func_00325830(D_0038BC10, D_003788F0, arg1);
            } else if (arg1 == (s32)0xFF000F1F) {
                func_00325830(D_0038BC10, D_00378A40, arg1);
            } else {
                func_00325830(D_0038BC10, D_00378A88, arg1);
            }
        }
    } else if (arg1 >= (s32)0xFF000F17) {
        func_00325830(D_0038BC10, D_00378890, arg1);
    } else {
        if (arg1 == (s32)0xFF00040C || arg1 == (s32)0xFF000408) {
            func_00325830(D_0038BC10, D_003788F0, arg1);
        } else if (arg1 > (s32)0xFF00040C) {
            if (arg1 == (s32)0xFF000C04) {
                func_00325830(D_0038BC10, D_003789B8, (s32)0xFF000C04);
            } else if (arg1 == (s32)0xFF000F15) {
                func_00325830(D_0038BC10, D_00378948, (s32)0xFF000F15);
            } else {
                func_00325830(D_0038BC10, D_00378A88, arg1);
            }
        } else {
            func_00325830(D_0038BC10, D_00378A88, arg1);
        }
    }

    return Rand_Range(D_0038BC10);
}
