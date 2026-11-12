#include "common.h"

s32 BtlScene_IsCharStopped(s32 arg0);
void BtlTask_SetDead(s32 arg0);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void func_00129C28(s32 arg0, s32 arg1);
void func_0012D5D8(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg1);
void func_00151FB0(s32 arg0);
s32 func_00152200(s32 arg0, s32 arg1);
void func_00152930(s32 arg0, s32 arg1);
void func_00190AB0(s32 arg0);
void func_00190CA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_00191238(u8 *arg0) {
    f32 f0;
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    s32 v1;

    s1 = *(u8 **)(arg0 + 0x38);
    s4 = *(u8 **)s1;
    if (BtlScene_IsCharStopped(*(s32 *)s4) != 0) {
        return;
    }
    if (*(f32 *)(s1 + 0x3C) <= 0.0f) {
        s3 = s1 + 0x820;
        func_00129C28((s32)(s1 + 0x830), (s32)s3);
        if (!(*(s32 *)(*(u8 **)(s4 + 0x20) + 0x30) & 2)) {
            v1 = *(s32 *)(s1 + 0x30);
            if (v1 & 0x20) {
            } else if (v1 & 0x40) {
            } else if (v1 & 0x200) {
                func_00129C28((s32)s3, (s32)(s1 + 0x50));
            } else {
                s2 = s1 + 0x840;
                if (*(f32 *)(*(u8 **)(s4 + 0x24) + 0x10) > 0.0f) {
                    s0 = s1 + 0x40;
                    func_0012D5D8(*(f32 *)(s1 + 0x2C), (s32)s0, (s32)s3, (s32)s0, *(s32 *)s4, *(f32 *)(*(u8 **)(s4 + 0x24) + 0x10));
                    s2 = s1 + 0x840;
                    func_00129BD0((s32)s2, (s32)s0, *(f32 *)(s1 + 0x2C));
                }
                Vec3_Add((s32)s3, (s32)s3, (s32)s2);
            }
        }
    }
    if (*(f32 *)(s1 + 0x3C) > 0.0f) {
        *(f32 *)(s1 + 0x3C) = *(f32 *)(s1 + 0x3C) - 1.0f;
    }
    v1 = *(s32 *)(s1 + 0x30);
    if (v1 & 0x400) {
        f0 = *(f32 *)(s1 + 0x34) - 1.0f;
        *(f32 *)(s1 + 0x34) = f0;
        if (f0 <= 0.0f) {
            *(s32 *)(s1 + 0x30) = v1 | 2;
        }
    }
    s0 = s1 + 0x60;
    if (EftShot_TestBits(*(s32 *)s4, 0x80) != 0) {
        *(s32 *)(s1 + 0x30) = *(s32 *)(s1 + 0x30) | 2;
    }
    func_00151FB0((s32)s0);
    func_00190CA8(*(s32 *)s4, (s32)arg0, *(s32 *)(s1 + 4), 0);
    v1 = *(s32 *)(s1 + 0x30);
    if (func_00152200(*(s32 *)(s1 + 4), (s32)s0) == 0 && (v1 & 4)) {
        BtlTask_SetDead((s32)arg0);
        return;
    }
    if (v1 & 2) {
        *(s32 *)(s1 + 0x30) = v1 | 4;
        return;
    }
    if (!(v1 & 0x80)) {
        func_00152930(*(s32 *)(s1 + 4), (s32)s0);
        func_00190AB0((s32)arg0);
    }
}
