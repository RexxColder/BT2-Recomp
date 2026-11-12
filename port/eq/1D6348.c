#include "m2c_macros.h"

extern u8 *D_00387E9C;
extern f32 D_003854E0;
u8 *func_001D62E8(void);
void func_00129C28(void *a0, void *a1);
f32 EftMath_WrapAngle(f32 angle);
f32 func_0012A3F8(f32 angle);
f32 Mathf_Cos(f32 angle);
s32 rand(void);

/* Takes an 0x80-byte particle from the pool (func_001D62E8), copies the two 16-byte vectors arg0 and arg1 into
 * it, sets the speed/alpha/life fields from the float arguments (life = f3 * 30, the sign of the start
 * direction comes from rand), and counts it in the pool's live-total at +0x1438. */
void EftParticle_Spawn(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4) {
    u8 frame[0x20];
    u8 *s;
    f32 ang;
    f32 sign;
    s32 r;

    *(u64 *)(frame + 0x08) = *(u64 *)(arg0 + 0x08);
    *(u64 *)(frame + 0x00) = *(u64 *)(arg0 + 0x00);
    *(u64 *)(frame + 0x10) = *(u64 *)(arg1 + 0x00);
    *(u64 *)(frame + 0x18) = *(u64 *)(arg1 + 0x08);

    s = func_001D62E8();
    if (s == NULL) {
        return;
    }
    func_00129C28(s, frame);
    func_00129C28(s + 0x10, frame + 0x10);

    *(f32 *)(s + 0x34) = f0;
    *(f32 *)(s + 0x38) = (f1 == 0.0f) ? 0.0f : 1.0f / f1;
    *(s32 *)(s + 0x3C) = 0;

    r = rand();
    sign = ((r & 1) != 0) ? -1.0f : 1.0f;
    *(f32 *)(s + 0x40) = sign;
    *(f32 *)(s + 0x60) = f3 * 30.0f;
    *(f32 *)(s + 0x5C) = 0.5f;
    *(u8 *)(s + 0x68) = 0x80;
    *(u8 *)(s + 0x69) = 0x80;
    *(u8 *)(s + 0x6A) = 0x80;
    *(u8 *)(s + 0x6B) = 1;
    *(u8 *)(s + 0x6C) = 0;
    *(u8 *)(s + 0x6D) = (u8)arg2;
    *(u8 *)(s + 0x6E) = (u8)arg3;
    *(u8 *)(s + 0x6F) = 1;
    *(u8 *)(s + 0x70) = 0;

    ang = EftMath_WrapAngle((f2 / 180.0f) * D_003854E0);
    *(f32 *)(s + 0x20) = func_0012A3F8(ang);
    *(f32 *)(s + 0x24) = Mathf_Cos(ang);
    *(s32 *)(s + 0x28) = 0;
    *(f32 *)(s + 0x64) = f4;
    *(f32 *)(s + 0x2C) = 1.0f;

    *(s32 *)(D_00387E9C + 0x1438) = *(s32 *)(D_00387E9C + 0x1438) + 1;
}
