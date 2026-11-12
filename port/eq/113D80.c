#include "common.h"

void func_00113A18(s32 arg0);

void func_00113D80(u8 *arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_v1;

    *(s32 *)(arg0 + 0x0) = 1;
    if ((arg1 & 0xFF) != 0) {
        temp_a2 = (0x200 - *(s16 *)(arg0 + 0x10)) >> 1;
        temp_v1 = (0x1C0 - *(s16 *)(arg0 + 0x12)) >> 1;
        *(s16 *)(arg0 + 0x8) = (s16)((u16)*(s16 *)(arg0 + 0x10) + temp_a2);
        *(s16 *)(arg0 + 0xA) = (s16)((u16)*(s16 *)(arg0 + 0x12) + temp_v1);
        *(s16 *)(arg0 + 0x4) = (s16)temp_a2;
        *(s16 *)(arg0 + 0x6) = (s16)temp_v1;
    } else {
        *(s16 *)(arg0 + 0x8) = (s16)(*(u16 *)(arg0 + 0x10) - *(u16 *)(arg0 + 0xC));
        *(s16 *)(arg0 + 0x4) = 0;
        *(s16 *)(arg0 + 0xA) = (s16)(*(u16 *)(arg0 + 0x12) - *(u16 *)(arg0 + 0xE));
        *(s16 *)(arg0 + 0x6) = 0;
    }
    func_00113A18((s32)(arg0 + 0x16));
}
