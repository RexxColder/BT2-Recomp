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
void func_0012D3A0(u8 *arg0, u8 *arg1, u8 *arg2);
s32 func_0012D488(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);
s32 func_00208DE8(u8 *a0, u8 *a1, s32 a2);
s32 func_0020AB90(u8 *arg0);
void func_00126DE0(u8 *arg0);
void func_001694E8(u8 *arg0);
void func_00169A30(u8 *arg0, u8 *arg1, u8 *arg2);
s32 func_00169868(u8 *arg0);

/* 0x00169D48: per-frame update of a shot effect task (S = task+0x38, O = S+0xB0), task[1] = phase (jtbl_0036E5B0).
   The "end" flag is 0x100 here (not 1). */
s32 func_00169D48(u8 *task) {
    u8 sp[0x30];
    u8 *S = *(u8 **)(task + 0x38);
    u8 *O;
    u8 *own;
    u8 *tmp;
    u8 *vA;
    u8 *vB;
    u8 *vC;
    u8 *vD;
    u8 *vE;
    u8 *prm;
    s32 wait = 0;
    s32 r;
    s32 alive;
    u32 fl;
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
                *(s32 *)(S + 0xC) = r;
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
            func_00208DE8(*(u8 **)O, sp, *(s32 *)(S + 0xC));
            func_00129C28(S + 0x40, sp);
            if (EftShot_TestBits(*(u8 **)O, 0x40) != 0) {
                r = *(s32 *)(S + 0x9B0);
                *(s32 *)(S + 0x14) = r;
                func_00208DE8(*(u8 **)O, sp, r);
                func_00129C28(S + 0x60, sp);
                *(u32 *)S |= 0x40;
            }
            if (EftShot_TestBits(*(u8 **)O, 4) != 0) {
                vA = S + 0x50;
                vB = S + 0x70;
                vC = S + 0x80;
                vD = S + 0x30;
                r = *(s32 *)(S + 0x8B0);
                *(u32 *)S |= 0x10;
                *(s32 *)(S + 0x10) = r;
                func_00208DE8(*(u8 **)O, sp, r);
                func_00129C28(vA, sp);
                func_00129C28(vB, vA);
                func_00129C28(vC, vB);
                func_00129C28(S + 0x90, vC);
                func_0012D488(O, vD, vC, *(u8 **)O);
                func_00129BD0(S + 0xA0, vD, *(f32 *)(S + 0x18));
                task[1] = 3;
            }
            break;
        case 4:
            vC = S + 0x80;
            func_00129C28(S + 0x90, vC);
            prm = *(u8 **)(*(u8 **)(S + 0xB0) + 0x20);
            if ((*(u32 *)(prm + 0x30) & 2) == 0 && (*(u32 *)S & 0x20) == 0) {
                vE = S + 0xA0;
                f13 = *(f32 *)(*(u8 **)(O + 0x24) + 0x10);
                if (0.0f < f13) {
                    vD = S + 0x30;
                    func_0012D5D8(vD, vC, vD, *(u8 **)O, *(f32 *)(S + 0x18), f13);
                    func_00129BD0(vE, vD, *(f32 *)(S + 0x18));
                }
                Vec3_Add(vC, vC, vE);
            }
            func_00208DE8(*(u8 **)O, sp, *(s32 *)(S + 0x10));
            func_00129C28(S + 0x50, sp);
            if (EftShot_TestBits(*(u8 **)O, 8) != 0) {
                *(u32 *)S |= 0x109;
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
        *(u32 *)S = fl | 0x100;
    }
    func_001694E8(task);
    tmp = S + 0xB4;
    func_00151FB0(tmp);
    func_00169A30(*(u8 **)O, task, own);
    if (func_0020AB90(*(u8 **)O) != 0 && (*(u32 *)S & 0x400) == 0) {
        *(s32 *)(sp + 0x20) = *(s32 *)(own + 0x1E84);
        *(s32 *)(sp + 0x24) = *(s32 *)O;
        *(s32 *)(sp + 0x28) = **(s32 **)(O + 0x20);
        __builtin_memcpy(sp + 0x10, sp + 0x20, 12);
        func_00126DE0(sp + 0x10);
        *(u32 *)S |= 0x400;
    }
    alive = func_00152200(own, tmp) != 0;
    if (wait != 0) {
        task[1] = task[1] + 1;
    }
    fl = *(u32 *)S;
    if (alive == 0 && (fl & 2) != 0) {
        return BtlTask_SetDead(task);
    }
    if ((fl & 0x100) != 0) {
        *(u32 *)S = fl | 2;
        return fl | 2;
    }
    if ((*(u32 *)(*(u8 **)(O + 0x20) + 0x30) & 1) != 0 && (fl & 0x10) != 0) {
        func_00152930(own, tmp);
        return func_00169868(task);
    }
    return fl & 0x10;
}
