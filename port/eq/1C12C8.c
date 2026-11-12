#include "common.h"

void func_001C12C8(u8 *arg0, u8 *arg1) {
    s64 sp0;
    s64 sp8;
    s64 sp10;
    s64 sp18;
    s64 sp20;
    s64 sp28;
    s64 sp30;
    s64 sp38;
    u8 *temp_a0;

    sp0 = *(s64 *)(arg1 + 0x00);
    sp8 = *(s64 *)(arg1 + 0x08);
    sp10 = *(s64 *)(arg1 + 0x10);
    sp18 = *(s64 *)(arg1 + 0x18);
    sp20 = *(s64 *)(arg1 + 0x20);
    sp28 = *(s64 *)(arg1 + 0x28);
    sp30 = *(s64 *)(arg1 + 0x30);
    sp38 = *(s64 *)(arg1 + 0x38);
    if (arg0 != 0) {
        temp_a0 = (u8 *)*(s32 *)(arg0 + 0x38);
        if (temp_a0 != 0) {
            *(s64 *)(temp_a0 + 0xA70) = sp0;
            *(s64 *)(temp_a0 + 0xA78) = sp8;
            *(s64 *)(temp_a0 + 0xA80) = sp10;
            *(s64 *)(temp_a0 + 0xA88) = sp18;
            *(s64 *)(temp_a0 + 0xA90) = sp20;
            *(s64 *)(temp_a0 + 0xA98) = sp28;
            *(s64 *)(temp_a0 + 0xAA0) = sp30;
            *(s64 *)(temp_a0 + 0xAA8) = sp38;
        }
    }
}
