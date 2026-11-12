#include "common.h"

typedef struct { u64 lo, hi; } q128;

s32 func_001F3758(s32 arg0);
s32 BtlScene_IsCharStopped(s32 arg0);
void func_00152530(s32 arg0, s32 arg1);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
s32 func_00208DE8(s32 a0, s32 a1, s32 a2);
s32 func_001714C0(s32 arg0);
f32 func_0020A068(s32 arg0);
void func_001715C0(s32 arg0);
void func_00171380(u8 *arg0);
void func_001712E8(s32 arg0);
void func_00171590(s32 arg0);
void Vec3_Normalize(s32 arg0, s32 arg1);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Scale(u8 *arg0, u8 *arg1, f32 farg0);
void func_001715D0(u8 *arg0);
void func_00129C28(q128 *arg0, q128 *arg1);
void func_00129C38(u8 *arg0, u8 *arg1);
void func_0012D5D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1);
void func_00171348(void *arg0);
void func_00151FB0(u8 *arg0);
void func_00170B00(s32 arg0, u8 *arg1, s32 *arg2, s32 arg3);
s32 func_00152200(s32 arg0, s32 arg1);
void func_00171838(u8 *arg0, u8 *arg1);
s32 func_001E7178(s32 *arg0);
s32 BtlTask_SetDead(s32 arg0);
void func_00152930(s32 arg0, s32 arg1);
void func_00170A10(s32 arg0);
extern f32 D_003848B8;

#define ADDR(p) ((s32)(u32)(p))

/* 0x00170D40: effect shot task update (variant of 0x167100 using helper routines per phase). */
void func_00170D40(u8 *self) {
    u8 *shot = *(u8 **)(self + 0x38);
    s32 *flags = (s32 *)shot;
    u8 *effect = *(u8 **)(shot + 0xB0);
    s32 owner = *(s32 *)(func_001F3758(ADDR(self)) + 0x38);
    s32 advance = 0;
    s32 ok;
    u8 *vecs;

    if (BtlScene_IsCharStopped(*(s32 *)effect) != 0) {
        return;
    }
    func_00152530(ADDR(effect), ADDR(shot + 0x860));
    if ((*flags & 0x80) == 0) {
        if (EftShot_TestBits(*(s32 *)effect, 2) != 0) {
            self[1] = 0;
            *flags = *flags | 0x80;
        } else if (EftShot_TestBits(*(s32 *)effect, 4) != 0) {
            self[1] = 2;
            *flags = *flags | 0x80;
        }
    }
    if ((*flags & 0x80) != 0 && self[1] < 6) {
        switch (self[1]) {
        case 0:
            if (EftShot_TestBits(*(s32 *)effect, 2) != 0) {
                func_001714C0(ADDR(shot));
                self[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            advance = 1;
            break;
        case 2:
            *(f32 *)(shot + 0x20) = func_0020A068(*(s32 *)effect);
            *(f32 *)(shot + 0x18) = *(f32 *)(shot + 0x14) * (*(f32 *)(shot + 0x20) * 0.5f + 1.0f);
            func_001715C0(ADDR(shot));
            func_00208DE8(*(s32 *)effect, ADDR(shot + 0x40), *(s32 *)(shot + 4));
            if (EftShot_TestBits(*(s32 *)effect, 0x40) != 0) {
                *(s32 *)(shot + 0xC) = *(s32 *)(shot + 0x9B0);
                func_00208DE8(*(s32 *)effect, ADDR(shot + 0x60), *(s32 *)(shot + 0xC));
                *flags = *flags | 0x40;
            }
            if (EftShot_TestBits(*(s32 *)effect, 4) != 0) {
                func_00171380(shot);
                func_001712E8(ADDR(shot));
                Vec3_Normalize(ADDR(shot + 0x30), ADDR(shot + 0x30));
                Vec3_Scale(shot + 0xA0, shot + 0x30, *(f32 *)(shot + 0x10));
                func_00171380(shot);
                func_00171590(ADDR(shot));
                self[1] = 3;
            }
            break;
        case 4:
            func_001715D0(shot);
            func_00129C28((q128 *)(shot + 0x90), (q128 *)(shot + 0x80));
            if ((*(s32 *)(*(u8 **)(*(u8 **)(shot + 0xB0) + 0x20) + 0x30) & 2) == 0) {
                if ((*flags & 0x20) != 0) {
                    func_00129C38(shot + 0x80, self + 0x10);
                } else {
                    func_0012D5D8(ADDR(shot + 0x30), ADDR(shot + 0x80), ADDR(shot + 0x30),
                                  *(s32 *)effect, *(f32 *)(shot + 0x10), D_003848B8);
                    func_00171348(shot);
                    Vec3_Scale(shot + 0xA0, shot + 0x30, *(f32 *)(shot + 0x10));
                    Vec3_Add(ADDR(shot + 0x80), ADDR(shot + 0x80), ADDR(shot + 0xA0));
                }
            }
            func_00208DE8(*(s32 *)effect, ADDR(shot + 0x50), *(s32 *)(shot + 8));
            if (EftShot_TestBits(*(s32 *)effect, 8) != 0) {
                *flags = *flags | 9;
                self[1] = 5;
            }
            break;
        }
    }
    if (EftShot_TestBits(*(s32 *)effect, 0x80) != 0 || (*flags & 0x200) != 0) {
        if ((*flags & 8) == 0) {
            *flags = *flags | 4;
        }
        *flags = *flags | 1;
    }
    vecs = shot + 0xB4;
    func_00151FB0(vecs);
    func_00170B00(*(s32 *)effect, self, (s32 *)(u32)owner, 0);
    ok = func_00152200(owner, ADDR(vecs)) != 0;
    func_00171838((u8 *)(u32)owner, shot);
    func_001E7178((s32 *)(shot + 0xABC));
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
    } else if ((*(s32 *)(*(u8 **)(effect + 0x20) + 0x30) & 1) != 0 && (*flags & 0x10) != 0) {
        func_00152930(owner, ADDR(vecs));
        func_00170A10(ADDR(self));
    }
}
