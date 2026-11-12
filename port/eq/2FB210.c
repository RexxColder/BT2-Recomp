#include "common.h"

void func_002F9300(s32 arg0);
extern u8 D_0037DD58[] __attribute__((section(".data")));

s64 func_002FB210(u8 *arg0) {
    s64 var_s0;
    s64 temp_s0;
    s64 second;
    s64 (*temp_v0)(s32, s32, s32, s32);

    var_s0 = 0;
    if (arg0 == 0) {
        func_002F9300((s32)D_0037DD58);
        return 0;
    }
    temp_v0 = (s64 (*)(s32, s32, s32, s32))(*(s32 *)(*(s32 *)arg0 + 0x60));
    if (temp_v0 != 0) {
        temp_s0 = temp_v0(*(s32 *)(arg0 + 4), 0xC8, 0, 0);
        second = temp_v0(*(s32 *)(arg0 + 4), 0xC9, 0, 0);
        var_s0 = (s64)((u64)temp_s0 << 32) + (s64)(((u64)second << 32) >> 32);
    }
    return var_s0;
}
