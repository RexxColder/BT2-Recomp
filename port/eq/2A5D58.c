#include "common.h"

s32 Gsc_FindOptionN(s32 arg0, s32 arg1);
f32 Gsc_GetFloat(void);
void func_002A3AF8(s32 arg0, f32 *arg1, f32 *arg2);
extern f32 D_003872CC;

s32 func_002A5D58(s32 arg0) {
    f32 raw[3];
    f32 scaled[3];
    f32 d;
    s32 s0;
    s32 idx;

    if (arg0 == 0) {
        d = D_003872CC;
        s0 = 0;
        while (Gsc_FindOptionN(0x70, s0) != 0) {
            raw[0] = Gsc_GetFloat();
            raw[1] = Gsc_GetFloat();
            raw[2] = Gsc_GetFloat();
            scaled[0] = (Gsc_GetFloat() / 180.0f) * d;
            scaled[1] = (Gsc_GetFloat() / 180.0f) * d;
            scaled[2] = (Gsc_GetFloat() / 180.0f) * d;
            idx = s0;
            s0 += 1;
            func_002A3AF8(idx, raw, scaled);
        }
    }
    return 1;
}
