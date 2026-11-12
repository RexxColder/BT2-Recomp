#include "common.h"

void func_00122EC0(s32 arg0, s32 arg1, s32 arg2);
void func_00123CD8(s32 arg0, s32 arg1, s32 arg2);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_003126C8(s32 arg0, s32 arg1);
s32 rand(void);
extern u8 *D_003876FC;

s32 func_0011FBC8(u8 *arg0, s32 arg1) {
    s32 sp[4];
    s32 sp10[4];
    s32 sp20[4];
    u8 *temp_a3;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_s3;
    s32 temp_v1;
    s32 var_v0;
    u8 *temp_s0;
    u8 *temp_v0;

    temp_a3 = arg0 + 0x38;
    temp_a0 = *(s32 *)(temp_a3 + 0x108);
    var_v0 = 0;
    if (temp_a0 != *(s32 *)(temp_a3 + 0x10C)) {
        temp_a1 = temp_a0 + 1;
        temp_v1 = temp_a0 * 4;
        temp_v0 = arg0 + 0x40;
        temp_s3 = *(s32 *)(temp_v0 + temp_v1);
        *(s32 *)(temp_a3 + 0x108) = temp_a1;
        if (temp_a1 >= 0x20) {
            *(s32 *)(temp_a3 + 0x108) = 0;
        }
        var_v0 = 0;
        if (temp_s3 != -1) {
            *(s32 *)(temp_a3 + 0x11C) = arg1;
            *(s32 *)(temp_a3 + 4) = *(s32 *)(temp_v1 + temp_v0 + 0x80);
            *(s32 *)(arg0 + 0x38) = temp_s3;
            *(s32 *)(temp_a3 + 0x110) = 0;
            *(s32 *)(temp_a3 + 0x114) = 0;
            *(s32 *)(temp_a3 + 0x118) = 0;
            if (temp_s3 >= 0xFA) {
                if (temp_s3 < 0xFC) {
                    func_00208DE8(*(s32 *)arg0, (s32)sp, 3, (s32)temp_a3);
                    func_00123CD8((s32)arg0, (s32)sp, (s32)(arg0 + 0x10B0));
                    func_00122EC0((s32)arg0, temp_s3 != 0xFA, 1);
                } else if (temp_s3 < 0xFE) {
                    temp_s0 = *(u8 **)(D_003876FC + 0x10);
                    func_00208DE8(*(s32 *)arg0, (s32)sp10, 3, (s32)temp_a3);
                    func_003126C8((s32)sp20, *(s32 *)(temp_s0 + 0x48) + ((rand() % *(s32 *)(temp_s0 + 8)) * 0x10));
                    func_00123CD8((s32)arg0, (s32)sp10, (s32)sp20);
                    func_00122EC0((s32)arg0, temp_s3 != 0xFC, 0);
                }
            }
            var_v0 = 1;
        }
    }
    return var_v0;
}
