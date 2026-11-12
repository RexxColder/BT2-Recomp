#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);

s32 func_002CF170(u8 *arg0, s32 arg1) {
    s32 temp_v1;

    temp_v1 = *(s32 *)(arg0 + 0x58);
    if (temp_v1 == 0) {
        *(s32 *)(arg0 + 0x58) = arg1;
        return 0;
    }
    if (temp_v1 != arg1) {
        return func_002C2FF0((s32)arg0, 0xFF000207);
    }
    return 0;
}
