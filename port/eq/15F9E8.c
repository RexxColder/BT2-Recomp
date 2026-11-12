#include "common.h"

u8 *func_001F3758(void *a0);
s32 BtlScene_IsCharStopped(s32 a0);
void func_00152530(u8 *a0, u8 *a1);
s32 EftShot_TestBits(s32 a0, s32 a1);
s32 func_00208DE8(s32 a0, u8 *a1, s32 a2);
void func_00129C28(u8 *dst, u8 *src);
s32 func_0012D3A0(u8 *a0, u8 *a1, s32 a2);
void func_00129BD0(u8 *dst, u8 *src, f32 f12);
void func_0012D5D8(u8 *a0, u8 *a1, u8 *a2, s32 a3, f32 f12, f32 f13);
void Vec3_Add(u8 *dst, u8 *a, u8 *b);
void func_0015F3E8(u8 *a0);
void func_00151FB0(u8 *a0);
void func_0015F718(s32 a0, u8 *a1, u8 *a2);
s32 func_00152200(u8 *a0, u8 *a1);
void func_00152930(u8 *a0, u8 *a1);
void func_0015F608(u8 *a0);
s32 BtlTask_SetDead(u8 *a0);

s32 func_0015F9E8(u8 *task) {
    u8 sp[0x10];
    u8 *d = *(u8 **)(task + 0x38);
    u8 *obj = *(u8 **)(d + 0xF0);
    u8 *env = *(u8 **)(func_001F3758(task) + 0x38);
    u8 *posA = d + 0xB0;
    u8 *posB = d + 0xC0;
    u8 *dir = d + 0x30;
    u8 *vel;
    s32 stepFlag = 0;
    s32 res;
    s32 flags;
    s32 rc;
    s32 stopped;
    f32 *scale = (f32 *)(d + 0x18);

    res = BtlScene_IsCharStopped(*(s32 *)obj);
    if (res != 0) {
        return res;
    }
    func_00152530(obj, d + 0x8A0);
    if ((*(s32 *)d & 0x80) == 0) {
        if (EftShot_TestBits(*(s32 *)obj, 2) != 0) {
            task[1] = 0;
            *(s32 *)d |= 0x80;
        } else if (EftShot_TestBits(*(s32 *)obj, 4) != 0) {
            task[1] = 2;
            *(s32 *)d |= 0x80;
        }
    }
    if (EftShot_TestBits(*(s32 *)obj, 0x10) != 0) {
        func_00208DE8(*(s32 *)obj, posA, *(s32 *)(d + 0x970));
        func_00129C28(posB, posA);
        func_0012D3A0(dir, posB, *(s32 *)obj);
        func_00129BD0(d + 0xE0, dir, *scale);
        *(s32 *)d |= 0x800;
    }
    if (EftShot_TestBits(*(s32 *)obj, 0x20) != 0) {
        *scale = *(f32 *)(*(u8 **)(obj + 0x24) + 8);
        func_0012D3A0(dir, posB, *(s32 *)obj);
        func_00129BD0(d + 0xE0, dir, *scale);
        *(s32 *)d |= 0x1010;
        *(s32 *)(task + 4) &= ~1;
        *(s32 *)(task + 4) &= ~4;
        *(s32 *)(task + 4) &= ~0x200;
    }
    if ((*(s32 *)d & 0x80) != 0 && task[1] < 6) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(*(s32 *)obj, 2) != 0) {
                *(s32 *)(d + 0xC) = *(s32 *)(d + 0x8B0);
                func_00208DE8(*(s32 *)obj, sp, *(s32 *)(d + 0xC));
                func_00129C28(d + 0x40, sp);
                func_0012D3A0(dir, d + 0x40, *(s32 *)obj);
                task[1] = 1;
            }
            break;
        case 2:
            func_00208DE8(*(s32 *)obj, sp, *(s32 *)(d + 0xC));
            func_00129C28(d + 0x40, sp);
            if (EftShot_TestBits(*(s32 *)obj, 0x40) != 0) {
                *(s32 *)(d + 0x14) = *(s32 *)(d + 0x9F0);
                func_00208DE8(*(s32 *)obj, sp, *(s32 *)(d + 0x14));
                func_00129C28(d + 0x60, sp);
                *(s32 *)d |= 0x40;
            }
            if (EftShot_TestBits(*(s32 *)obj, 4) != 0) {
                *(s32 *)(d + 0x10) = *(s32 *)(d + 0x8F0);
                *(s32 *)d |= 0x10;
                func_00208DE8(*(s32 *)obj, sp, *(s32 *)(d + 0x10));
                func_00129C28(d + 0x50, sp);
                func_00129C28(d + 0x70, d + 0x50);
                func_00129C28(d + 0x80, d + 0x70);
                func_00129C28(d + 0x90, d + 0x80);
                func_0012D3A0(dir, d + 0x80, *(s32 *)obj);
                func_00129BD0(d + 0xA0, dir, *scale);
                task[1] = 3;
            }
            break;
        case 4:
            if ((*(s32 *)d & 0x400) == 0) {
                func_00129C28(d + 0x90, d + 0x80);
                if ((*(s32 *)(*(u8 **)(*(u8 **)(d + 0xF0) + 0x20) + 0x30) & 2) == 0 && (*(s32 *)d & 0x20) == 0) {
                    if (*(f32 *)(*(u8 **)(obj + 0x24) + 0x10) > 0.0f) {
                        func_0012D5D8(dir, d + 0x80, dir, *(s32 *)obj, *scale, *(f32 *)(*(u8 **)(obj + 0x24) + 0x10));
                        func_00129BD0(d + 0xA0, dir, *scale);
                    }
                    Vec3_Add(d + 0x80, d + 0x80, d + 0xA0);
                }
            }
            func_00208DE8(*(s32 *)obj, sp, *(s32 *)(d + 0x10));
            func_00129C28(d + 0x50, sp);
            if (EftShot_TestBits(*(s32 *)obj, 8) != 0) {
                *(s32 *)d |= 0x109;
                task[1] = 5;
            }
            break;
        default:
            stepFlag = 1;
            break;
        }
    }
    func_00129C28(d + 0xD0, posB);
    if ((*(s32 *)d & 0x1000) != 0) {
        if (*(f32 *)(*(u8 **)(*(u8 **)(d + 0xF0) + 0x20) + 0x18) > 0.0f) {
            func_0012D5D8(dir, posB, dir, *(s32 *)obj, *scale, *(f32 *)(*(u8 **)(*(u8 **)(d + 0xF0) + 0x20) + 0x18));
            func_00129BD0(d + 0xE0, dir, *scale);
        }
        Vec3_Add(posB, posB, d + 0xE0);
    } else if ((*(s32 *)d & 0x800) != 0) {
        func_00208DE8(*(s32 *)obj, posB, *(s32 *)(d + 0x970));
    }
    if (EftShot_TestBits(*(s32 *)obj, 0x80) != 0) {
        flags = *(s32 *)d;
        if ((flags & 8) == 0) {
            flags |= 4;
        }
        *(s32 *)d = flags | 0x100;
    }
    func_0015F3E8(task);
    func_00151FB0(d + 0xF4);
    func_0015F718(*(s32 *)obj, task, env);
    stopped = func_00152200(env, d + 0xF4) != 0;
    if (stepFlag != 0) {
        task[1] = task[1] + 1;
    }
    flags = *(s32 *)d;
    if (stopped == 0) {
        if ((flags & 2) != 0) {
            return BtlTask_SetDead(task);
        }
    }
    if ((flags & 0x100) != 0) {
        res = flags | 2;
        *(s32 *)d = res;
        return res;
    }
    res = flags & 0x10;
    if ((*(s32 *)(*(u8 **)(obj + 0x20) + 0x30) & 1) != 0) {
        if (res == 0) {
            return 0;
        }
        func_00152930(env, d + 0xF4);
        func_0015F608(task);
        return 0;
    }
    return res;
}
