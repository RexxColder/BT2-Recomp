#include "m2c_macros.h"

extern f32 D_003870F0;

s32 ColBox_HasVolume(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (!(M2C_FIELD(arg0, f32 *, 0xC) < (M2C_FIELD(arg0, f32 *, 0) + D_003870F0)) && !(M2C_FIELD(arg0, f32 *, 0x10) < (M2C_FIELD(arg0, f32 *, 4) + D_003870F0))) {
        var_v0 = 1;
        if (M2C_FIELD(arg0, f32 *, 0x14) < (M2C_FIELD(arg0, f32 *, 8) + D_003870F0)) {
            var_v0 = 0;
        }
    }
    return var_v0;
}
