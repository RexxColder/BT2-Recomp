#include "common.h"

void func_00113878(void *arg0, s32 arg1, s32 arg2);
void func_00113A18(void *arg0);

void func_00113CB8(u8 *arg0, s32 arg1, s32 arg2, s16 arg3) {
    u8 *s1;
    s32 s0;
    s32 v0;
    s32 v1;

    s1 = arg0;
    s0 = arg1 & 0xFF;
    *(s32 *)s1 = 1;
    func_00113878(s1 + 0xC, arg2, (s32)(s16)arg3);
    if (s0 != 0) {
        v1 = (0x200 - *(s16 *)(s1 + 0x10)) >> 1;
        v0 = (0x1C0 - *(s16 *)(s1 + 0x12)) >> 1;
        *(s16 *)(s1 + 8) = (s16)((u16)*(u16 *)(s1 + 0x10) + v1);
        *(s16 *)(s1 + 0xA) = (s16)((u16)*(u16 *)(s1 + 0x12) + v0);
        *(s16 *)(s1 + 4) = (s16)v1;
        *(s16 *)(s1 + 6) = (s16)v0;
    } else {
        *(s16 *)(s1 + 4) = 0;
        *(s16 *)(s1 + 6) = 0;
        *(s16 *)(s1 + 8) = (s16)(*(u16 *)(s1 + 0x10) - *(u16 *)(s1 + 0xC));
        *(s16 *)(s1 + 0xA) = (s16)(*(u16 *)(s1 + 0x12) - *(u16 *)(s1 + 0xE));
    }
    func_00113A18(s1 + 0x16);
}
