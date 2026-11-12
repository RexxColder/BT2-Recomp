#include "common.h"

s32 Queue_AllocNode(s32 arg0);
s32 Queue_GetTail(s32 arg0);

s32 Queue_Push(s32 arg0, s32 arg1) {
    u8 *var_v0;
    u8 *temp_v0;

    var_v0 = (u8 *)Queue_AllocNode(arg0);
    if (var_v0 == 0) {
        return 0;
    }
    if (arg1 != 0) {
        *(s32 *)(var_v0 + 4) = arg1;
    }
    temp_v0 = (u8 *)Queue_GetTail(arg0);
    if (temp_v0 != 0) {
        *(u8 **)temp_v0 = var_v0;
    } else {
        *(u8 **)((u8 *)arg0 + 0xC) = var_v0;
    }
    *(s32 *)var_v0 = 0;
    return *(s32 *)(var_v0 + 4);
}
