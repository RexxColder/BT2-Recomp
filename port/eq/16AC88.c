#include "common.h"

u8 *func_001F3758(u8 *arg0);
s32 BtlScene_IsCharStopped(u8 *arg0);
s32 EftShot_TestBits(u8 *arg0, s32 arg1);
void func_00152530(u8 *arg0, u8 *arg1);
void func_00151FB0(u8 *arg0);
s32 func_00152200(u8 *arg0, u8 *arg1);
void func_00152930(u8 *arg0, u8 *arg1);
s32 BtlTask_SetDead(u8 *arg0);
void Vec3_Add(u8 *arg0, u8 *arg1, u8 *arg2);
void func_0012D5D8(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, f32 farg0, f32 farg1);
void func_00129BD0(u8 *arg0, u8 *arg1, f32 farg0);
void func_00129C28(u8 *arg0, u8 *arg1);
void func_00129C38(u8 *arg0, u8 *arg1);
void func_0012D3A0(u8 *arg0, u8 *arg1, u8 *arg2);
s32 func_0012D488(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);
s32 func_00208DE8(u8 *a0, u8 *a1, s32 a2);
f32 func_0020A068(u8 *arg0);
void func_0016A5A0(u8 *arg0);
void func_0016AA40(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
s32 func_0016A878(u8 *arg0);

/* 0x0016AC88: per-frame update of a shot effect task (sibling of 0x0014DC10, other offsets). task+0x38 = state S,
   S+0xB0 = shot object O. task[1] = phase. */
s32 func_0016AC88(u8 *task) {
    u8 sp[16];
    u8 *S = *(u8 **)(task + 0x38);
    u8 *O;
    u8 *own;
    u8 *prm;
    u8 *vec;
    u8 *vecA;
    u8 *vecB;
    u8 *vecC;
    u8 *vecE;
    u8 *tmp;
    s32 wait = 0;
    s32 r;
    s32 alive;
    u32 fl;
    f32 f0;
    f32 f13;

    own = *(u8 **)(func_001F3758(task) + 0x38);
    O = *(u8 **)(S + 0xB0);
    r = BtlScene_IsCharStopped(*(u8 **)O);
    if (r != 0) {
        return r;
    }
    func_00152530(O, S + 0x860);
    if ((*(u32 *)S & 0x80) == 0) {
        if (EftShot_TestBits(*(u8 **)O, 2) != 0) {
            task[1] = 0;
            *(u32 *)S |= 0x80;
        } else if (EftShot_TestBits(*(u8 **)O, 4) != 0) {
            task[1] = 2;
            *(u32 *)S |= 0x80;
        }
    }
    if ((*(u32 *)S & 0x80) != 0) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(*(u8 **)O, 2) != 0) {
                r = *(s32 *)(S + 0x870);
                *(s32 *)(S + 8) = r;
                func_00208DE8(*(u8 **)O, sp, r);
                func_00129C28(S + 0x40, sp);
                func_0012D3A0(S + 0x30, S + 0x40, *(u8 **)O);
                task[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            wait = 1;
            break;
        case 2:
            f0 = func_0020A068(*(u8 **)O);
            *(f32 *)(S + 0x20) = f0;
            *(f32 *)(S + 0x1C) = *(f32 *)(S + 0x18) * (f0 * 0.5f + 1.0f);
            func_00208DE8(*(u8 **)O, sp, *(s32 *)(S + 8));
            func_00129C28(S + 0x40, sp);
            if (EftShot_TestBits(*(u8 **)O, 0x40) != 0) {
                r = *(s32 *)(S + 0x9B0);
                *(s32 *)(S + 0x10) = r;
                func_00208DE8(*(u8 **)O, sp, r);
                func_00129C28(S + 0x60, sp);
                *(u32 *)S |= 0x40;
            }
            if (EftShot_TestBits(*(u8 **)O, 4) != 0) {
                r = *(s32 *)(S + 0x8B0);
                *(u32 *)S |= 0x10;
                *(s32 *)(S + 0xC) = r;
                vec = S + 0x50;
                vecA = S + 0x70;
                vecB = S + 0x80;
                vecC = S + 0x30;
                func_00208DE8(*(u8 **)O, sp, r);
                func_00129C28(vec, sp);
                func_00129C28(vecA, vec);
                func_00129C28(vecB, vecA);
                func_00208DE8(*(u8 **)O, S + 0x90, 0x11);
                func_0012D488(O, vecC, vecB, *(u8 **)O);
                func_00129BD0(S + 0xA0, vecC, *(f32 *)(S + 0x14));
                task[1] = 3;
            }
            break;
        case 4:
            vecB = S + 0x80;
            func_00129C28(S + 0x90, vecB);
            prm = *(u8 **)(*(u8 **)(S + 0xB0) + 0x20);
            if ((*(u32 *)(prm + 0x30) & 2) == 0) {
                if ((*(u32 *)S & 0x20) != 0) {
                    func_00129C38(vecB, task + 0x10);
                } else {
                    vecE = S + 0xA0;
                    f13 = *(f32 *)(prm + 0x18);
                    if (0.0f < f13) {
                        vecC = S + 0x30;
                        func_0012D5D8(vecC, vecB, vecC, *(u8 **)O, *(f32 *)(S + 0x14), f13);
                        func_00129BD0(vecE, vecC, *(f32 *)(S + 0x14));
                    }
                    Vec3_Add(vecB, vecB, vecE);
                }
            }
            func_00208DE8(*(u8 **)O, sp, *(s32 *)(S + 0xC));
            func_00129C28(S + 0x50, sp);
            if (EftShot_TestBits(*(u8 **)O, 8) != 0) {
                *(u32 *)S |= 9;
                task[1] = 5;
            }
            break;
        default:
            break;
        }
    }
    if (EftShot_TestBits(*(u8 **)O, 0x80) != 0) {
        fl = *(u32 *)S;
        if ((fl & 8) == 0) {
            fl = fl | 4;
        }
        *(u32 *)S = fl | 1;
    }
    func_0016A5A0(task);
    tmp = S + 0xB4;
    func_00151FB0(tmp);
    func_0016AA40(*(u8 **)O, task, own, 0);
    alive = func_00152200(own, tmp) != 0;
    if (wait != 0) {
        task[1] = task[1] + 1;
    }
    fl = *(u32 *)S;
    if (alive == 0 && (fl & 2) != 0) {
        return BtlTask_SetDead(task);
    }
    if ((fl & 1) != 0) {
        *(u32 *)S = fl | 2;
        return fl | 2;
    }
    if ((*(u32 *)(*(u8 **)(O + 0x20) + 0x30) & 1) != 0 && (fl & 0x10) != 0) {
        func_00152930(own, tmp);
        return func_0016A878(task);
    }
    return fl & 0x10;
}
