#include "common.h"

void func_00129C28(void *arg0, void *arg1);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void Vec3_Add(void *arg0, void *arg1, void *arg2);
void func_0012D5D8(f32 farg0, f32 farg1, void *arg0, void *arg1, void *arg2, s32 arg3);
void func_00196B68(void *arg0, s32 arg1);
void func_00197030(void *arg0, s32 arg1, s32 arg2);
s32 func_0020B3D0(s32 arg0);

void func_00196048(u8 *arg0) {
    f32 sp[4];
    f32 sp10[4];
    u8 *s0 = arg0 + 0xAD0;
    s32 *s2p = *(s32 **)(s0 + 0x20);
    s32 cnt, v, v1;
    s64 flag;
    u8 *s2b, *s3b;

    cnt = *(s32 *)(arg0 + 0xB08) - 1;
    *(s32 *)(arg0 + 0xB08) = cnt;
    if (cnt > 0) {
        return;
    }
    v1 = *(s32 *)(arg0 + 0xAC0);
    *(s32 *)(arg0 + 0xB08) = 0;
    if (!(v1 & 1)) {
        *(s32 *)(arg0 + 0xAC0) = v1 | 1;
    }
    v = *(s32 *)(arg0 + 0xB70);
    if (v & 0x80) {
        func_00196B68(arg0, 0x80);
        v = *(s32 *)(arg0 + 0xB70) & ~0x80;
        *(s32 *)(arg0 + 0xB70) = v;
    }
    if (v & 0x100) {
        func_00196B68(arg0, 0x100);
        v = *(s32 *)(arg0 + 0xB70) & ~0x100;
        *(s32 *)(arg0 + 0xB70) = v;
    }
    if (v & 0x200) {
        func_00197030(arg0 + 0xB30, func_0020B3D0(*s2p), *(s32 *)(arg0 + 0xB04));
    }
    flag = *(s64 *)(arg0 + 0xB70);
    if ((flag & 0x202) == 2) {
        s2b = arg0 + 0xB50;
        s3b = arg0 + 0xB30;
        func_0012D5D8(*(f32 *)(s0 + 0x3C), *(f32 *)(s0 + 0x40), sp, s3b, s2b, *s2p);
        func_00129C28(s2b, sp);
        if (*(s32 *)(arg0 + 0xB70) & 0x400) {
            func_00129C28(arg0 + 0xB40, s3b);
        }
        func_00129BD0(sp10, s2b, *(f32 *)(s0 + 0x3C));
        Vec3_Add(s3b, s3b, sp10);
        *(s32 *)(arg0 + 0xB70) = *(s32 *)(arg0 + 0xB70) | 0x400;
    }
}
