#include "common.h"

extern u8 *func_001F3758(void *a0);
extern void func_00152530(u8 *a0, u8 *a1);
extern void func_00208DE8(s32 a0, u8 *out, s32 a2);
extern void func_00129C28(u8 *dst, u8 *src);
extern void func_00129BD0(u8 *a0, u8 *a1, f32 f12);
extern void Vec3_Sub(u8 *a0, u8 *a1, s32 a2);
extern void func_00147FB8(s32 a0);
extern s32 func_0020B3D0(s32 a0);
extern void func_00151FB0(u8 *a0);
extern void func_00158EB0(s32 a0, u8 *a1, u8 *a2, s32 a3);
extern void func_00158AD8(u8 *a0);
extern s32 func_00152200(u8 *a0, u8 *a1);
extern s32 func_00182B10(s32 arg0);
extern void func_00182AB8(s32 a0);
extern s32 func_00158910(u8 *a0);
extern s32 BtlScene_IsCharStopped(s32 a0);
extern s32 EftShot_TestBits(s32 a0, s32 a1);
extern s32 BtlTask_SetDead(u8 *a0);

s32 func_00159158(u8 *task) {
    u8 *ef;
    u8 *ctx;
    u8 *owner;
    u8 *ray;
    u8 *slot;
    s32 res;
    s32 touch;
    s32 i;
    u32 flags;

    owner = *(u8 **)(func_001F3758(task) + 0x38);
    ef = *(u8 **)(task + 0x38);
    ctx = *(u8 **)(ef + 8);
    res = BtlScene_IsCharStopped(*(s32 *)ctx);
    if (res != 0) {
        return res;
    }
    func_00152530(ctx, ef + 0x860);
    switch (*(s32 *)(ef + 4)) {
    case 0:
        if (EftShot_TestBits(*(s32 *)ctx, 2) != 0) {
            *(s32 *)(ef + 0x20) = *(s32 *)(ef + 0x870);
            func_00208DE8(*(s32 *)ctx, ef + 0x40, *(s32 *)(ef + 0x20));
            Vec3_Sub(ef + 0x30, ef + 0x40, *(s32 *)ctx);
            *(s32 *)(ef + 4) = 1;
        }
        break;
    case 1:
        *(s32 *)(ef + 4) = 2;
        break;
    case 2:
        func_00208DE8(*(s32 *)ctx, ef + 0x40, *(s32 *)(ef + 0x20));
        if (EftShot_TestBits(*(s32 *)ctx, 0x10) != 0) {
            func_00147FB8(*(s32 *)ctx);
            func_00208DE8(func_0020B3D0(*(s32 *)ctx), ef + 0x70, 0x11);
            func_00129C28(ef + 0x80, ef + 0x70);
            func_00129C28(ef + 0x90, ef + 0x80);
            Vec3_Sub(ef + 0x30, ef + 0x40, *(s32 *)ctx);
            func_00129BD0(ef + 0xA0, ef + 0x30, *(f32 *)(ef + 0x18));
        }
        if (EftShot_TestBits(*(s32 *)ctx, 0x40) != 0) {
            *(s32 *)(ef + 0x28) = *(s32 *)(ef + 0x9B0);
            func_00208DE8(*(s32 *)ctx, ef + 0x60, *(s32 *)(ef + 0x28));
            *(u32 *)ef |= 0x40;
            func_00158AD8(task);
        }
        if (EftShot_TestBits(*(s32 *)ctx, 4) != 0) {
            *(s32 *)(ef + 4) = 3;
            *(s32 *)(ef + 0x24) = *(s32 *)(ef + 0x8B0);
        }
        break;
    case 3:
        *(s32 *)(ef + 4) = 4;
        break;
    case 4:
        func_00129C28(ef + 0x90, ef + 0x80);
        if (*(s32 *)(ef + 0x24) != 0) {
            func_00208DE8(*(s32 *)ctx, ef + 0x50, *(s32 *)(ef + 0x24));
        } else {
            func_00129C28(ef + 0x50, ef + 0x70);
        }
        if (EftShot_TestBits(*(s32 *)ctx, 8) != 0) {
            *(s32 *)(ef + 4) = 5;
            *(u32 *)ef |= 9;
        }
        break;
    case 5:
        *(s32 *)(ef + 4) = 6;
        break;
    default:
        break;
    }

    ray = ef + 0xB0;
    if (EftShot_TestBits(*(s32 *)ctx, 0x80) != 0) {
        flags = *(u32 *)ef | 3;
        if ((*(u32 *)ef & 8) == 0) {
            flags |= 4;
        }
        *(u32 *)ef = flags;
    }
    func_00151FB0(ray);
    func_00158EB0(*(s32 *)ctx, task, owner, 0);
    touch = func_00152200(owner, ray);
    flags = *(u32 *)ef;
    if (touch == 0 && (flags & 2) != 0) {
        return BtlTask_SetDead(task);
    }
    if ((flags & 1) != 0) {
        if (*(s32 *)(ef + 0x14) == 0) {
            res = flags | 2;
            *(u32 *)ef = res;
            return res;
        }
        for (i = 0; i < *(s32 *)(ef + 0x14); i++) {
            slot = ef + 0xC + 4 * i;
            if (*(s32 *)slot != 0 && func_00182B10(*(s32 *)slot) != 0) {
                func_00182AB8(*(s32 *)slot);
                *(s32 *)slot = 0;
                *(s32 *)(ef + 0x10) = *(s32 *)(ef + 0x10) - 1;
            }
        }
        res = *(s32 *)(ef + 0x10);
        if (res == 0) {
            res = *(u32 *)ef | 2;
            *(u32 *)ef = res;
        }
        return res;
    }
    res = flags & 0x10;
    if ((*(u32 *)(*(u8 **)(ctx + 0x20) + 0x30) & 1) != 0 && res != 0) {
        return func_00158910(task);
    }
    return res;
}
