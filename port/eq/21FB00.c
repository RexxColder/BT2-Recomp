#include "common.h"

s32 BtlChar_FrameMod(s32 arg0);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212320(s32 arg0);
s32 func_00212820(s32 arg0);
s32 func_00212878(void);
s32 func_00217518(s32 arg0, s32 arg1);
s32 func_0023CDF8(s32 arg0, s32 arg1);
s32 func_0023F410(s32 arg0);

s32 func_0021FB00(s32 arg0) {
    s32 temp;
    s32 s2;
    s32 s2b;
    s32 s2c;
    s32 r;

    if (*(u8 *)(arg0 + 0x1014) != 0) {
        return -1;
    }
    if (func_00211310(arg0, 7, 0x400) != 0) {
        temp = func_00212320(arg0);
        if (temp == 3) {
            return 0xE1;
        }
        if (temp >= 4) {
            if (temp == 4) {
                return 0xE2;
            }
        } else {
            if (temp == 2) {
                return 0xE0;
            }
        }
    }
    if (func_00211310(arg0, 7, 0x4000) != 0) {
        return 0xE4;
    }
    r = func_0023CDF8(arg0, *(s32 *)(arg0 + 0xB48));
    if (r != -1) {
        return r;
    }
    if (func_00211310(arg0, 0xB, 1) != 0) {
        return 3;
    }
    if (func_00211310(arg0, 0xB, 4) != 0) {
        return 4;
    }
    if (func_00211310(arg0, 0xB, 0x10) != 0) {
        return 5;
    }
    if (func_00211310(arg0, 4, 0x200000) != 0) {
        return 0x9E;
    }
    if (func_00211310(arg0, 4, 0x400000) != 0) {
        return 0x3B;
    }
    if (func_00211310(arg0, 4, 0x4000) != 0) {
        return 0x3C;
    }
    if (func_00211310(arg0, 4, 0x8000) != 0) {
        return 0x3D;
    }
    if (func_00211310(arg0, 4, 0x10000) != 0) {
        return 0x3E;
    }
    if (func_00211310(arg0, 4, 0x20000) != 0) {
        return 0x3F;
    }
    if (func_00211310(arg0, 4, 0x40000) != 0) {
        return 0x40;
    }
    if (func_00211310(arg0, 4, 0x80000) != 0) {
        if ((func_0023F410(arg0) & 2) == 0) {
            return 0x43;
        }
        return 0x47;
    }
    if (func_00211310(arg0, 4, 0x10000000) != 0) {
        return 0x81;
    }
    if (func_00212820(arg0) == 0) {
        return -1;
    }
    if (func_00211310(arg0, 4, 0x20000000) != 0) {
        func_002113C0(arg0, 0, 2, 1);
        if (BtlPad_Test48(arg0, 0xE) != 0) {
            return 0x1C;
        }
        if (BtlPad_Test48(arg0, 0xF) == 0) {
            return 0x1F;
        }
        return 0x1D;
    }
    if (func_00211310(arg0, 4, 0x80000000) != 0) {
        func_002113C0(arg0, 0, 2, 1);
        if (BtlPad_Test48(arg0, 0xE) != 0) {
            return 0x1C;
        }
        if (BtlPad_Test48(arg0, 0xF) != 0) {
            return 0x1D;
        }
        if (BtlChar_FrameMod(2) == 0) {
            return 0x1D;
        }
        return 0x1C;
    }
    if (func_00211310(arg0, 4, 0x40000000) == 0) {
        return -1;
    }
    func_002113C0(arg0, 0, 2, 1);
    s2 = (BtlChar_FrameMod(2) == 0) ? 0x1D : 0x1C;
    s2b = (BtlPad_Test48(arg0, 0xE) != 0) ? 0x1C : s2;
    s2c = (BtlPad_Test48(arg0, 0xF) != 0) ? 0x1D : s2b;
    if (func_00212878() != 0) {
        return func_00217518(s2c, 0x5C);
    }
    return func_00217518(s2c, 0x5B);
}
