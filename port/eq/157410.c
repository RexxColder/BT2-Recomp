#include "common.h"

s32 BtlScene_GetPackEntry(s32 arg0, s32 arg1);
s32 func_00207EC0(s32 arg0);

s32 func_00157410(u8 *arg0) {
    s32 var_a1;
    s32 var_s1;
    u8 *temp_v0;

    var_s1 = 0;
    if (*(s32 *)(*(u8 **)(arg0 + 0x20)) == 0x166) {
        if (func_00207EC0(*(s32 *)arg0) == 3) {
            var_s1 = BtlScene_GetPackEntry(*(s32 *)(arg0 + 0x1C), 0x23);
        }
        var_a1 = 0x24;
        if (func_00207EC0(*(s32 *)arg0) == 0x4B) {
            goto block_8;
        }
    } else {
        temp_v0 = *(u8 **)(arg0 + 0x1C);
        if (*(s32 *)(temp_v0 + 0xC) != *(s32 *)(temp_v0 + 8)) {
            var_a1 = 2;
block_8:
            var_s1 = BtlScene_GetPackEntry(*(s32 *)(arg0 + 0x1C), var_a1);
        }
    }
    return var_s1;
}
