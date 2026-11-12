#include "common.h"

void func_001BFC00(s32 arg0, s32 arg1, s32 arg2, s64 arg3, f32 farg0, f32 farg1);
void func_001C0228(s32 arg0, s32 arg1, s32 arg2);

void func_001C02C0(s32 *arg0, u8 *arg1) {
    u8 *var_s0;
    s32 temp_v0;

    var_s0 = (u8 *)*arg0;
    if (var_s0 != 0) {
        do {
            if (*(s32 *)(var_s0 + 0xE8) != 0) {
                func_001C0228((s32)arg0, (s32)arg1, (s32)var_s0);
            } else {
                func_001BFC00((s32)arg0, (s32)var_s0, (s32)(var_s0 + 0x70),
                              *(s64 *)(*(u8 **)(arg1 + 0x34) + (*(s32 *)(arg1 + 0x30) * 0x10)),
                              *(f32 *)(var_s0 + 0x28), *(f32 *)(var_s0 + 0x28));
            }
            temp_v0 = *(s32 *)(var_s0 + 0xE0);
            var_s0 = (u8 *)temp_v0;
        } while (temp_v0 != 0);
    }
}
