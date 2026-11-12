#include "common.h"

u8 *func_001F3758(s32 arg0);
s32 BtlScene_IsCharStopped(s32 arg0);
void func_00152530(s32 arg0, s32 arg1);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
s32 func_00208DE8(s32 a0, s32 a1, s32 a2);
s32 func_0012D3A0(u8 *arg0, s32 arg1, s32 arg2);
void func_00129C28(u8 *arg0, u8 *arg1);
s32 func_0012D488(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3);
void Vec3_Scale(u8 *arg0, u8 *arg1, f32 farg0);
void func_00159988(u8 *arg0);
void ColSeg_Set(s32 arg0, s32 arg1, s32 arg2);
s32 func_0011E1C8(s32 arg0);
void func_00159678(u8 *arg0);
void func_00151FB0(u8 *arg0);
void func_00159C98(s32 arg0, void *arg1, s32 *arg2);
s32 func_00152200(u8 *arg0, s32 arg1);
s32 func_001597E0(u8 *arg0);
s32 BtlTask_SetDead(s32 arg0);
void func_00152930(s32 arg0, s32 arg1);
void func_00159B80(s32 arg0);

s32 func_00159E80(u8 *task) {
    u8 sp[32];
    s32 advance = 0;
    u8 *obj;
    u8 *owner;
    u8 *player;
    s32 stopped;
    s32 flags;
    s32 gone;
    s32 dead;
    s32 updated;

    player = func_001F3758(0);
    obj = *(u8 **)(task + 0x38);
    owner = *(u8 **)(player + 0x38);
    player = *(u8 **)(obj + 0xA0);
    stopped = BtlScene_IsCharStopped(*(s32 *)player);
    if (stopped != 0) {
        return stopped;
    }
    func_00152530((s32)player, (s32)(obj + 0x850));
    if ((*(s32 *)obj & 0x40) == 0) {
        if (EftShot_TestBits(*(s32 *)player, 2) != 0) {
            task[1] = 0;
            *(s32 *)obj |= 0x40;
        } else if (EftShot_TestBits(*(s32 *)player, 4) != 0) {
            task[1] = 2;
            *(s32 *)obj |= 0x40;
        }
    }
    if ((*(s32 *)obj & 0x40) != 0) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(*(s32 *)player, 2) != 0) {
                *(s32 *)(obj + 4) = *(s32 *)(obj + 0x860);
                func_00208DE8(*(s32 *)player, (s32)(obj + 0x30), *(s32 *)(obj + 0x860));
                func_0012D3A0(obj + 0x20, (s32)(obj + 0x30), *(s32 *)player);
                task[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            advance = 1;
            break;
        case 2:
            func_00208DE8(*(s32 *)player, (s32)(obj + 0x30), *(s32 *)(obj + 4));
            if (EftShot_TestBits(*(s32 *)player, 0x40) != 0) {
                *(s32 *)(obj + 0xC) = *(s32 *)(obj + 0x9A0);
                func_00208DE8(*(s32 *)player, (s32)(obj + 0x50), *(s32 *)(obj + 0x9A0));
                *(s32 *)obj |= 0x20;
            }
            if (EftShot_TestBits(*(s32 *)player, 4) != 0) {
                *(s32 *)(obj + 8) = *(s32 *)(obj + 0x8A0);
                *(s32 *)obj |= 0x10;
                func_00208DE8(*(s32 *)player, (s32)(obj + 0x40), *(s32 *)(obj + 0x8A0));
                func_00129C28(obj + 0x60, obj + 0x40);
                func_00129C28(obj + 0x70, obj + 0x60);
                func_00129C28(obj + 0x80, obj + 0x70);
                func_0012D488(player, obj + 0x20, (s32)(obj + 0x70), *(s32 *)player);
                Vec3_Scale(obj + 0x90, obj + 0x20, *(f32 *)(obj + 0x10));
                task[1] = 3;
            }
            break;
        case 4:
            func_00208DE8(*(s32 *)player, (s32)(obj + 0x40), *(s32 *)(obj + 8));
            func_00159988(task);
            ColSeg_Set((s32)sp, (s32)(obj + 0x40), (s32)(obj + 0x70));
            if (func_0011E1C8((s32)sp) != 0) {
                func_00159678(task);
            }
            if (EftShot_TestBits(*(s32 *)player, 8) != 0) {
                *(s32 *)obj |= 9;
                task[1] = 5;
            }
            break;
        default:
            break;
        }
    }
    if (EftShot_TestBits(*(s32 *)player, 0x80) != 0) {
        flags = *(s32 *)obj;
        if ((flags & 8) == 0) {
            flags |= 4;
            *(s32 *)obj = flags;
        }
        *(s32 *)obj = flags | 1;
    }
    func_00151FB0(obj + 0xA4);
    func_00159C98(*(s32 *)player, task, (s32 *)owner);
    gone = func_00152200(owner, (s32)(obj + 0xA4)) != 0;
    if (advance != 0) {
        task[1] = task[1] + 1;
    }
    dead = func_001597E0(task);
    flags = *(s32 *)obj;
    if (gone == 0 && dead == 0) {
        if ((flags & 2) != 0) {
            return BtlTask_SetDead((s32)task);
        }
    }
    if ((flags & 1) != 0) {
        *(s32 *)obj = flags | 2;
        return flags | 2;
    }
    if ((*(u32 *)(*(u8 **)(player + 0x20) + 0x30) & 1) != 0 && (flags & 0x10) != 0) {
        func_00152930((s32)owner, (s32)(obj + 0xA4));
        func_00159B80((s32)task);
    }
    return 0;
}
