#include "common.h"

void func_00129C38(u8 *arg0, u8 *arg1);
void func_001AC0A0(u8 *arg0, u8 *arg1);
void func_001AD520(u8 *arg0, u8 *arg1);

void func_001AD318(u8 *arg0) {
    s32 temp_v0;
    u8 *temp_s0;
    u8 *temp_s1;

    temp_s1 = *(u8 **)(arg0 + 0x38);
    if (*(s32 *)(temp_s1 + 0x11C) != -1) {
        temp_v0 = *(s32 *)(arg0 + 4);
        if (temp_v0 & 0x3F) {
            *(s32 *)(temp_s1 + 0xC4) = 0;
            if (!(*(s32 *)(temp_s1 + 0xC0) & 0x10)) {
                temp_s0 = temp_s1 + 0x50;
                func_00129C38(temp_s0, arg0 + 0x10);
                func_001AD520(arg0, temp_s0);
                *(s32 *)(temp_s1 + 0xC0) = (*(s32 *)(temp_s1 + 0xC0) | 0x10) & ~0x40 & ~0x80;
            }
        } else if ((temp_v0 & 0xC0) && !(*(s32 *)(temp_s1 + 0xC0) & 4)) {
            func_001AC0A0(arg0, temp_s1);
            *(f32 *)(temp_s1 + 0x50) = *(f32 *)(arg0 + 0x10);
            *(f32 *)(temp_s1 + 0x54) = *(f32 *)(arg0 + 0x14);
            *(s32 *)(temp_s1 + 0xC0) = *(s32 *)(temp_s1 + 0xC0) | 0x20;
            *(f32 *)(temp_s1 + 0x58) = *(f32 *)(arg0 + 0x18);
            *(s32 *)(arg0 + 4) = *(s32 *)(arg0 + 4) & ~0xC0;
        }
    }
}
