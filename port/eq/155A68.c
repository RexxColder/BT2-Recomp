#include "common.h"

u8 *func_001F3758(u8 *arg0);
s32 BtlScene_IsCharStopped(u8 *arg0);
s32 EftShot_TestBits(u8 *arg0, s32 arg1);
void func_00152530(u8 *arg0, u8 *arg1);
void func_00151FB0(u8 *arg0);
s32 func_00152200(u8 *arg0, u8 *arg1);
s32 BtlTask_SetDead(u8 *arg0);
void func_00129BD0(u8 *arg0, u8 *arg1, f32 farg0);
void func_00129C28(u8 *arg0, u8 *arg1);
void func_0012D3A0(u8 *arg0, u8 *arg1, u8 *arg2);
s32 func_0012D488(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);
s32 func_00208DE8(u8 *a0, u8 *a1, s32 a2);
u8 *func_0020B3D0(u8 *arg0);
void func_001561C8(u8 *arg0);
void func_001567A8(u8 *arg0);
void func_00156738(u8 *arg0);
s32 func_00156548(u8 *arg0);
void func_001565D8(u8 *arg0);
void func_00156650(u8 *arg0);
void func_001566C8(u8 *arg0);
s32 func_001564B8(u8 *arg0);
void func_00156448(u8 *arg0);
void func_00155868(u8 *arg0, u8 *arg1, u8 *arg2);

/* 0x00155A68: per-frame update of a shot effect task (sibling of 0x0014DC10). task+0x38 = state S, S+0xA0 = shot O.
   task[1] = phase (switch through jtbl_0036E170). */
s32 func_00155A68(u8 *task) {
    u8 sp[16];
    u8 *S = *(u8 **)(task + 0x38);
    u8 *O;
    u8 *own;
    u8 *vecA;
    u8 *vecB;
    u8 *vecC;
    u8 *vecD;
    u8 *tmp;
    s32 wait = 0;
    s32 r;
    s32 alive;
    u32 fl;

    own = *(u8 **)(func_001F3758(task) + 0x38);
    O = *(u8 **)(S + 0xA0);
    r = BtlScene_IsCharStopped(*(u8 **)O);
    if (r != 0) {
        return r;
    }
    func_00152530(O, S + 0x850);
    if ((*(u32 *)S & 0x40) == 0) {
        if (EftShot_TestBits(*(u8 **)O, 2) != 0) {
            task[1] = 0;
            *(u32 *)S |= 0x40;
        } else if (EftShot_TestBits(*(u8 **)O, 4) != 0) {
            task[1] = 2;
            *(u32 *)S |= 0x40;
        }
    }
    if ((*(u32 *)S & 0x40) != 0) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(*(u8 **)O, 2) != 0) {
                vecA = S + 0x30;
                r = *(s32 *)(S + 0x860);
                *(s32 *)(S + 4) = r;
                func_00208DE8(*(u8 **)O, sp, r);
                func_00129C28(vecA, sp);
                func_0012D3A0(S + 0x20, vecA, *(u8 **)O);
                if (**(s32 **)(O + 0x20) == 0x6A) {
                    func_00208DE8(*(u8 **)O, sp, *(s32 *)(S + 4));
                    func_00129C28(S + 0x40, sp);
                    func_001561C8(task);
                    func_001567A8(task);
                }
                task[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            wait = 1;
            break;
        case 2:
            func_00208DE8(*(u8 **)O, sp, *(s32 *)(S + 4));
            func_00129C28(S + 0x30, sp);
            if (EftShot_TestBits(*(u8 **)O, 0x40) != 0) {
                r = *(s32 *)(S + 0x9A0);
                *(s32 *)(S + 0xC) = r;
                func_00208DE8(*(u8 **)O, sp, r);
                func_00129C28(S + 0x50, sp);
                *(u32 *)S |= 0x20;
            }
            if (EftShot_TestBits(*(u8 **)O, 4) != 0) {
                r = *(s32 *)(S + 0x8A0);
                *(u32 *)S |= 8;
                *(s32 *)(S + 8) = r;
                vecA = S + 0x40;
                vecB = S + 0x60;
                vecC = S + 0x70;
                vecD = S + 0x20;
                func_00208DE8(*(u8 **)O, sp, r);
                func_00129C28(vecA, sp);
                func_00129C28(vecB, vecA);
                func_00129C28(vecC, vecB);
                func_00129C28(S + 0x80, vecC);
                func_0012D488(O, vecD, vecC, *(u8 **)O);
                func_00129BD0(S + 0x90, vecD, *(f32 *)(S + 0x10));
                if (**(s32 **)(O + 0x20) == 0x6B) {
                    func_001561C8(task);
                    func_001561C8(task);
                    func_001561C8(task);
                }
                func_00156738(task);
                task[1] = 3;
            }
            break;
        case 4:
            if (func_00156548(task) != 0) {
                func_001565D8(task);
                *(u32 *)S |= 0x80;
            }
            if (EftShot_TestBits(*(u8 **)O, 0x10) != 0) {
                func_00156650(task);
            }
            if (EftShot_TestBits(*(u8 **)O, 0x20) != 0) {
                func_001566C8(task);
            }
            if (func_001564B8(task) == 0) {
                *(u32 *)S |= 1;
                task[1] = 5;
            }
            func_00208DE8(func_0020B3D0(*(u8 **)O), sp, 3);
            func_00129C28(S + 0x70, sp);
            func_00129C28(S + 0x80, sp);
            func_00208DE8(*(u8 **)O, sp, *(s32 *)(S + 8));
            func_00129C28(S + 0x40, sp);
            if ((*(u32 *)S & 0x80) == 0 && EftShot_TestBits(*(u8 **)O, 8) != 0) {
                func_001566C8(task);
                *(u32 *)S |= 1;
                task[1] = 5;
            }
            break;
        default:
            break;
        }
    }
    tmp = S + 0xA4;
    if (EftShot_TestBits(*(u8 **)O, 0x80) != 0) {
        *(u32 *)S |= 5;
    }
    func_00151FB0(tmp);
    func_00155868(*(u8 **)O, task, own);
    alive = func_00152200(own, tmp) != 0;
    if (wait != 0) {
        task[1] = task[1] + 1;
    }
    fl = *(u32 *)S;
    if (alive == 0 && (fl & 2) != 0) {
        func_00156448(task);
        return BtlTask_SetDead(task);
    }
    if ((fl & 1) != 0) {
        *(u32 *)S = fl | 2;
    }
    return fl | 2;
}
