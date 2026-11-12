#include "common.h"

void Vec3_Normalize(s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void func_00129B28(s32 arg0, s32 arg1, s32 arg2);
void func_00129C28(s32 arg0, s32 arg1);
void func_001EADC8(s32 arg0);
void func_001EAE10(s32 arg0, s32 arg1);
void func_001EAEE0(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
void func_001EAFD0(s32 arg0, s32 arg1);
s32 func_001EB038(s32 arg0);
void func_001EB788(s32 arg0, s32 arg1, s32 arg2);
void *memset(void *s, s32 c, u32 n);

void func_001EB5C8(u8 *arg0) {
    u8 buf[0x20];
    u8 *s0;
    u8 *s2;

    s2 = *(u8 **)(arg0 + 4);
    memset(buf, 0, 0x10);
    memset(buf + 0x10, 0, 0x10);
    if (*(f32 *)(s2 + 0x11C) != 0.0f) {
        Vec3_Normalize((s32)(buf + 0x10), (s32)(arg0 + 0x20));
        func_00129BD0((s32)(buf + 0x10), (s32)(buf + 0x10), *(f32 *)(s2 + 0x11C));
        func_00129B28((s32)buf, (s32)(arg0 + 0x10), (s32)(buf + 0x10));
    } else {
        func_00129C28((s32)buf, (s32)(arg0 + 0x10));
    }

    s0 = *(u8 **)(arg0 + 0x64);
    if (s0 != NULL) {
        do {
            if (func_001EB038(*(s32 *)s0) == 0) {
                *(s32 *)(s0 + 4) = 0;
                func_001EB788((s32)(arg0 + 0x64), (s32)(arg0 + 0x68), (s32)s0);
            } else {
                func_001EAEE0(*(s32 *)s0, (s32)(arg0 + 0x68), (s32)s0, *(f32 *)(arg0 + 0x34));
                func_001EAFD0(*(s32 *)s0, (s32)(arg0 + 0x20));
                func_001EAE10(*(s32 *)s0, (s32)buf);
            }
            if (*(u16 *)(arg0 + 0x60) & 2) {
                func_001EADC8(*(s32 *)s0);
            }
            s0 = *(u8 **)(s0 + 8);
        } while (s0 != NULL);
    }
}
