#include "common.h"

u8 *func_00208768(s32 arg0, s32 arg1);

void *func_00240F50(u8 *arg0, s32 arg1) {
    u8 *var_v0;

    var_v0 = func_00208768(*(s32 *)(arg0 + 0x1534), arg1);
    if (var_v0 != NULL) {
        var_v0 = *(u8 **)(var_v0 + 0x30);
    }
    return var_v0;
}
