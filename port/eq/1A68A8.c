#include "common.h"

s32 BtlScene_IsEffectStopped(s32 a0, s32 a1);
void BtlTask_SetDead(s32 a0);
void EftTrail_UpdateTextures(s32 a0);
void Vec3_Add(void *a0, void *a1, void *a2);
void Vec3_Sub(void *a0, void *a1, void *a2);
void Vec3_Normalize(void *a0, void *a1);
void func_00129BB8(f32 f12, s32 a0, s32 a1);
void func_00129BD0(s32 a0, s32 a1, f32 f12);
void func_00129C28(s32 a0, s32 a1);
extern f32 D_00384E94;

void EftTrail_Update(u8 *arg0) {
    s32 sp[4];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    s32 cnt;
    s32 v1;
    s32 t;
    f32 f0;
    f32 f1;

    s2 = *(u8 **)(arg0 + 0x38);
    if (BtlScene_IsEffectStopped(*(s32 *)(s2 + 4), *(u8 *)(s2 + 8)) == 0) {
        if (!(*(s32 *)(s2 + 0x28) & 1)) {
            cnt = *(s32 *)(s2 + 0x1B0) - 1;
            if (cnt > 0) {
                s0 = s2 + cnt * 0x10;
                do {
                    cnt -= 1;
                    func_00129C28((s32)(s0 + 0x70), (s32)(s0 + 0x60));
                    s0 -= 0x10;
                } while (cnt > 0);
            }
            s1 = s2 + 0x40;
            Vec3_Sub(sp, *(u8 **)(s2 + 0x30), s1);
            s0 = s2 + 0x50;
            Vec3_Normalize(sp, sp);
            func_00129BD0((s32)sp, (s32)sp, *(f32 *)(s2 + 0x14));
            Vec3_Add(s0, s0, sp);
            Vec3_Normalize(s0, s0);
            func_00129BB8(*(f32 *)(s2 + 0xC), (s32)sp, (s32)s0);
            func_00129C28((s32)(s2 + 0x70), (s32)s1);
        }
        f0 = *(f32 *)(s2 + 0xC) + *(f32 *)(s2 + 0x10);
        *(f32 *)(s2 + 0xC) = f0;
        if (100.0f < f0) {
            *(f32 *)(s2 + 0xC) = 100.0f;
        }
        *(f32 *)(s2 + 0x14) = *(f32 *)(s2 + 0x14) + *(f32 *)(s2 + 0x18);
        v1 = *(s32 *)(s2 + 0x28);
        if (v1 & 1) {
            f0 = *(f32 *)(s2 + 0x20) / (f32)*(s32 *)(s2 + 0x2C);
            f1 = *(f32 *)(s2 + 0x1C) - f0;
            *(f32 *)(s2 + 0x1C) = f1;
            if (f1 <= D_00384E94) {
                BtlTask_SetDead((s32)arg0);
            }
        }
        t = *(s32 *)(s2 + 0x24);
        if (t >= 0) {
            t = t - 1;
            *(s32 *)(s2 + 0x24) = t;
            if (t <= 0) {
                BtlTask_SetDead((s32)arg0);
            }
        }
    }
    EftTrail_UpdateTextures((s32)s2);
}
