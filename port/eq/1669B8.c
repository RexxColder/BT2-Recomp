#include "common.h"

extern u8 *func_001F3758(void *a0);
extern s32 BtlScene_IsCharStopped(s32 arg0);
extern void func_00152530(u8 *arg0, u8 *arg1);
extern s32 EftShot_TestBits(s32 arg0, s32 arg1);
extern void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
extern void func_00129C28(void *arg0, void *arg1);
extern s32 func_0012D3A0(u8 *arg0, s32 arg1, s32 arg2);
extern f32 func_0020A068(s32 arg0);
extern s32 func_00166580(void *arg0);
extern void func_00151FB0(u8 *arg0);
extern void func_00165F60(s32 a0, u8 *a1, u8 *a2, u8 a3);
extern s32 func_00152200(u8 *arg0, u8 *arg1);
extern void BtlTask_SetDead(void *arg0);

s32 func_001669B8(u8 *task) {
    u8 sp[16];
    u8 *st;
    u8 *obj;
    u8 *other;
    u8 *ev;
    s32 advance;
    s32 r;
    s32 done;
    s32 flags;
    f32 f;

    advance = 0;
    other = *(u8 **)(func_001F3758(task) + 0x38);
    st = *(u8 **)(task + 0x38);
    obj = *(u8 **)(st + 0xB0);
    r = BtlScene_IsCharStopped(*(s32 *)obj);
    if (r != 0) {
        return r;
    }
    func_00152530(obj, st + 0x860);
    if ((*(s32 *)st & 0x80) == 0) {
        if (EftShot_TestBits(*(s32 *)obj, 2) != 0) {
            task[1] = 0;
            *(s32 *)st |= 0x80;
        } else if (EftShot_TestBits(*(s32 *)obj, 4) != 0) {
            task[1] = 2;
            *(s32 *)st |= 0x80;
        }
    }
    if ((*(s32 *)st & 0x80) != 0) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(*(s32 *)obj, 2) != 0) {
                *(s32 *)(st + 4) = *(s32 *)(st + 0x870);
                func_00208DE8(*(s32 *)obj, sp, *(s32 *)(st + 0x870));
                func_00129C28(st + 0x40, sp);
                func_0012D3A0(st + 0x30, (s32)(st + 0x40), *(s32 *)obj);
                task[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            advance = 1;
            break;
        case 2:
            f = func_0020A068(*(s32 *)obj);
            *(f32 *)(st + 0x20) = f;
            *(f32 *)(st + 0x1C) = *(f32 *)(st + 0x18) * (f + 1.0f);
            func_00208DE8(*(s32 *)obj, sp, *(s32 *)(st + 4));
            func_00129C28(st + 0x40, sp);
            if (EftShot_TestBits(*(s32 *)obj, 0x40) != 0) {
                *(s32 *)(st + 0xC) = *(s32 *)(st + 0x9B0);
                func_00208DE8(*(s32 *)obj, sp, *(s32 *)(st + 0x9B0));
                func_00129C28(st + 0x60, sp);
                *(s32 *)st |= 0x40;
            }
            if (EftShot_TestBits(*(s32 *)obj, 4) != 0) {
                *(s32 *)(st + 8) = *(s32 *)(st + 0x8B0);
                func_00208DE8(*(s32 *)obj, sp, *(s32 *)(st + 0x8B0));
                func_00129C28(st + 0x50, sp);
                func_00129C28(st + 0x70, st + 0x50);
                func_00129C28(st + 0x80, st + 0x70);
                task[1] = 3;
            }
            break;
        case 4:
            func_00208DE8(*(s32 *)obj, sp, *(s32 *)(st + 8));
            func_00129C28(st + 0x50, sp);
            if (EftShot_TestBits(*(s32 *)obj, 8) != 0) {
                *(s32 *)st |= 9;
                task[1] = 5;
            }
            break;
        default:
            break;
        }
    }
    if (EftShot_TestBits(*(s32 *)obj, 0x80) != 0) {
        flags = *(s32 *)st;
        if ((flags & 8) == 0) {
            *(s32 *)st = flags | 4;
            flags |= 4;
        }
        *(s32 *)st = flags | 1;
    }
    done = func_00166580(task);
    ev = st + 0xB4;
    flags = *(s32 *)st;
    if ((flags & 0x400) != 0 && done == 0) {
        *(s32 *)st = flags | 1;
    }
    func_00151FB0(ev);
    func_00165F60(*(s32 *)obj, task, other, 0);
    r = func_00152200(other, ev) != 0;
    if (advance != 0) {
        task[1]++;
    }
    flags = *(s32 *)st;
    if (done == 0 && r == 0) {
        if ((flags & 2) != 0) {
            BtlTask_SetDead(task);
            return 0;
        }
    }
    if ((flags & 1) != 0) {
        *(s32 *)st = flags | 2;
    }
    return flags | 2;
}
