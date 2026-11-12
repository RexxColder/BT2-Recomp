#include "common.h"

void func_00129BD0(u8 *arg0, u8 *arg1, f32 farg0);
void func_00129C38();
s32 func_001CC978(u8 *arg0);
void func_001CCC68(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001CCD10(s32 arg0, s32 arg1);

void func_0019B198(u8 *arg0) {
    u8 sp[0x80];
    u8 *s1;
    u8 *s2;
    s32 v;

    s1 = *(u8 **)(arg0 + 0x38);
    s2 = *(u8 **)(s1 + 0x0);
    *(s32 *)(sp + 0x40) = *(s32 *)(s1 + 0x50);
    *(s32 *)(sp + 0x44) = *(u8 *)(s2 + 0x23);
    *(f32 *)(sp + 0x48) = *(f32 *)(s2 + 0x18);
    *(f32 *)(sp + 0x4C) = *(f32 *)(s2 + 0x1C);
    memset(sp + 0x50, 0, 0x10);
    memset(sp + 0x60, 0, 0x10);
    *(s32 *)(sp + 0x70) = *(s32 *)(s1 + 0x1C);
    *(s32 *)(sp + 0x74) = *(s32 *)(s1 + 0x20);
    *(s32 *)(sp + 0x78) = *(s32 *)(s1 + 0x24);
    *(s64 *)(sp + 0x30) = *(s64 *)(sp + 0x70);
    *(s64 *)(sp + 0x00) = *(s64 *)(sp + 0x40);
    *(s64 *)(sp + 0x08) = *(s64 *)(sp + 0x48);
    *(s64 *)(sp + 0x10) = *(s64 *)(sp + 0x50);
    *(s64 *)(sp + 0x18) = *(s64 *)(sp + 0x58);
    *(s64 *)(sp + 0x20) = *(s64 *)(sp + 0x60);
    *(s64 *)(sp + 0x28) = *(s64 *)(sp + 0x68);
    *(s64 *)(sp + 0x38) = *(s64 *)(sp + 0x78);
    func_00129C38(sp + 0x10, s1 + 0x30, *(s64 *)(sp + 0x78), *(s64 *)(sp + 0x60));
    func_00129C38(sp + 0x20, s1 + 0x40);
    if (*(u8 *)(s2 + 0x27) == 0) {
        func_00129BD0(sp + 0x20, sp + 0x20, -1.0f);
    }
    v = func_001CC978(sp);
    *(s32 *)(s1 + 0x28) = v;
    func_001CCC68(v, *(s32 *)(s1 + 0x1C), *(u8 *)(s2 + 0x23),
                  *(u8 *)(s2 + 0x23) + *(s32 *)(s1 + 0x54));
    func_001CCD10(*(s32 *)(s1 + 0x28), 2);
}
