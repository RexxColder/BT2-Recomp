#include "common.h"

extern u8 *func_001F3758(void *a0);
extern s32 BtlScene_IsCharStopped(s32 arg0);
extern void func_00152530(u8 *arg0, u8 *arg1);
extern s32 EftShot_TestBits(s32 arg0, s32 arg1);
extern void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
extern void func_00129C28(void *arg0, void *arg1);
extern s32 func_0012D3A0(u8 *arg0, s32 arg1, s32 arg2);
extern f32 func_0020A068(s32 arg0);
extern s32 func_00175020(void *arg0);
extern void func_00151FB0(u8 *arg0);
extern void func_00174E40(s32 arg0, u8 *arg1, u8 *arg2, s32 arg3);
extern s32 func_00152200(u8 *arg0, u8 *arg1);
extern void func_00152930(u8 *arg0, u8 *arg1);
extern void func_00174C78(u8 *arg0);
extern void BtlTask_SetDead(void *arg0);

s32 func_00175538(u8 *task) {
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
                func_00208DE8(*(s32 *)obj, st + 0x40, *(s32 *)(st + 0x870));
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
            func_00208DE8(*(s32 *)obj, st + 0x40, *(s32 *)(st + 4));
            if (EftShot_TestBits(*(s32 *)obj, 0x40) != 0) {
                *(s32 *)(st + 0xC) = *(s32 *)(st + 0x9B0);
                func_00208DE8(*(s32 *)obj, st + 0x60, *(s32 *)(st + 0x9B0));
                *(s32 *)st |= 0x40;
            }
            if (EftShot_TestBits(*(s32 *)obj, 4) != 0) {
                *(s32 *)(st + 8) = *(s32 *)(st + 0x8B0);
                func_00208DE8(*(s32 *)obj, st + 0x50, *(s32 *)(st + 0x8B0));
                func_00129C28(st + 0x70, st + 0x50);
                func_00129C28(st + 0x80, st + 0x70);
                task[1] = 3;
            }
            break;
        case 4:
            func_00208DE8(*(s32 *)obj, st + 0x50, *(s32 *)(st + 8));
            if (EftShot_TestBits(*(s32 *)obj, 8) != 0) {
                *(s32 *)st |= 9;
                task[1] = 5;
            }
            break;
        default:
            break;
        }
    }
    done = func_00175020(task);
    flags = *(s32 *)st;
    if ((flags & 0x200) != 0 && done == 0) {
        *(s32 *)st = flags | 1;
    }
    ev = st + 0xB4;
    if (EftShot_TestBits(*(s32 *)obj, 0x80) != 0) {
        flags = *(s32 *)st;
        if ((flags & 8) == 0) {
            *(s32 *)st = flags | 4;
            flags |= 4;
        }
        *(s32 *)st = flags | 1;
    }
    func_00151FB0(ev);
    func_00174E40(*(s32 *)obj, task, other, 0);
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
        return flags | 2;
    }
    if ((*(s32 *)(*(u8 **)(obj + 0x20) + 0x30) & 1) != 0 && (flags & 0x10) != 0) {
        func_00152930(other, ev);
        func_00174C78(task);
    }
    return 0;
}
