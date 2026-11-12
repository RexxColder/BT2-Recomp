#include "common.h"

s32 func_003126C8(s32 arg0, s32 arg1, f32 farg0);
s32 func_0013B350(f32 *out);
void EftWater_AddSplash(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, f32 farg0);
extern u8 *D_003876A0;
extern s32 gEftDust;

s32 func_0013B608(s32 arg0, f32 farg0) {
    s32 sp[4];
    f32 sp10;
    s32 var_v0;

    var_v0 = 0;
    if (gEftDust != 0 && !(*(s64 *)(D_003876A0 + 0x4D8) & 2)) {
        func_003126C8((s32)sp, arg0, farg0);
        if (func_0013B350((s32)&sp10) != 0) {
            *(f32 *)&sp[1] = sp10 + -1.0f;
        }
        EftWater_AddSplash(gEftDust + 0x3C, gEftDust + 0x40, (s32)sp, 7, 4, 3, 2, farg0);
        var_v0 = 1;
    }
    return var_v0;
}
