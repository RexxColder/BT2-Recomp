#include "common.h"

void func_002C32B0(s32 arg0, s32);
void func_002C32C8(s32 arg0);

s32 func_002C06B0(s32 arg0, s32 arg1) {
    s32 sp[4];
    s32 var_s1;
    s32 var_s2;
    s32 *temp_v0;
    u8 *var_s0;

    var_s0 = (u8 *)(arg0 + (arg1 * 0x74) + 0x1320);
    func_002C32B0((s32)sp, arg1);
    var_s1 = *(s32 *)(var_s0 + 0x20);
    var_s2 = *(s32 *)(var_s0 + 0x24);
    if (var_s1 == 0) {
        if (var_s2 != 0) {
            temp_v0 = (s32 *)*(s32 *)(var_s0 + 0x4);
            var_s1 = var_s2 + ((s32 (*)(s32, s32))(*(s32 *)(*(s32 *)temp_v0 + 0x24)))((s32)temp_v0, 1);
        }
    }
    var_s1 = (var_s1 < 0) ? 0x7FFFFFFF : var_s1;
    func_002C32C8((s32)sp);
    return var_s1;
}
