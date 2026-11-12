#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_00387760;

s32 func_00148440(s32 arg0, s32 arg1, void *arg2) {
    f32 temp_f1;
    s32 temp_a0;
    s32 var_v0;
    u8 *temp_a2;
    u8 *temp_s1;
    u8 *temp_s3;

    if (D_00387760 == NULL) {
        return 0;
    }
    temp_s1 = *(u8 **)(D_00387760 + 4) + arg0 * 0x270;
    temp_s3 = temp_s1 + arg1 * 0x50;
    memset(temp_s3, 0, 0x50);
    var_v0 = 0;
    if (arg2 != NULL) {
        *(u8 **)(temp_s3 + 0x24) = temp_s1 + arg1 * 0x14 + 0x1E0;
        *(void **)(temp_s3 + 0x1C) = arg2;
        temp_a0 = *(s32 *)((u8 *)arg2 + 4);
        temp_a2 = (u8 *)arg2 + (((u32)temp_a0 >> 2) * 4);
        if ((*(s32 *)((u8 *)arg2 + 8) - temp_a0) <= 0) {
            *(void **)(temp_s3 + 0x1C) = NULL;
            return 0;
        }
        *(u8 **)(temp_s3 + 0x20) = temp_a2;
        temp_f1 = *(f32 *)(temp_a2 + 0x18);
        var_v0 = 1;
        if (temp_f1 != 0.0f) {
            *(f32 *)(temp_a2 + 0x18) = temp_f1 / 30.0f;
        }
        return var_v0;
    }
    return var_v0;
}
