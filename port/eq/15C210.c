#include "common.h"

typedef struct { u64 lo, hi; } q128;

s32 func_001F3758(s32 arg0);
s32 BtlScene_IsCharStopped(s32 arg0);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
s32 func_00208DE8(s32 a0, s32 a1, s32 a2);
s32 func_0012D3A0(u8 *arg0, s32 arg1, s32 arg2);
void func_00129C28(q128 *arg0, q128 *arg1);
void func_0015C7A8(u8 *arg0);
s32 func_0012D488(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
void Vec3_Scale(u8 *arg0, u8 *arg1, f32 farg0);
void func_0015C9F0(s32 arg0);
void func_0012D5D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void EftShot_BitTableUpdate2(s32 arg0, u8 *arg1);
void func_00151FB0(u8 *arg0);
void func_0015C038(s32 arg0, u8 *arg1, s32 *arg2);
s32 func_00152200(s32 arg0, s32 arg1);
void func_0015C980(s32 arg0);
s32 BtlTask_SetDead(s32 arg0);

#define ADDR(p) ((s32)(u32)(p))

/* 0x0015C210: effect shot task update (variant with 0x40 as "started" flag, node 0x2E). */
void func_0015C210(u8 *self) {
    u8 *shot = *(u8 **)(self + 0x38);
    s32 *flags = (s32 *)shot;
    u8 *effect = *(u8 **)(shot + 0xA0);
    s32 eft = *(s32 *)effect;
    s32 owner = *(s32 *)(func_001F3758(ADDR(self)) + 0x38);
    s32 advance = 0;
    s32 ok;
    u8 *vecs;
    f32 tmp[4];
    f32 limit;

    if (BtlScene_IsCharStopped(eft) != 0) {
        return;
    }
    if ((*flags & 0x40) == 0) {
        if (EftShot_TestBits(eft, 2) != 0) {
            self[1] = 0;
            *flags = *flags | 0x40;
        } else if (EftShot_TestBits(eft, 4) != 0) {
            self[1] = 2;
            *flags = *flags | 0x40;
        }
    }
    if ((*flags & 0x40) != 0 && self[1] < 6) {
        switch (self[1]) {
        case 0:
            if (EftShot_TestBits(eft, 2) != 0) {
                *(s32 *)(shot + 4) = 0x2E;
                func_00208DE8(eft, ADDR(tmp), 0x2E);
                func_00129C28((q128 *)(shot + 0x30), (q128 *)tmp);
                func_0012D3A0(shot + 0x20, ADDR(shot + 0x30), eft);
                self[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            advance = 1;
            break;
        case 2:
            if (EftShot_TestBits(eft, 0x10) != 0) {
                func_0015C7A8(self);
            }
            func_00208DE8(eft, ADDR(tmp), *(s32 *)(shot + 4));
            func_00129C28((q128 *)(shot + 0x30), (q128 *)tmp);
            if (EftShot_TestBits(eft, 0x40) != 0) {
                *(s32 *)(shot + 0xC) = 0x2E;
                func_00208DE8(eft, ADDR(tmp), 0x2E);
                func_00129C28((q128 *)(shot + 0x50), (q128 *)tmp);
                *flags = *flags | 0x20;
            }
            if (EftShot_TestBits(eft, 4) != 0) {
                *(s32 *)(shot + 8) = 0x2E;
                *flags = *flags | 8;
                func_00208DE8(eft, ADDR(tmp), 0x2E);
                func_00129C28((q128 *)(shot + 0x40), (q128 *)tmp);
                func_00129C28((q128 *)(shot + 0x60), (q128 *)(shot + 0x40));
                func_00129C28((q128 *)(shot + 0x70), (q128 *)(shot + 0x60));
                func_00129C28((q128 *)(shot + 0x80), (q128 *)(shot + 0x70));
                func_0012D488(effect, shot + 0x20, ADDR(shot + 0x70), eft);
                Vec3_Scale(shot + 0x90, shot + 0x20, *(f32 *)(shot + 0x10));
                func_0015C9F0(ADDR(self));
                self[1] = 3;
            }
            break;
        case 4:
            func_00129C28((q128 *)(shot + 0x80), (q128 *)(shot + 0x70));
            if ((*(s32 *)(*(u8 **)(*(u8 **)(shot + 0xA0) + 0x20) + 0x30) & 2) == 0 && (*flags & 0x10) == 0) {
                limit = *(f32 *)(*(u8 **)(effect + 0x24) + 0x10);
                if (0.0f < limit) {
                    func_0012D5D8(ADDR(shot + 0x20), ADDR(shot + 0x70), ADDR(shot + 0x20), eft,
                                  *(f32 *)(shot + 0x10), limit);
                    Vec3_Scale(shot + 0x90, shot + 0x20, *(f32 *)(shot + 0x10));
                }
                Vec3_Add(ADDR(shot + 0x70), ADDR(shot + 0x70), ADDR(shot + 0x90));
            }
            func_00208DE8(*(s32 *)effect, ADDR(tmp), *(s32 *)(shot + 8));
            func_00129C28((q128 *)(shot + 0x40), (q128 *)tmp);
            if (EftShot_TestBits(*(s32 *)effect, 8) != 0) {
                *flags = *flags | 1;
                self[1] = 5;
            }
            break;
        }
    }
    if (EftShot_TestBits(*(s32 *)effect, 0x80) != 0) {
        *flags = *flags | 5;
    }
    EftShot_BitTableUpdate2(*(s32 *)effect, shot + 0x850);
    vecs = shot + 0xA4;
    func_00151FB0(vecs);
    func_0015C038(*(s32 *)effect, self, (s32 *)(u32)owner);
    ok = func_00152200(owner, ADDR(vecs)) != 0;
    if (advance != 0) {
        self[1] = self[1] + 1;
    }
    if (ok == 0) {
        if ((*flags & 2) != 0) {
            func_0015C980(ADDR(self));
            BtlTask_SetDead(ADDR(self));
            return;
        }
    }
    if ((*flags & 1) != 0) {
        *flags = *flags | 2;
    }
}
