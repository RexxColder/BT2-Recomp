#include "common.h"

u8 *StgRigid_Find(u8 *arg0);
s32 BtlStage_IsReady(u8 *arg0);
void func_003126C8(u8 *arg0, u8 *arg1);
f32 sceVu0InnerProduct(u8 *arg0, u8 *arg1);
s32 rand();
void Rigid_SetVelocity(u8 *arg0, u8 *arg1, u8 *arg2);
void memset(void *arg0, s32 arg1, u32 arg2);
extern f32 D_00386D58;

void StgRigid_LaunchSpin(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 sp[0x10];
    u8 *s0;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f20;
    s32 r;

    memset(sp, 0, 0x10);
    *(f32 *)(sp + 0xC) = 1.0f;
    s0 = StgRigid_Find(arg0);
    if (s0 == 0) {
        BtlStage_IsReady(sp);
        return;
    }

    func_003126C8(sp, arg1);
    *(s32 *)(sp + 0x4) = 0;
    f2 = sceVu0InnerProduct(sp, sp);
    f0 = 1200.0f;
    f1 = *(f32 *)(sp + 0x0);
    if (f0 < f2) {
        f2 = f0 / f2;
        f0 = *(f32 *)(sp + 0x8) * f2;
        f1 = f1 * f2;
        *(f32 *)(sp + 0x8) = f0;
        *(f32 *)(sp + 0x0) = f1;
    }

    r = rand();
    f20 = D_00386D58;
    f0 = -5.0f;
    f1 = (f32)r;
    f1 = f1 / f20;
    f1 = f1 * f0;
    f1 = f1 + f0;
    *(f32 *)(sp + 0x4) = f1;

    r = rand();
    if (r & 1) {
        r = rand();
        f0 = (f32)r / f20;
        f1 = *(f32 *)(sp + 0x0);
        f0 = f1 * f0;
        f1 = f1 + f0;
        *(f32 *)(sp + 0x0) = f1;
    }

    r = rand();
    if (r & 1) {
        r = rand();
        f0 = (f32)r / f20;
        f1 = *(f32 *)(sp + 0x4);
        f0 = f1 * f0;
        f1 = f1 + f0;
        *(f32 *)(sp + 0x4) = f1;
    }

    r = rand();
    if (r & 1) {
        r = rand();
        f0 = (f32)r / f20;
        f1 = *(f32 *)(sp + 0x8);
        f0 = f1 * f0;
        f1 = f1 + f0;
        *(f32 *)(sp + 0x8) = f1;
    }

    Rigid_SetVelocity(s0 + 0x10, sp, arg2);
}
