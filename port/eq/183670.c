#include "common.h"

void ColSphere_Set(f32 farg0, s32 arg0, s32 arg1);
s32 EftHit_GetNew(void);
void EftHit_SetShapeSpheres(s32 arg0, s32 arg1, s32 arg2);
void func_00127128(s32 arg0);
s32 func_00127F88(s32 arg0);

void func_00183670(u8 *arg0) {
    u8 sp[16];
    u8 *s2;
    u8 *s3;
    u8 *a0p;
    f32 f20;
    s32 s0;
    s32 s1;

    s2 = *(u8 **)(arg0 + 0x38);
    s3 = (u8 *)EftHit_GetNew();
    *(s32 *)(s3 + 0x60) = (s32)arg0;
    a0p = s2 + 0xA10;
    *(s64 *)(s3 + 0x10) = *(s64 *)(s2 + 0xA60);
    *(s64 *)(s3 + 0x18) = *(s64 *)(s2 + 0xA68);
    *(s64 *)(s3 + 0x20) = *(s64 *)(s2 + 0xA70);
    *(s64 *)(s3 + 0x28) = *(s64 *)(s2 + 0xA78);
    *(s64 *)(s3 + 0x30) = *(s64 *)(s2 + 0xA80);
    *(s64 *)(s3 + 0x38) = *(s64 *)(s2 + 0xA88);
    *(s64 *)(s3 + 0x40) = *(s64 *)(s2 + 0xA90);
    *(s64 *)(s3 + 0x48) = *(s64 *)(s2 + 0xA98);
    *(s32 *)(s3 + 0x64) = *(s32 *)(a0p + 0x44);
    if (*(u8 *)(s2 + 0xA5C) != 0) {
        *(s32 *)(s3 + 0x50) = *(s32 *)(s3 + 0x50) | 0x10;
    }
    f20 = *(f32 *)(a0p + 0x2C);
    s1 = func_00127F88((s32)a0p);
    s0 = func_00127F88(0);
    *(f32 *)(sp + 0x0) = *(f32 *)(s2 + 0xA70);
    *(f32 *)(sp + 0x4) = *(f32 *)(s2 + 0xA74) - *(f32 *)(s2 + 0xB20);
    *(f32 *)(sp + 0x8) = *(f32 *)(s2 + 0xA78);
    *(f32 *)(sp + 0xC) = 1.0f;
    ColSphere_Set(f20, s1, (s32)sp);
    *(f32 *)(sp + 0x0) = *(f32 *)(s2 + 0xA80);
    *(f32 *)(sp + 0x4) = *(f32 *)(s2 + 0xA84) - *(f32 *)(s2 + 0xB20);
    *(f32 *)(sp + 0x8) = *(f32 *)(s2 + 0xA88);
    *(f32 *)(sp + 0xC) = 1.0f;
    ColSphere_Set(f20, s0, (s32)sp);
    EftHit_SetShapeSpheres((s32)s3, s1, s0);
    func_00127128((s32)s3);
}
