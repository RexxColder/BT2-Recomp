#include "common.h"

void func_001CDBD8(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_003878C8;

void func_001CDDA8(s32 arg0) {
    u8 *var_s0;
    s32 temp_v0;
    u8 *temp_v1;

    if (D_003878C8 == 0) {
        return;
    }
    var_s0 = (u8 *)*(s32 *)(D_003878C8 + 0x210);
    while (var_s0 != 0) {
        if (*(s32 *)(var_s0 + 4) == arg0) {
            temp_v0 = *(s32 *)var_s0;
            if (temp_v0 == 0) {
                *(s32 *)var_s0 = 0;
                *(s32 *)(var_s0 + 8) = 0;
                func_001CDBD8((s32)(D_003878C8 + 0x210), (s32)(D_003878C8 + 0x214), (s32)var_s0);
                var_s0 = (u8 *)*(s32 *)(var_s0 + 0xC);
            } else {
                temp_v1 = (u8 *)*(s32 *)(temp_v0 + 0x38);
                if (temp_v1 != 0) {
                    *(u16 *)(temp_v1 + 0x12C) = (u16)(*(u16 *)(temp_v1 + 0x12C) | 2);
                }
                return;
            }
        } else {
            var_s0 = (u8 *)*(s32 *)(var_s0 + 0xC);
        }
    }
}
