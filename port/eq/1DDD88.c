#include "common.h"

void Vec3_Normalize(void *arg0, s32 arg1, s32 arg2, void *arg3);
extern void func_001DDA10(void);

s32 func_001DDD88(u8 *arg0, s32 arg1) {
    s32 temp_a2;
    s32 var_v0;
    u8 *temp_s0;

    var_v0 = 0;
    if (arg0 != NULL) {
        temp_a2 = **(s32 **)(arg0 + 0x28);
        if (temp_a2 == (s32)0x001DDA10u) {
            temp_s0 = *(u8 **)(arg0 + 0x38);
            if (*(s32 *)(temp_s0 + 0x40) & 1) {
                Vec3_Normalize(temp_s0 + 0x30, arg1, temp_a2, arg0);
                var_v0 = 1;
                *(f32 *)(temp_s0 + 0x3C) = 1.0f;
            }
        }
    }
    return var_v0;
}
