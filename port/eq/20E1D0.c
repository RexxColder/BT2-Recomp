#include "common.h"

s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_0023F420(s32 arg0);

#define FLD(off) (*(s32 *)(arg0 + (off)))

void func_0020E1D0(s32 arg0) {
    s32 t;
    s32 v;

    if (func_00211310(arg0, 1, 0x01000000) != 0) {
        FLD(0x1178) = -0x1E;
        FLD(0x1164) = -0x1E;
        FLD(0x1168) = -0x1E;
    }

    /* 0x1164 */
    t = FLD(0x1164) - 1;
    FLD(0x1164) = t;
    if (t < -0x1E) {
        FLD(0x1164) = -0x1E;
        if (BtlPad_Test4C(arg0, 2) != 0) {
            if (func_0023F420(arg0) & 0x400) {
                FLD(0x1164) = 3;
            }
        }
    } else {
        if (BtlPad_Test4C(arg0, 2) != 0) {
            FLD(0x1164) = -1;
        }
        if (FLD(0xB48) != 1) {
            FLD(0x1164) = -0x1E;
        }
    }

    /* 0x1168 */
    t = FLD(0x1168) - 1;
    FLD(0x1168) = t;
    if (t < -0x1E) {
        FLD(0x1168) = -0x1E;
        if (BtlPad_Test4C(arg0, 2) != 0) {
            if (func_0023F420(arg0) & 0x400) {
                FLD(0x1168) = 2;
            }
        }
    } else {
        if (BtlPad_Test4C(arg0, 2) != 0) {
            FLD(0x1168) = -1;
        }
    }

    /* 0x116C */
    t = FLD(0x116C) - 1;
    FLD(0x116C) = t;
    if (t < -0x1E) {
        FLD(0x116C) = -0x1E;
        if (BtlPad_Test4C(arg0, 0xC) != 0) {
            if (BtlPad_Test4C(arg0, 0) != 0) {
                FLD(0x116C) = 1;
            }
        }
    } else {
        if (BtlPad_Test4C(arg0, 0xC) != 0) {
            if (BtlPad_Test4C(arg0, 0) != 0) {
                FLD(0x116C) = -1;
            }
        }
    }

    /* 0x1170 */
    t = FLD(0x1170) - 1;
    FLD(0x1170) = t;
    if (t < -0xF) {
        FLD(0x1170) = -0xF;
        if (BtlPad_Test4C(arg0, 2) != 0 && (func_0023F420(arg0) & 0x100)) {
            FLD(0x1170) = 5;
        }
    }

    /* 0x1174 */
    t = FLD(0x1174) - 1;
    FLD(0x1174) = t;
    if (t < -0x1E) {
        FLD(0x1174) = -0x1E;
        if (BtlPad_Test4C(arg0, 2) != 0) {
            FLD(0x1174) = 4;
        }
    }

    /* 0x1178 */
    t = FLD(0x1178) - 1;
    FLD(0x1178) = t;
    if (t < -0x1E) {
        FLD(0x1178) = -0x1E;
        if (BtlPad_Test4C(arg0, 2) != 0) {
            if (func_0023F420(arg0) & 0x400) {
                FLD(0x1178) = 2;
            }
        }
    } else {
        v = -1;
        if (BtlPad_Test4C(arg0, 2) != 0) {
            FLD(0x1178) = v;
        }
    }
    (void)v;
}
