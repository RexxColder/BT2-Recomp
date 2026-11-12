#include "common.h"

s32 func_002D1070(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if ((*(s32 *)((u8 *)arg0 + 0x48) == 4) && (*(s32 *)((u8 *)arg0 + 0x50) == 0)) {
        var_v0 = *(s32 *)((u8 *)arg0 + 0x950 + 0x20) == 0;
    }
    return var_v0;
}
