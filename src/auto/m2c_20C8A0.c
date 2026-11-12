#include "m2c_macros.h"

extern void *D_00387E18;

s32  func_0020C8A0(void) {
    u8 var_v0;

    var_v0 = 0;
    if (D_00387E18 != NULL) {
        var_v0 = M2C_FIELD(D_00387E18, u8 *, 0xA);
    }
    return (u8)(var_v0);
}
