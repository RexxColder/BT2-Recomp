#include "common.h"

void *BtlMember_GetActiveGauge(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
void EftAura_Command(s32 arg0, s32 arg1);
void EftAura_SetLevel(s32 arg0, f32 farg0);
void func_001DD030(s32 arg0);
void func_001DD130(s32 arg0);
s32 func_001FA3A8(s32 arg0);
s32 func_0020A758(s32 arg0);
s32 func_00210DD8(s32 arg0);
s32 func_00211288(s32 arg0);
s32 func_00212320(s32 arg0);
s32 func_0023F410(s32 arg0);
s32 func_0023F430(s32 arg0);
s32 func_002411E0(s32 arg0, s32 arg1);

void func_00203E58(u8 *arg0) {
    f32 f20;
    s64 s3;
    s64 s4;
    s64 s5;
    s64 v0_64;
    u8 *gauge;
    u8 *p1530;
    s32 v1;
    s32 s0;
    s32 s2;

    s3 = *(s64 *)(arg0 + 0x338);
    v0_64 = *(s64 *)(arg0 + 0x400);
    s5 = v0_64 & ~s3;
    s4 = s3 & ~v0_64;
    gauge = (u8 *)BtlMember_GetActiveGauge((s32)arg0);   /* asm: a0 sigue siendo arg0 (el nor va en otro registro) */
    v1 = *(s32 *)(gauge + 0x10);
    if (v1 <= 0) {
        f20 = 0.0f;
    } else {
        f20 = (f32)*(s32 *)(gauge + 0xC) / (f32)v1;
        if (f20 < 0.5f) {
            f20 = 0.0f;
        }
    }
    if (func_0023F410((s32)arg0) & 0x10) {
        f20 = 0.0f;
    }
    p1530 = (u8 *)*(s32 *)(arg0 + 0x1530);
    if (*(s32 *)(p1530 + 0xAF0) & 0x40000) {
        f20 = 1.0f;
    }
    if (func_0020A758(*(s32 *)(arg0 + 0x1534)) != 0) {
        s0 = func_001FA3A8(BtlObjXf_Update((s32)arg0));
        s2 = func_00212320((s32)arg0);
        if (s0 & 0x10) {
            if (func_002411E0(func_00211288(func_00210DD8((s32)arg0)), s2) & 0x4000) {
                f20 = 0.0f;
                EftAura_Command(*(s32 *)(arg0 + 0x1534), 7);
            }
        } else if (func_002411E0((s32)arg0, s2) & 0x2000) {
            f20 = 0.0f;
            EftAura_Command(*(s32 *)(arg0 + 0x1534), 7);
        }
    }
    if (s3 & 0x10000) {
        f20 = 0.0f;
        EftAura_Command(*(s32 *)(arg0 + 0x1534), 7);
    }
    if (0.0f < f20) {
        EftAura_Command(*(s32 *)(arg0 + 0x1534), 0);
        EftAura_SetLevel(*(s32 *)(arg0 + 0x1534), f20);
    } else {
        EftAura_Command(*(s32 *)(arg0 + 0x1534), 1);
    }
    if (func_0023F410((s32)arg0) & 0x10) {
        return;
    }
    if (s4 & 0x40) {
        EftAura_Command(*(s32 *)(arg0 + 0x1534), 2);
        if (func_0023F430((s32)arg0) & 0x100) {
            func_001DD030(*(s32 *)(arg0 + 0x1534));
        }
    }
    if (s5 & 0x40) {
        EftAura_Command(*(s32 *)(arg0 + 0x1534), 3);
        if (func_0023F430((s32)arg0) & 0x100) {
            func_001DD130(*(s32 *)(arg0 + 0x1534));
        }
    }
    if (s3 & 0x100) {
        EftAura_Command(*(s32 *)(arg0 + 0x1534), 4);
        if (func_0023F430((s32)arg0) & 0x100) {
            func_001DD130(*(s32 *)(arg0 + 0x1534));
        }
    }
}
