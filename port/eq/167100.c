#include "common.h"

typedef struct { u64 lo, hi; } q128;

s32 func_001F3758(s32 arg0);
s32 BtlScene_IsCharStopped(s32 arg0);
void func_00152530(s32 arg0, s32 arg1);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
s32 func_00208DE8(s32 a0, s32 a1, s32 a2);
s32 func_0012D3A0(u8 *arg0, s32 arg1, s32 arg2);
f32 func_0020A068(s32 arg0);
void func_00129C28(q128 *arg0, q128 *arg1);
void func_00129C38(u8 *arg0, u8 *arg1);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
void Vec3_Scale(u8 *arg0, u8 *arg1, f32 farg0);
void func_00151FB0(u8 *arg0);
void func_00166ED0(s32 arg0, u8 *arg1, s32 *arg2, s32 arg3);
s32 func_00152200(u8 *arg0, s32 arg1);
s32 BtlTask_SetDead(s32 arg0);

#define ADDR(p) ((s32)(u32)(p))

/* 0x00167100: effect shot task update. self+1 = phase (0..5), self+0x38 = shot data. */
void func_00167100(u8 *self) {
    u8 *shot = *(u8 **)(self + 0x38);
    s32 *flags = (s32 *)shot;
    s32 *eftp = *(s32 **)(shot + 0xB0);
    s32 owner = *(s32 *)(func_001F3758(ADDR(self)) + 0x38);
    s32 advance = 0;
    s32 ok;
    u8 *vecs;
    f32 a[4];
    f32 b[4];

    if (BtlScene_IsCharStopped(*eftp) != 0) {
        return;
    }
    func_00152530(ADDR(eftp), ADDR(shot + 0x860));
    if ((*flags & 0x80) == 0) {
        if (EftShot_TestBits(*eftp, 2) != 0) {
            self[1] = 0;
            *flags = *flags | 0x80;
        } else if (EftShot_TestBits(*eftp, 4) != 0) {
            self[1] = 2;
            *flags = *flags | 0x80;
        }
    }
    if ((*flags & 0x80) != 0 && self[1] < 6) {
        switch (self[1]) {
        case 0:
            if (EftShot_TestBits(*eftp, 2) != 0) {
                *(s32 *)(shot + 4) = *(s32 *)(shot + 0x870);
                func_00208DE8(*eftp, ADDR(shot + 0x40), *(s32 *)(shot + 4));
                func_0012D3A0(shot + 0x30, ADDR(shot + 0x40), *eftp);
                self[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            advance = 1;
            break;
        case 2:
            *(f32 *)(shot + 0x20) = func_0020A068(*eftp);
            *(f32 *)(shot + 0x18) = *(f32 *)(shot + 0x14) * (*(f32 *)(shot + 0x20) * 0.5f + 1.0f);
            func_00208DE8(*eftp, ADDR(shot + 0x40), *(s32 *)(shot + 4));
            if (EftShot_TestBits(*eftp, 0x40) != 0) {
                *(s32 *)(shot + 0xC) = *(s32 *)(shot + 0x9B0);
                func_00208DE8(*eftp, ADDR(shot + 0x60), *(s32 *)(shot + 0xC));
                *flags = *flags | 0x40;
            }
            if (EftShot_TestBits(*eftp, 4) != 0) {
                *flags = *flags | 0x10;
                *(s32 *)(shot + 8) = *(s32 *)(shot + 0x8B0);
                func_00208DE8(*eftp, ADDR(shot + 0x50), *(s32 *)(shot + 8));
                func_00129C28((q128 *)(shot + 0x70), (q128 *)(shot + 0x50));
                func_00129C28((q128 *)(shot + 0x80), (q128 *)(shot + 0x70));
                func_00208DE8(*eftp, ADDR(shot + 0x90), 0x11);
                __builtin_memset(a, 0, 16);
                a[3] = 1.0f;
                __builtin_memset(b, 0, 16);
                b[3] = 1.0f;
                func_00208DE8(*eftp, ADDR(a), 0x15);
                func_00208DE8(*eftp, ADDR(b), 0x14);
                Vec3_Sub(ADDR(shot + 0x30), ADDR(a), ADDR(b));
                Vec3_Normalize(ADDR(shot + 0x30), ADDR(shot + 0x30));
                Vec3_Scale(shot + 0xA0, shot + 0x30, *(f32 *)(shot + 0x10));
                self[1] = 3;
            }
            break;
        case 4:
            func_00129C28((q128 *)(shot + 0x90), (q128 *)(shot + 0x80));
            if ((*(s32 *)(*(u8 **)(*(u8 **)(shot + 0xB0) + 0x20) + 0x30) & 2) == 0) {
                if ((*flags & 0x20) != 0) {
                    func_00129C38(shot + 0x80, self + 0x10);
                } else {
                    Vec3_Add(ADDR(shot + 0x80), ADDR(shot + 0x80), ADDR(shot + 0xA0));
                }
            }
            func_00208DE8(*eftp, ADDR(shot + 0x50), *(s32 *)(shot + 8));
            if (EftShot_TestBits(*eftp, 8) != 0) {
                *flags = *flags | 9;
                self[1] = 5;
            }
            break;
        }
    }
    if (EftShot_TestBits(*eftp, 0x80) != 0) {
        if ((*flags & 8) == 0) {
            *flags = *flags | 4;
        }
        *flags = *flags | 1;
    }
    vecs = shot + 0xB4;
    func_00151FB0(vecs);
    func_00166ED0(*eftp, self, (s32 *)(u32)owner, 0);
    ok = func_00152200((u8 *)(u32)owner, ADDR(vecs)) != 0;
    if (advance != 0) {
        self[1] = self[1] + 1;
    }
    if (ok == 0) {
        if ((*flags & 2) != 0) {
            BtlTask_SetDead(ADDR(self));
            return;
        }
    }
    if ((*flags & 1) != 0) {
        *flags = *flags | 2;
    }
}
