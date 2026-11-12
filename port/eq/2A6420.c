#include "common.h"

f32 Gsc_GetFloat(void);
s32 Gsc_GetInt(void);
void func_002613F8(s32 arg0, void *arg1);
extern f32 D_003872D4;

s32 func_002A6420(s32 arg0) {
    f32 sp[4];
    f32 temp_f20;
    s32 temp_v0;

    if (arg0 == 0) {
        temp_v0 = Gsc_GetInt();
        if (temp_v0 >= 0) {
            temp_f20 = 180.0f;
            sp[0] = Gsc_GetFloat() / temp_f20 * D_003872D4;
            sp[1] = Gsc_GetFloat() / temp_f20 * D_003872D4;
            sp[2] = Gsc_GetFloat() / temp_f20 * D_003872D4;
            sp[3] = 1.0f;
            func_002613F8(temp_v0 & 0xFFFF, sp);
        }
    }
    return 1;
}
