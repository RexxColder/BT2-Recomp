#include "common.h"

f32 Gsc_GetFloat(void);
s32 Gsc_GetInt(void);
void func_00261378(s32 arg0, s32 arg1);
void func_002613F8(s32 arg0, s32 arg1);
extern f32 D_003872D8;

s32 func_002A65D0(s32 arg0) {
    f32 v0[4];
    f32 v1[4];
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 e;
    f32 f;
    f32 k;
    s32 raw;
    s32 s0;

    if (arg0 != 0) {
        return 1;
    }
    raw = Gsc_GetInt();
    if (raw < 0) {
        return 1;
    }
    s0 = raw & 0xFFFF;

    a = Gsc_GetFloat();
    b = Gsc_GetFloat();
    c = Gsc_GetFloat();
    d = Gsc_GetFloat();
    e = Gsc_GetFloat();
    f = Gsc_GetFloat();
    k = D_003872D8;

    v0[0] = a;
    v0[1] = b;
    v0[2] = c;
    v0[3] = 1.0f;
    v1[0] = (d / 180.0f) * k;
    v1[1] = (e / 180.0f) * k;
    v1[2] = (f / 180.0f) * k;
    v1[3] = 1.0f;

    func_00261378(s0, (s32)v0);
    func_002613F8(s0, (s32)v1);
    return 1;
}
