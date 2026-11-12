#include "common.h"

#define F32(p, off) (*(f32 *)((p) + (off)))
#define S32(p, off) (*(s32 *)((p) + (off)))
#define PTR(p, off) (*(u8 **)((p) + (off)))

extern u8 *gEftAuraPool;
extern u8 *D_0038777C;
extern f32 D_003849C8;
extern f32 D_003849CC;
extern f32 D_003849D0;

void EftAura_SpawnSparks(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00129C28(u8 *dst, u8 *src);
s32 func_00208DE8(s32 objId, u8 *out, s32 node);
void func_00129B58(u8 *a, u8 *b, u8 *c);
void func_00129BD0(u8 *out, u8 *v, f32 scale);
void func_00129B28(u8 *a, u8 *b, u8 *c);

void EftAura_StepSparks(u8 *arg0, s32 arg1) {
    u8 sp[0x30];
    u8 *s0;
    u8 *s1;
    u8 *s3;
    u8 *drift;
    f32 one = 1.0f;
    f32 k = D_003849C8;
    f32 t;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    s32 node;
    s32 flags;

    memset(sp, 0, 0x10);
    s0 = gEftAuraPool + 0x20;
    s1 = *(u8 **)s0;
    while (s1 != NULL) {
        if (s1[4] != arg1) {
            s0 = s1 + 0xA0;
        } else if (F32(s1, 0x8) < F32(s1, 0xC)) {
            s3 = s1 + 0x30;
            func_00129C28(s3, arg0 + (s1[5] << 4) + 0x330);
            node = S32(D_0038777C, (s1[5] << 3) + 0x4A8);
            if (node >= 0) {
                func_00208DE8(s1[4], sp + 0x10, node);
                func_00129B58(sp, sp + 0x10, s3);
                func_00129BD0(sp + 0x20, sp, F32(s1, 0x20));
                func_00129B28(s3, s3, sp + 0x20);
            }
            drift = s1 + 0x50;
            F32(s1, 0x3C) = one;
            func_00129BD0(sp + 0x20, s1 + 0x60, F32(s1, 0x1C));
            func_00129B28(drift, drift, sp + 0x20);
            t = F32(s1, 0x8) / F32(s1, 0xC);
            f1 = F32(s1, 0x1C) + F32(D_0038777C, 0x1D8) * t;
            F32(s1, 0x1C) = f1;
            F32(s1, 0x1C) = f1 * (F32(D_0038777C, 0x1DC) * t);
            func_00129B28(s3, s3, drift);
            F32(s1, 0x3C) = one;
            f2 = F32(s1, 0x10) + F32(s1, 0x14);
            F32(s1, 0x10) = f2;
            if (D_003849CC <= f2) {
                F32(s1, 0x10) = f2 - k;
            } else if (f2 <= D_003849D0) {
                F32(s1, 0x10) = f2 + k;
            }
            f3 = F32(s1, 0x8);
            f0 = F32(s1, 0xC) - f3;
            f2 = F32(D_0038777C, 0x1BC);
            if (!(f0 <= f2)) {
                if (F32(D_0038777C, 0x1B8) < f3) {
                    F32(s1, 0x8C) = 0.0f;
                }
            } else {
                flags = S32(s1, 0);
                if (!(flags & 1)) {
                    S32(s1, 0) = flags | 1;
                    F32(s1, 0x8C) = -F32(s1, 0x7C) / f2;
                }
            }
            f1 = F32(s1, 0x7C);
            f0 = f1 + F32(s1, 0x8C);
            F32(s1, 0x7C) = f0;
            if (f0 < 0.0f) {
                F32(s1, 0x7C) = 0.0f;
            }
            s0 = s1 + 0xA0;
            F32(s1, 0x8) = f3 + one;
        } else {
            EftAura_SpawnSparks(arg0, s1[4], s1[5], 1);
            *(u8 **)s0 = PTR(s1, 0xA0);
            PTR(s1, 0xA0) = PTR(gEftAuraPool, 0x1C);
            PTR(gEftAuraPool, 0x1C) = s1;
        }
        s1 = *(u8 **)s0;
    }
}
