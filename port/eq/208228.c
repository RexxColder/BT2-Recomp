#include "common.h"

extern s32 D_00387930;

s32 func_00211288(s32 arg0);
s32 func_00217488(s32 arg0);
s32 func_00208008(s32 arg0, s32 arg1);
s32 func_00208158(s32 arg0, s32 arg1);
s32 func_002080E0(s32 arg0);
s32 func_00203188(s32 arg0);
void *func_00202E60(s32 arg0, s32 arg1);
s32 func_002081A8(s32 arg0);

s32 func_00208228(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s32 s1;
    s32 s2;
    s32 s3;
    s32 u;
    s32 t;
    s32 dv;
    u8 *p;

    if (D_00387930 == 0) {
        return 0;
    }
    if ((u32)arg0 >= 2) {
        return 0;
    }
    s1 = 0;
    s2 = func_00211288(arg0);
    s3 = 0;
    u = func_00217488(s2);
    dv = 0;

    if (u == 0x34) {
        s1 = func_00208158(arg0, 0);
        dv = 1;
    } else if (u < 0x35) {
        if (u == 0x30) {
            s1 = func_00208008(arg0, 2);
            dv = 1;
        } else if (u < 0x31) {
            if (u == 0x2E) {
                s1 = func_00208008(arg0, 0);
                dv = 1;
            } else if (u == 0x2F) {
                s1 = func_00208008(arg0, 1);
                dv = 1;
            }
        } else if (u == 0x31) {
            s1 = func_00208008(arg0, 3);
            dv = 1;
        } else {
            s3 = 0x16;
            s1 = func_002080E0(arg0);
            t = func_00203188(s2);
            p = (u8 *)func_00202E60(s2, t);
            if (*(u8 *)(p + 0x2C) == 0) {
                dv = 1;
            }
        }
    } else {
        if (u == 0x35) {
            s1 = func_00208158(arg0, 1);
            dv = 1;
        } else if (u == 0x36) {
            s1 = func_00208158(arg0, 2);
            dv = 1;
        } else if (u == 0x38) {
            s1 = func_00208158(arg0, 1);
            dv = 1;
        } else if (u == 0x39) {
            s1 = func_00208158(arg0, 2);
            dv = 1;
        } else if (u == 0xC3) {
            s3 = -1;
            s1 = func_002081A8(arg0);
        }
    }

    if (dv != 0) {
        s3 = s1 / 9;
    }
    if (arg1 != NULL) {
        *arg1 = s3;
    }
    if (arg2 != NULL) {
        *arg2 = s3;
    }
    if (arg3 != NULL) {
        *arg3 = s3;
    }
    return s1;
}
