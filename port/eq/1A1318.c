#include "common.h"

extern u8 **D_0038780C;

f32 func_001A1318(s32 arg0) {
    f32 var_f0;
    u8 *temp_v0;

    var_f0 = 0.0f;
    temp_v0 = D_0038780C[arg0];
    if (temp_v0 != NULL) {
        var_f0 = *(f32 *) (*(u8 **) (temp_v0 + 0x38) + 0x44);
    }
    return var_f0;
}
