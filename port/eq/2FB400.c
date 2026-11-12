#include "common.h"

u8 *func_002F95C8(s32 arg0, s32 arg1, s32 arg2);
void func_002F9B38(s32 arg0, s32 arg1, s32 arg2);

s64 func_002FB400(s32 arg0, s32 arg1, s32 arg2) {
    u8 buf[0x260];
    u8 *sp130;
    u8 *temp_v0;
    s64 (*temp_v1)(s32, s32, s32, s32);
    s64 r1;
    s64 r2;
    s64 temp_s0;
    s64 var_v0;

    sp130 = buf + 0x130;
    temp_v0 = func_002F95C8(arg0, arg1, arg2);
    var_v0 = 0;
    if (temp_v0 != 0) {
        func_002F9B38((s32)buf, (s32)sp130, arg0);
        var_v0 = 0;
        temp_v1 = (s64 (*)(s32, s32, s32, s32))(*(s32 *)(temp_v0 + 0x60));
        if (temp_v1 != 0) {
            r1 = temp_v1(arg0, 0xCC, (s32)sp130, arg1);
            temp_s0 = (s64)(u32)r1 << 32;
            r2 = temp_v1(arg0, 0xCD, (s32)sp130, arg1);
            var_v0 = temp_s0 + (s64)(u32)r2;
        }
    }
    return var_v0;
}
