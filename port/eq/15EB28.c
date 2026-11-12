#include "common.h"

u8 *func_001F3758(u8 *arg0);
s32 BtlScene_IsCharStopped(u8 *arg0);
s32 EftShot_TestBits(u8 *arg0, s32 arg1);
void func_00152530(u8 *arg0, u8 *arg1);
void func_00151FB0(u8 *arg0);
s32 func_00152200(u8 *arg0, u8 *arg1);
void func_00152930(u8 *arg0, u8 *arg1);
s32 BtlTask_SetDead(u8 *arg0);
void func_00129C28(u8 *arg0, u8 *arg1);
void func_0012D3A0(u8 *arg0, u8 *arg1, u8 *arg2);
s32 func_0012D488(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);
s32 func_00208DE8(u8 *a0, u8 *a1, s32 a2);
f32 func_0020A068(u8 *arg0);
void func_0019D6B8(u8 *arg0, s32 arg1);
void func_0019D6E8(u8 *arg0);
s32 func_0019D808(u8 *arg0);
void func_0015E800(u8 *arg0, s32 arg1);
void func_0015E6A8(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
s32 func_0015E4E0(u8 *arg0);

/* 0x0015EB28: per-frame update of a multi-part shot effect task (S = task+0x38, O = S+0xC0). S+0x14 = part count,
   S+0xAC0 = part pointers. task[1] = phase (jtbl_0036E3A0). */
s32 func_0015EB28(u8 *task) {
    u8 sp[16];
    u8 *S = *(u8 **)(task + 0x38);
    u8 *O;
    u8 *own;
    u8 *tmp;
    s32 wait = 0;
    s32 r;
    s32 i;
    s32 alive;
    u32 fl;
    f32 f0;

    own = *(u8 **)(func_001F3758(task) + 0x38);
    O = *(u8 **)(S + 0xC0);
    r = BtlScene_IsCharStopped(*(u8 **)O);
    if (r != 0) {
        return r;
    }
    for (i = 0; i < *(s32 *)(S + 0x14); i++) {
        func_0019D6B8(*(u8 **)(S + 0xAC0 + i * 4), 0);
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
            *(f32 *)(S + 0x24) = f0;
            *(f32 *)(S + 0x20) = *(f32 *)(S + 0x1C) * (f0 + 1.0f);
            func_00208DE8(*(u8 **)O, sp, *(s32 *)(S + 4));
            func_00129C28(S + 0x40, sp);
            if (EftShot_TestBits(*(u8 **)O, 0x10) != 0) {
                func_00208DE8(*(u8 **)O, S + 0x60, 0x11);
            }
            if (EftShot_TestBits(*(u8 **)O, 0x20) != 0) {
                func_00208DE8(*(u8 **)O, S + 0x60, 0x11);
            }
            if (EftShot_TestBits(*(u8 **)O, 0x40) != 0) {
                func_00208DE8(*(u8 **)O, S + 0x60, 0x11);
            }
            if (EftShot_TestBits(*(u8 **)O, 4) != 0) {
                r = *(s32 *)(S + 0x8C0);
                *(s32 *)(S + 8) = r;
                func_00208DE8(*(u8 **)O, sp, r);
                func_00129C28(S + 0x50, sp);
                func_00129C28(S + 0x80, S + 0x50);
                func_00129C28(S + 0x90, S + 0x80);
                func_00208DE8(*(u8 **)O, S + 0xA0, 0x11);
                func_0012D488(O, S + 0x30, S + 0x90, *(u8 **)O);
                func_00129C28(S + 0xB0, S + 0x30);
                func_00208DE8(*(u8 **)O, S + 0x70, 0x15);
                func_0015E800(task, *(s32 *)(S + 0x10));
                r = *(s32 *)(S + 0x10) + 1;
                *(s32 *)(S + 0x10) = r;
                if (!(r < *(s32 *)(S + 0x14))) {
                    task[1] = 3;
                }
            }
            break;
        case 4:
            if (EftShot_TestBits(*(u8 **)O, 8) != 0) {
                *(u32 *)S |= 9;
                task[1] = 5;
            }
            i = 0;
            while (i < *(s32 *)(S + 0x14)) {
                if (func_0019D808(*(u8 **)(S + 0xAC0 + i * 4)) != 0) {
                    break;
                }
                i++;
            }
            *(u32 *)S |= 9;
            task[1] = 5;
            break;
        default:
            break;
        }
    }
    tmp = S + 0xC4;
    if (EftShot_TestBits(*(u8 **)O, 0x80) != 0) {
        fl = *(u32 *)S;
        if ((fl & 8) == 0) {
            *(u32 *)S = fl | 4;
            for (i = 0; i < *(s32 *)(S + 0x14); i++) {
                func_0019D6E8(*(u8 **)(S + 0xAC0 + i * 4));
            }
            fl = *(u32 *)S;
        }
        *(u32 *)S = fl | 1;
    }
    func_00151FB0(tmp);
    func_0015E6A8(*(u8 **)O, task, own, 0);
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
        return func_0015E4E0(task);
    }
    return fl & 0x10;
}
