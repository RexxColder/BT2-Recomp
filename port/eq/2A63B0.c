#include "common.h"

s32 Gsc_GetInt(void);
f32 Gsc_GetFloat(void);
void func_00261378(s32 arg0, s32 arg1);

s32 func_002A63B0(s32 arg0) {
    f32 sp[4];
    s32 temp_v0;

    if (arg0 == 0) {
        temp_v0 = Gsc_GetInt();
        if (temp_v0 >= 0) {
            sp[0] = Gsc_GetFloat();
            sp[1] = Gsc_GetFloat();
            sp[2] = Gsc_GetFloat();
            sp[3] = 1.0f;
            func_00261378(temp_v0 & 0xFFFF, (s32)sp);
        }
    }
    return 1;
}
