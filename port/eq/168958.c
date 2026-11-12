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
void Vec3_Scale(u8 *arg0, u8 *arg1, f32 farg0);
s32 func_0020AB90(s32 arg0);
void EftTechEvt_RequestStop(s32 arg0);
void func_001681B0(s32 arg0);
void func_00151FB0(u8 *arg0);
void func_001686F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00152200(s32 arg0, s32 arg1);
s32 BtlTask_SetDead(s32 arg0);
void func_00152930(s32 arg0, s32 arg1);
void func_00168520(s32 arg0);

#define ADDR(p) ((s32)(u32)(p))

/* 0x00168958: effect shot task update (variant of 0x167100 with a stop request in phase 4). */
void func_00168958(u8 *self) {
    u8 *shot = *(u8 **)(self + 0x38);
    s32 *flags = (s32 *)shot;
    u8 *effect = *(u8 **)(shot + 0x120);
    s32 owner = *(s32 *)(func_001F3758(ADDR(self)) + 0x38);
    s32 advance = 0;
    s32 ok;
    u8 *vecs;

    if (BtlScene_IsCharStopped(*(s32 *)effect) != 0) {
        return;
    }
    func_00152530(ADDR(effect), ADDR(shot + 0x8D0));
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
                *(s32 *)(shot + 0xC) = *(s32 *)(shot + 0x8E0);
                func_00208DE8(*(s32 *)effect, ADDR(shot + 0xB0), *(s32 *)(shot + 0xC));
                func_0012D3A0(shot + 0xA0, ADDR(shot + 0xB0), *(s32 *)effect);
                self[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            advance = 1;
            break;
        case 2:
            *(f32 *)(shot + 0x28) = func_0020A068(*(s32 *)effect);
            *(f32 *)(shot + 0x20) = *(f32 *)(shot + 0x1C) * (*(f32 *)(shot + 0x28) * 0.5f + 1.0f);
            func_00208DE8(*(s32 *)effect, ADDR(shot + 0xB0), *(s32 *)(shot + 0xC));
            if (EftShot_TestBits(*(s32 *)effect, 0x40) != 0) {
                *(s32 *)(shot + 0x14) = *(s32 *)(shot + 0xA20);
                func_00208DE8(*(s32 *)effect, ADDR(shot + 0xD0), *(s32 *)(shot + 0x14));
                *flags = *flags | 0x40;
            }
            if (EftShot_TestBits(*(s32 *)effect, 4) != 0) {
                *(s32 *)(shot + 0x10) = 0x15;
                *flags = *flags | 0x10;
                func_00208DE8(*(s32 *)effect, ADDR(shot + 0xC0), 0x15);
                func_00129C28((q128 *)(shot + 0xE0), (q128 *)(shot + 0xC0));
                func_00129C28((q128 *)(shot + 0xF0), (q128 *)(shot + 0xE0));
                func_00208DE8(*(s32 *)effect, ADDR(shot + 0x100), 0x11);
                func_0012D3A0(shot + 0xA0, ADDR(shot + 0xF0), *(s32 *)effect);
                Vec3_Scale(shot + 0x110, shot + 0xA0, *(f32 *)(shot + 0x18));
                self[1] = 3;
            }
            break;
        case 4:
            if (EftShot_TestBits(*(s32 *)effect, 0x20) != 0) {
                *flags = *flags | 0x400;
            }
            if ((*flags & 0x400) == 0) {
                func_00129C28((q128 *)(shot + 0x100), (q128 *)(shot + 0xF0));
                func_00129C28((q128 *)(shot + 0xF0), (q128 *)(shot + 0x70));
            }
            if (func_0020AB90(*(s32 *)effect) != 0) {
                if ((*flags & 0x200) == 0) {
                    EftTechEvt_RequestStop(*(s32 *)effect);
                    *flags = *flags | 0x200;
                }
            }
            if (EftShot_TestBits(*(s32 *)effect, 8) != 0) {
                *flags = *flags | 9;
                self[1] = 5;
            }
            break;
        }
    }
    func_001681B0(ADDR(self));
    vecs = shot + 0x124;
    func_00151FB0(vecs);
    func_001686F0(*(s32 *)effect, ADDR(self), owner, 0);
    if (EftShot_TestBits(*(s32 *)effect, 0x80) != 0) {
        if ((*flags & 8) == 0) {
            *flags = *flags | 4;
        }
        *flags = *flags | 1;
    }
    ok = func_00152200(owner, ADDR(vecs)) != 0;
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
        func_00168520(ADDR(self));
    }
}
