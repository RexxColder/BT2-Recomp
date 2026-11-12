#include "m2c_macros.h"

extern s32 BtlPad_Test48(s32 arg0, s32 arg1);
extern s32 BtlPad_Test4C(s32 arg0, s32 arg1);
extern s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_00217518(s32 arg0, s32 arg1);
extern s32 func_0023D410(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_0023D4E0(s32 arg0, s32 arg1);
extern s32 func_002411E0(s32 arg0, s32 arg1);

s32 func_0023D600(s32 arg0) {
    s32 s1;
    s32 s2;
    s32 s3;

    if (BtlPad_Test48(arg0, 7) == 0) {
        return -1;
    }
    if (BtlPad_Test4C(arg0, 1) == 0) {
        return -1;
    }
    if (*(s32 *)(arg0 + 0xA34) > 0) {
        return -1;
    }
    s1 = 3;
    if (BtlPad_Test48(arg0, 0xC) == 0) {
        s1 = (BtlPad_Test48(arg0, 0xD) == 0) ? 2 : 4;
    }
    if (func_0023D4E0(arg0, s1) == 0) {
        return -1;
    }
    s3 = func_002411E0(arg0, s1);
    s2 = func_0023D410(arg0, s1, 0);
    s1 = -1;
    if (func_00211310(arg0, 1, 1) != 0) {
        s1 = (s3 & 0x10000000) ? -1 : 0x18;
    }
    if (s3 & 0x80000) {
        if (*(f32 *)(arg0 + 0xAC4) > 0.0f) {
            s1 = 0xD9;
        }
    }
    if (s1 != -1) {
        s2 = func_00217518(s1, s2);
    }
    return s2;
}
