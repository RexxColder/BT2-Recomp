#include "common.h"

s32 func_001E03E0(s32 arg0);

s32  func_001E0990(u8 *arg0) {
    u8 var_v0 = *(u8 *)(arg0 + 0x21E5);

    if (var_v0 != 0) {
        u8 temp_v0 = (u8)func_001E03E0((s32)arg0);

        *(u8 *)(arg0 + 0x21E5) = temp_v0;
        var_v0 = temp_v0;
    }
    return (u8)(var_v0);
}
