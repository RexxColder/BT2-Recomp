#include "common.h"

extern u8 *func_001F3758(void *a0);
extern void func_00152530(u8 *a0, u8 *a1);
extern void func_00208DE8(s32 a0, u8 *out, s32 a2);
extern void func_00129C28(u8 *dst, u8 *src);
extern void Vec3_Sub(u8 *a0, u8 *a1, s32 a2);
extern f32 func_0020A068(s32 a0);
extern void func_00151FB0(u8 *a0);
extern void func_0016F118(s32 a0, u8 *a1, u8 *a2, s32 a3);
extern s32 func_0016F7B0(u8 *a0);
extern s32 func_00152200(u8 *a0, u8 *a1);
extern void func_00152930(u8 *a0, u8 *a1);
extern s32 func_0016EF50(u8 *a0);
extern s32 BtlScene_IsCharStopped(s32 a0);
extern s32 EftShot_TestBits(s32 a0, s32 a1);
extern s32 BtlTask_SetDead(u8 *a0);

s32 func_0016F988(u8 *task) {
    u8 sp[16];
    u8 *ef;
    u8 *ctx;
    u8 *owner;
    u8 *ray;
    s32 adv = 0;
    s32 res;
    s32 hit;
    s32 touch;
    u32 flags;

    owner = *(u8 **)(func_001F3758(task) + 0x38);
    ef = *(u8 **)(task + 0x38);
    ctx = *(u8 **)(ef + 0xB0);
    res = BtlScene_IsCharStopped(*(s32 *)ctx);
    if (res != 0) {
        return res;
    }
    func_00152530(ctx, ef + 0x860);
    if ((*(u32 *)ef & 0x80) == 0) {
        if (EftShot_TestBits(*(s32 *)ctx, 2) != 0) {
            task[1] = 0;
            *(u32 *)ef |= 0x80;
        } else if (EftShot_TestBits(*(s32 *)ctx, 4) != 0) {
            task[1] = 2;
            *(u32 *)ef |= 0x80;
        }
    }
    if ((*(u32 *)ef & 0x80) != 0) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(*(s32 *)ctx, 2) != 0) {
                *(s32 *)(ef + 4) = *(s32 *)(ef + 0x870);
                func_00208DE8(*(s32 *)ctx, sp, *(s32 *)(ef + 4));
                func_00129C28(ef + 0x40, sp);
                Vec3_Sub(ef + 0x30, ef + 0x40, *(s32 *)ctx);
                task[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            adv = 1;
            break;
        case 2: {
            f32 v = func_0020A068(*(s32 *)ctx);
            *(f32 *)(ef + 0x20) = v;
            *(f32 *)(ef + 0x1C) = *(f32 *)(ef + 0x18) * (v + 1.0f);
            func_00208DE8(*(s32 *)ctx, sp, *(s32 *)(ef + 4));
            func_00129C28(ef + 0x40, sp);
            if (EftShot_TestBits(*(s32 *)ctx, 0x40) != 0) {
                *(s32 *)(ef + 0xC) = *(s32 *)(ef + 0x9B0);
                func_00208DE8(*(s32 *)ctx, sp, *(s32 *)(ef + 0xC));
                func_00129C28(ef + 0x60, sp);
                *(u32 *)ef |= 0x40;
            }
            if (EftShot_TestBits(*(s32 *)ctx, 4) != 0) {
                *(s32 *)(ef + 8) = *(s32 *)(ef + 0x8B0);
                func_00208DE8(*(s32 *)ctx, sp, *(s32 *)(ef + 8));
                func_00129C28(ef + 0x50, sp);
                func_00129C28(ef + 0x70, ef + 0x50);
                func_00129C28(ef + 0x80, ef + 0x70);
                task[1] = 3;
            }
            break;
        }
        case 4:
            func_00208DE8(*(s32 *)ctx, sp, *(s32 *)(ef + 8));
            func_00129C28(ef + 0x50, sp);
            if (EftShot_TestBits(*(s32 *)ctx, 8) != 0) {
                *(u32 *)ef |= 9;
                task[1] = 5;
            }
            break;
        }
    }
    ray = ef + 0xB4;
    if (EftShot_TestBits(*(s32 *)ctx, 0x80) != 0) {
        flags = *(u32 *)ef | 1;
        if ((*(u32 *)ef & 8) == 0) {
            flags |= 4;
        }
        *(u32 *)ef = flags;
    }
    func_00151FB0(ray);
    func_0016F118(*(s32 *)ctx, task, owner, 0);
    hit = func_0016F7B0(task);
    touch = func_00152200(owner, ray) != 0;
    if (adv != 0) {
        task[1] = task[1] + 1;
    }
    flags = *(u32 *)ef;
    if (hit == 0 && touch == 0) {
        if ((flags & 2) != 0) {
            return BtlTask_SetDead(task);
        }
    }
    if ((flags & 1) != 0) {
        res = flags | 2;
        *(u32 *)ef = res;
        return res;
    }
    res = flags & 0x10;
    if ((*(u32 *)(*(u8 **)(ctx + 0x20) + 0x30) & 1) != 0 && res != 0) {
        func_00152930(owner, ray);
        return func_0016EF50(task);
    }
    return res;
}
