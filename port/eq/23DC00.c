#include "common.h"

s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 func_0023F460(s32 arg0, s32 arg1);
void func_0023F4A8(s32 arg0, s32 arg1);
s32 func_0023F450(s32 arg0);
s32 func_0023F530(s32 arg0, s32 arg1);
s32 func_0023DAE8(s32 arg0, s32 arg1);
s32 func_0023D9D0(s32 arg0, s32 arg1);

s32 func_0023DC00(s32 arg0) {
    s32 s0;
    s32 s2;
    s32 t;
    s32 i;

    if (BtlPad_Test4C(arg0, 9) == 0) {
        return -1;
    }
    s2 = 0;
    for (i = 0; i < 4; i++) {
        if ((func_0023F460(arg0, i) ^ 0xFF) != 0) {
            s2++;
        }
    }
    for (i = 0; i < 3; i++) {
        func_0023F4A8(arg0, i);
    }

    if (BtlPad_Test48(arg0, 7) != 0) {
        s0 = (BtlPad_Test48(arg0, 0xE) != 0) ? 0 : -1;
        if (BtlPad_Test48(arg0, 0xC) != 0) {
            s0 = 1;
        }
        if (BtlPad_Test48(arg0, 0xF) != 0) {
            s0 = 2;
        }
        if (s0 < 0) {
            return -1;
        }
        if (func_0023DAE8(arg0, s0) == 0) {
            return -1;
        }
        t = func_0023F530(arg0, s0);
        if (s0 == 1) {
            return ((t ^ 1) != 0) ? 0x38 : 0x35;
        }
        if (s0 == 0) {
            return ((t ^ 1) != 0) ? 0x37 : 0x34;
        }
        if (s0 == 2) {
            return ((t ^ 1) != 0) ? 0x39 : 0x36;
        }
        return -1;
    }

    s0 = -1;
    if (s2 == 1) {
        s0 = func_0023F450(arg0);
    }
    if (s0 < 0) {
        if (BtlPad_Test48(arg0, 0xE) != 0) {
            s0 = 0;
        }
        if (BtlPad_Test48(arg0, 0xC) != 0) {
            s0 = 1;
        }
        if (BtlPad_Test48(arg0, 0xF) != 0) {
            s0 = 2;
        }
        if (BtlPad_Test48(arg0, 0xD) != 0) {
            s0 = 3;
        }
        if (BtlPad_Test48(arg0, 8) == 0) {
            s0 = func_0023F450(arg0);
        }
        if (s0 < 0) {
            return -1;
        }
    }
    if (func_0023D9D0(arg0, s0) == 0) {
        return -1;
    }
    if (s0 == 1) {
        return 0x2F;
    }
    if (s0 == 0) {
        return 0x2E;
    }
    if (s0 == 2) {
        return 0x30;
    }
    if (s0 == 3) {
        return 0x31;
    }
    return -1;
}
