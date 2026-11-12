#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
s32 dpdiv(s32 arg0, s64 arg1);
f32 dptofp(s32 arg0);
s32 fptodp(f32 arg0);
void func_001DC5C0(void *arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern s64 D_0036F1D8;
extern u8 *D_003878D0;

void func_001DC268(void *arg0, void *arg1) {
    s32 temp_a1;
    s32 var_v0;
    u8 *temp_s0;
    u8 *temp_s3;

    temp_s0 = D_003878D0;
    temp_s3 = *(u8 **)((u8 *)arg0 + 0x38);
    memset(temp_s3, 0, 0x250);
    *(s32 *)(temp_s3 + 0) = *(s32 *)((u8 *)arg1 + 0);
    *(u8 **)(temp_s3 + 4) = temp_s0 + 8;
    *(s32 *)(temp_s3 + 8) = *(s32 *)(temp_s0 + 0x114);
    *(s32 *)(temp_s3 + 0xC) = *(s32 *)(temp_s0 + 0x118);
    *(s32 *)(temp_s3 + 0x244) = *(s32 *)((u8 *)arg1 + 8);
    *(f32 *)(temp_s3 + 0x248) =
        dptofp(dpdiv(fptodp(BtlCharApi_GetHeight(*(s32 *)((u8 *)arg1 + 8))), D_0036F1D8));
    *(u16 *)(temp_s3 + 0x24C) = (u16)(*(u16 *)(temp_s3 + 0x24C) | 1);
    temp_a1 = *(s32 *)((u8 *)arg1 + 4);
    if (temp_a1 != 2) {
        var_v0 = -1;
        if (temp_a1 >= 2) {
            var_v0 = -1;
            if (temp_a1 < 6) {
                if (temp_a1 < 4) {
                    var_v0 = -1;
                } else {
                    goto block_6;
                }
            }
        }
    } else {
block_6:
        var_v0 = 6;
    }
    *(s32 *)(temp_s3 + 0x240) = var_v0;
    func_001DC5C0(arg0, temp_a1);
}
