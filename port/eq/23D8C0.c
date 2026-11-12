#include "m2c_macros.h"

extern s32 BtlObjXf_Update(s32 arg0);
extern s32 BtlPad_Test48(s32 arg0, s32 arg1);
extern s32 BtlPad_Test4C(s32 arg0, s32 arg1);
extern s32 func_001FA3A8(s32 arg0);
extern s32 func_0023D740(s32 arg0, s32 arg1);
extern s32 func_00240FC8(s32 arg0, s32 arg1);
extern s32 func_00241F80(s32 arg0, s32 arg1);

s32 func_0023D8C0(s32 arg0) {
    s32 s1;
    s32 s2;
    s32 t;

    s2 = -1;
    if (BtlPad_Test48(arg0, 7) == 0) {
        return -1;
    }
    if (BtlPad_Test4C(arg0, 2) == 0) {
        return -1;
    }
    s1 = BtlPad_Test48(arg0, 0xC) != 0;
    if (func_0023D740(arg0, s1) == 0) {
        return -1;
    }
    if ((func_001FA3A8(BtlObjXf_Update(arg0)) & 0x10) != 0) {
        if ((func_00241F80(arg0, s1) & 8) == 0) {
            return -1;
        }
    }
    t = func_00240FC8(arg0, s1);
    if (t == 1) {
        s2 = s1 + 0xDC;
    } else if (t < 2) {
        if (t != 0) {
            return -1;
        }
        s2 = s1 + 0xDA;
    } else {
        if (t != 2) {
            return -1;
        }
        s2 = s1 + 0xDE;
    }
    return s2;
}
