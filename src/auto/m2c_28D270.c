#include "m2c_macros.h"

s32 ColNode_IsEmptyLeaf(void *arg0) {
    s32 temp_a0;
    s32 var_a1;

    temp_a0 = M2C_FIELD(arg0, s32 *, 0x1C);
    var_a1 = 0;
    if (temp_a0 == -1) {
        var_a1 = M2C_FIELD(arg0, s32 *, 0x18) == temp_a0;
    }
    return var_a1;
}
