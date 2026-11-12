#include "common.h"

extern s32 gEftDust;
extern u8 *D_003876A0;
void EftWaterTrail_Spawn(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_0013B408(s32 arg0, s32 arg1) {
    s32 t = gEftDust;

    if (t == 0) {
        return 0;
    }
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 2) != 0) {
        return 0;
    }
    EftWaterTrail_Spawn(t + 0x44, t + 0x48, arg0, arg1);
    return 1;
}
