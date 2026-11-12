#include "common.h"

u8 *func_001F3758(s32 arg0);
s32 BtlScene_IsCharStopped(s32 arg0);
void func_00152530(s32 arg0, s32 arg1);
s32 EftShot_TestBits(s32 arg0, s32 arg1);
s32 func_00208DE8(s32 a0, s32 a1, s32 a2);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
f32 func_0020A068(s32 arg0);
void func_00129C28(u8 *arg0, u8 *arg1);
void func_00151FB0(u8 *arg0);
void func_00160FE8(s32 arg0, u8 *arg1, s32 *arg2, s32 arg3);
s32 func_00152200(u8 *arg0, s32 arg1);
s32 BtlTask_SetDead(s32 arg0);
void func_00152930(s32 arg0, s32 arg1);
void func_00160E20(u8 *arg0);

s32 func_00161218(u8 *task) {
    u8 sp[16];
    s32 advance = 0;
    u8 *obj;
    u8 *owner;
    u8 *player;
    s32 stopped;
    s32 flags;
    s32 gone;
    f32 len;

    player = func_001F3758(0);
    obj = *(u8 **)(task + 0x38);
    owner = *(u8 **)(player + 0x38);
    player = *(u8 **)(obj + 0xB0);
    stopped = BtlScene_IsCharStopped(*(s32 *)player);
    if (stopped != 0) {
        return stopped;
    }
    func_00152530((s32)player, (s32)(obj + 0x860));
    if ((*(s32 *)obj & 0x80) == 0) {
        if (EftShot_TestBits(*(s32 *)player, 2) != 0) {
            task[1] = 0;
            *(s32 *)obj |= 0x80;
        } else if (EftShot_TestBits(*(s32 *)player, 4) != 0) {
            task[1] = 2;
            *(s32 *)obj |= 0x80;
        }
    }
    if ((*(s32 *)obj & 0x80) != 0) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(*(s32 *)player, 2) != 0) {
                *(s32 *)(obj + 4) = 0;
                func_00208DE8(*(s32 *)player, (s32)(obj + 0x40), 0);
                func_00208DE8(*(s32 *)player, (s32)sp, 3);
                Vec3_Sub((s32)(obj + 0x30), (s32)sp, (s32)(obj + 0x40));
                Vec3_Normalize((s32)(obj + 0x30), (s32)(obj + 0x30));
                task[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            advance = 1;
            break;
        case 2:
            len = func_0020A068(*(s32 *)player);
            *(f32 *)(obj + 0x20) = len;
            *(f32 *)(obj + 0x18) = *(f32 *)(obj + 0x14) * (len * 0.5f + 1.0f);
            func_00208DE8(*(s32 *)player, (s32)(obj + 0x40), *(s32 *)(obj + 4));
            if (EftShot_TestBits(*(s32 *)player, 0x40) != 0) {
                *(s32 *)(obj + 0xC) = *(s32 *)(obj + 0x9B0);
                func_00208DE8(*(s32 *)player, (s32)(obj + 0x60), *(s32 *)(obj + 0x9B0));
                *(s32 *)obj |= 0x40;
            }
            if (EftShot_TestBits(*(s32 *)player, 4) != 0) {
                *(s32 *)obj |= 0x10;
                *(s32 *)(obj + 4) = 4;
                *(s32 *)(obj + 8) = *(s32 *)(obj + 0x8B0);
                func_00208DE8(*(s32 *)player, (s32)sp, 3);
                func_00129C28(obj + 0x90, sp);
                task[1] = 3;
            }
            break;
        case 4:
            func_00129C28(obj + 0x90, obj + 0x80);
            if (EftShot_TestBits(*(s32 *)player, 8) != 0) {
                *(s32 *)obj |= 9;
                task[1] = 5;
            }
            break;
        default:
            break;
        }
    }
    if (task[1] != 0 && (*(s32 *)obj & 1) == 0) {
        func_00208DE8(*(s32 *)player, (s32)(obj + 0x40), *(s32 *)(obj + 4));
        func_00208DE8(*(s32 *)player, (s32)sp, 3);
        func_00129C28(obj + 0x80, obj + 0x40);
        Vec3_Sub((s32)(obj + 0x30), (s32)sp, (s32)(obj + 0x40));
        Vec3_Normalize((s32)(obj + 0x30), (s32)(obj + 0x30));
    }
    if (EftShot_TestBits(*(s32 *)player, 0x80) != 0) {
        flags = *(s32 *)obj;
        if ((flags & 8) == 0) {
            flags |= 4;
            *(s32 *)obj = flags;
        }
        *(s32 *)obj = flags | 1;
    }
    func_00151FB0(obj + 0xB4);
    func_00160FE8(*(s32 *)player, task, (s32 *)owner, 0);
    gone = func_00152200(owner, (s32)(obj + 0xB4)) != 0;
    if (advance != 0) {
        task[1] = task[1] + 1;
    }
    flags = *(s32 *)obj;
    if (gone == 0 && (flags & 2) != 0) {
        return BtlTask_SetDead((s32)task);
    }
    if ((flags & 1) != 0) {
        *(s32 *)obj = flags | 2;
        return flags | 2;
    }
    if ((*(u32 *)(*(u8 **)(player + 0x20) + 0x30) & 1) != 0 && (flags & 0x10) != 0) {
        func_00152930((s32)owner, (s32)(obj + 0xB4));
        func_00160E20(task);
    }
    return 0;
}
