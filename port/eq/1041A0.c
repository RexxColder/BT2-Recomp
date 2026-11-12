#include "common.h"

extern s32 D_003876A0;
extern s32 D_00387F2C;
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00208228(s32 arg0, void *arg1, void *arg2, void *arg3);
void func_00148810(s32 arg0);
s32 func_0020C6D0(s32 arg0);
s32 func_002A86E8(void *arg0, void *arg1, s32 arg2);
void func_001031E0(void);

s32 func_001041A0(s32 arg0) {
    u8 *g;
    u8 *obj;
    s32 v17[8];
    s32 v21;
    s32 v22;
    s32 v23;
    s32 s2;
    s32 flag;

    if (func_00211310(func_00211288(arg0), 12, 1) == 0) {
        return 0;
    }

    v17[6] = arg0;
    s2 = func_00208228(arg0, &v21, &v22, &v23);
    if (v22 >= 0) {
        func_00148810(arg0);
    }

    v17[1] = s2 + 44219;
    v17[0] = 0;
    if (v21 >= 0) {
        v17[2] = 9 * v21 + 44225;
    } else {
        v17[2] = -1;
    }
    if (v22 >= 0) {
        v17[3] = 9 * v22 + 44226;
    } else {
        v17[3] = -1;
    }

    if (v23 >= 0) {
        flag = *(s32 *)((u8 *)D_00387F2C + 0x1008) & 1;
        if (flag == 0) {
            v17[4] = v23 + 43939;
        } else {
            v17[4] = v23 + 44079;
        }
    } else {
        v17[4] = -1;
    }

    g = (u8 *)D_003876A0;
    obj = g + 464 * arg0;
    if (*(s32 *)(obj + 0xE0) < 2) {
        v17[5] = -1;
    } else if (func_0020C6D0(arg0) != 0) {
        v17[5] = -1;
    } else {
        v17[5] = 2 * v23;
        if (arg0 == 1) {
            v17[5] = v17[5] + 1;
        }
        v17[5] = v17[5] + 15554;
    }

    *(s32 *)(obj + 0x2AC) = s2;

    if (arg0 == 0) {
        *(s32 *)(g + 0x4E0) = *(s32 *)(g + 0x4E0) | 1;
    } else if (arg0 == 1) {
        *(s32 *)(g + 0x4E0) = *(s32 *)(g + 0x4E0) | 2;
    }

    func_002A86E8(v17, (void *)func_001031E0, 0);
    return func_002113C0(func_00211288(arg0), 12, 1, 0);
}
