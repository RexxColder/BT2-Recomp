#include "common.h"

extern u8 *gBtlCamView;

u8 *func_001F3758(u8 *arg0);
s32 BtlScene_IsCharStopped(u8 *arg0);
s32 EftShot_TestBits(u8 *arg0, s32 arg1);
void func_00152530(u8 *arg0, u8 *arg1);
void func_00151FB0(u8 *arg0);
s32 func_00152200(u8 *arg0, u8 *arg1);
void func_00152930(u8 *arg0, u8 *arg1);
s32 BtlTask_SetDead(u8 *arg0);
void EftCam_StopIfRunning(void);
void func_00129BD0(u8 *arg0, u8 *arg1, f32 farg0);
void func_00129C28(u8 *arg0, u8 *arg1);
void func_00129B28(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec3_Sub(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec3_Normalize(u8 *arg0, u8 *arg1);
void func_0012D3A0(u8 *arg0, u8 *arg1, u8 *arg2);
s32 func_00208DE8(u8 *a0, u8 *a1, s32 a2);
f32 func_0020A068(u8 *arg0);
u8 *func_0020B3D0(u8 *arg0);
s32 func_0020AB90(u8 *arg0);
void func_00126DE0(u8 *arg0);
void func_00175C18(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
void func_00175FD0(u8 *arg0);
s32 func_00175A50(u8 *arg0);

/* 0x00176140: per-frame update of a shot effect task (S = task+0x38, O = S+0xC0), task[1] = phase (jtbl_0036E7A0). */
s32 func_00176140(u8 *task) {
    u8 sp[0x30];
    u8 *S = *(u8 **)(task + 0x38);
    u8 *O;
    u8 *own;
    u8 *tmp;
    u8 *vA;
    u8 *vB;
    u8 *vC;
    s32 wait = 0;
    s32 r;
    s32 alive;
    u32 fl;
    f32 f0;

    own = *(u8 **)(func_001F3758(task) + 0x38);
    O = *(u8 **)(S + 0xC0);
    r = BtlScene_IsCharStopped(*(u8 **)O);
    if (r != 0) {
        return r;
    }
    func_00152530(O, S + 0x870);
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
                r = *(s32 *)(S + 0x880);
                *(s32 *)(S + 4) = r;
                func_00208DE8(*(u8 **)O, S + 0x40, r);
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
            *(f32 *)(S + 0x24) = f0;
            *(f32 *)(S + 0x1C) = *(f32 *)(S + 0x18) * (f0 * 0.5f + 1.0f);
            func_00208DE8(*(u8 **)O, S + 0x40, *(s32 *)(S + 4));
            if (EftShot_TestBits(*(u8 **)O, 0x40) != 0) {
                r = *(s32 *)(S + 0x9C0);
                *(s32 *)(S + 0xC) = r;
                func_00208DE8(*(u8 **)O, S + 0x60, r);
                *(u32 *)S |= 0x40;
            }
            if (EftShot_TestBits(*(u8 **)O, 4) != 0) {
                vA = S + 0x50;
                vB = S + 0x80;
                vC = S + 0x90;
                r = *(s32 *)(S + 0x8C0);
                *(s32 *)(S + 8) = r;
                func_00208DE8(*(u8 **)O, vA, r);
                func_00129C28(vB, vA);
                func_00129C28(vC, vB);
                func_00129C28(S + 0x70, vB);
                func_00208DE8(*(u8 **)O, S + 0xA0, 0x11);
                func_0012D3A0(S + 0x30, vC, *(u8 **)O);
                func_00129BD0(S + 0xB0, S + 0x30, *(f32 *)(S + 0x14));
                task[1] = 3;
                *(u32 *)S |= 0x200;
            }
            break;
        case 4:
            vA = sp + 0x10;
            vB = sp + 0x20;
            func_00208DE8(func_0020B3D0(*(u8 **)O), vA, 3);
            func_00129C28(vB, gBtlCamView + 0x1F0);
            Vec3_Sub(sp, vB, vA);
            Vec3_Normalize(sp, sp);
            func_00129BD0(sp, sp, 3.0f);
            func_00129B28(S + 0x90, vA, sp);
            if (EftShot_TestBits(*(u8 **)O, 8) != 0) {
                *(u32 *)S |= 9;
                task[1] = 5;
            }
            break;
        default:
            break;
        }
    }
    if (func_0020AB90(*(u8 **)O) != 0 && (*(u32 *)S & 0x400) == 0) {
        *(s32 *)(sp + 0x10) = *(s32 *)(own + 0x1E80);
        *(s32 *)(sp + 0x14) = *(s32 *)O;
        *(s32 *)(sp + 0x18) = **(s32 **)(O + 0x20);
        __builtin_memcpy(sp, sp + 0x10, 12);
        func_00126DE0(sp);
        *(u32 *)S |= 0x400;
    }
    if (EftShot_TestBits(*(u8 **)O, 0x80) != 0) {
        fl = *(u32 *)S;
        if ((fl & 8) == 0) {
            fl = fl | 4;
        }
        *(u32 *)S = fl | 1;
    }
    tmp = S + 0xC4;
    func_00151FB0(tmp);
    func_00175C18(*(u8 **)O, task, own, 0);
    func_00175FD0(task);
    alive = func_00152200(own, tmp) != 0;
    if (wait != 0) {
        task[1] = task[1] + 1;
    }
    fl = *(u32 *)S;
    if (alive == 0 && (fl & 2) != 0) {
        return BtlTask_SetDead(task);
    }
    if ((fl & 1) != 0) {
        if ((fl & 0x400) != 0) {
            EftCam_StopIfRunning();
            fl = *(u32 *)S;
        }
        *(u32 *)S = fl | 2;
        return fl | 2;
    }
    if ((*(u32 *)(*(u8 **)(O + 0x20) + 0x30) & 1) != 0 && (fl & 0x10) != 0) {
        func_00152930(own, tmp);
        return func_00175A50(task);
    }
    return fl & 0x10;
}
