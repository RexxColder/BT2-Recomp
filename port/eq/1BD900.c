#include "common.h"

void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void func_00129C28(s32 arg0, s32 arg1);
void func_00129C38(s32 arg0, s32 arg1);
void func_001BCD10(s32 arg0);

void func_001BD900(u8 *arg0, u8 *arg1) {
    u8 buf[0x40];
    u8 *s2;
    u8 *s6;

    if (*(f32 *)(arg1 + 0xC) <= (*(f32 *)(arg1 + 0x8) + (f32)*(u8 *)(*(u8 **)(arg0 + 0x38) + 8))) {
        func_001BCD10((s32)arg1);
    }
    func_00129C28((s32)buf, (s32)(arg1 + 0x40));
    func_00129C28((s32)(buf + 0x20), (s32)(arg1 + 0x60));
    s2 = *(u8 **)(arg1 + 0xE8);
    s6 = arg0 + 0x10;
    while (s2 != NULL) {
        func_00129C38((s32)(buf + 0x10), (s32)(s2 + 0x40));
        func_00129C38((s32)(s2 + 0x40), (s32)buf);
        func_00129C38((s32)buf, (s32)(buf + 0x10));
        Vec3_Add((s32)(s2 + 0x50), (s32)(s2 + 0x40), (s32)s6);
        func_00129C38((s32)(buf + 0x30), (s32)(s2 + 0x60));
        func_00129C38((s32)(s2 + 0x60), (s32)(buf + 0x20));
        func_00129C38((s32)(buf + 0x20), (s32)(buf + 0x30));
        s2 = *(u8 **)(s2 + 0xF0);
    }
}
