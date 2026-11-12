#include "common.h"

extern f32 D_00384594;

u8 *func_001F3758(void *a0);
s32 BtlScene_IsCharStopped(s32 a0);
void func_00152530(u8 *a0, u8 *a1);
s32 EftShot_TestBits(s32 a0, s32 a1);
s32 func_00208DE8(s32 a0, u8 *a1, s32 a2);
s32 func_0012D3A0(u8 *a0, u8 *a1, s32 a2);
f32 func_0020A068(s32 a0);
void func_00129C28(u8 *dst, u8 *src);
void func_00129C38(u8 *a0, u8 *a1);
s32 func_0012D488(u8 *a0, u8 *a1, u8 *a2, s32 a3);
void func_00129BD0(u8 *dst, u8 *src, f32 f12);
void func_0012D5D8(u8 *a0, u8 *a1, u8 *a2, s32 a3, f32 f12, f32 f13);
void Vec3_Add(u8 *dst, u8 *a, u8 *b);
void func_002837C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_00283800(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_00283840(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
void func_00283770(s32 a0, u8 *a1, s32 a2);
void func_00151FB0(u8 *a0);
s32 func_0014A6D0(s32 a0, u8 *a1, u8 *a2, s32 a3);
s32 func_00152200(u8 *a0, u8 *a1);
s32 BtlTask_SetDead(u8 *a0);
void func_00152930(u8 *a0, u8 *a1);
void func_0014A508(u8 *a0);

s32 func_0014A968(u8 *task) {
    u8 *d = *(u8 **)(task + 0x38);
    u8 *obj = *(u8 **)(d + 0xB0);
    u8 *scene = *(u8 **)(func_001F3758(task) + 0x38);
    u8 *cfg;
    u8 *ptr = d + 0xB4;
    s32 advance = 0;
    s32 res;
    s32 flags;
    s32 hit;
    f32 f;
    f32 fade;
    s32 r;
    s32 g;
    s32 b;

    res = BtlScene_IsCharStopped(*(s32 *)obj);
    if (res != 0) {
        return res;
    }
    func_00152530(obj, d + 0x860);

    if ((*(u32 *)d & 0x80) == 0) {
        if (EftShot_TestBits(*(s32 *)obj, 2) != 0) {
            task[1] = 0;
            *(u32 *)d |= 0x80;
        } else if (EftShot_TestBits(*(s32 *)obj, 4) != 0) {
            task[1] = 2;
            *(u32 *)d |= 0x80;
        }
    }

    if ((*(u32 *)d & 0x80) != 0 && task[1] < 6) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(*(s32 *)obj, 2) != 0) {
                *(s32 *)(d + 4) = *(s32 *)(d + 0x870);
                func_00208DE8(*(s32 *)obj, d + 0x40, *(s32 *)(d + 4));
                func_0012D3A0(d + 0x30, d + 0x40, *(s32 *)obj);
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
            *(f32 *)(d + 0x1C) = f;
            *(f32 *)(d + 0x18) = *(f32 *)(d + 0x14) * (f * 0.5f + 1.0f);
            func_00208DE8(*(s32 *)obj, d + 0x40, *(s32 *)(d + 4));
            if (EftShot_TestBits(*(s32 *)obj, 0x40) != 0) {
                *(s32 *)(d + 0xC) = *(s32 *)(d + 0x9B0);
                func_00208DE8(*(s32 *)obj, d + 0x60, *(s32 *)(d + 0xC));
                *(u32 *)d |= 0x40;
            }
            if (EftShot_TestBits(*(s32 *)obj, 4) != 0) {
                *(u32 *)d |= 0x10;
                *(s32 *)(d + 8) = *(s32 *)(d + 0x8B0);
                func_00208DE8(*(s32 *)obj, d + 0x50, *(s32 *)(d + 8));
                func_00129C28(d + 0x70, d + 0x50);
                func_00129C28(d + 0x80, d + 0x70);
                func_00208DE8(*(s32 *)obj, d + 0x90, 0x11);
                func_0012D488(obj, d + 0x30, d + 0x80, *(s32 *)obj);
                func_00129BD0(d + 0xA0, d + 0x30, *(f32 *)(d + 0x10));
                task[1] = 3;
            }
            break;
        case 4:
            func_00129C28(d + 0x90, d + 0x80);
            cfg = *(u8 **)(*(u8 **)(d + 0xB0) + 0x20);
            if ((*(u32 *)(cfg + 0x30) & 2) == 0) {
                if ((*(u32 *)d & 0x20) != 0) {
                    func_00129C38(d + 0x80, task + 0x10);
                } else {
                    f = *(f32 *)(*(u8 **)(obj + 0x24) + 0x10);
                    if (0.0f < f) {
                        func_0012D5D8(d + 0x30, d + 0x80, d + 0x30, *(s32 *)obj, *(f32 *)(d + 0x10), f);
                        func_00129BD0(d + 0xA0, d + 0x30, *(f32 *)(d + 0x10));
                    }
                    Vec3_Add(d + 0x80, d + 0x80, d + 0xA0);
                }
            }
            func_00208DE8(*(s32 *)obj, d + 0x50, *(s32 *)(d + 8));
            if (EftShot_TestBits(*(s32 *)obj, 8) != 0) {
                *(u32 *)d |= 9;
                task[1] = 5;
            }
            break;
        }
    }

    if (EftShot_TestBits(*(s32 *)obj, 0x80) != 0) {
        flags = *(s32 *)d;
        if ((flags & 8) == 0) {
            flags |= 4;
        }
        *(s32 *)d = flags | 1;
    }
    if ((*(u32 *)d & 0x200) == 0) {
        if (EftShot_TestBits(*(s32 *)obj, 0x10) != 0) {
            *(u32 *)d |= 0x200;
        }
    }
    if (EftShot_TestBits(*(s32 *)obj, 2) != 0) {
        *(s32 *)(d + 0x20) = 0;
        *(u32 *)d &= ~0x200;
    }
    if ((*(u32 *)d & 0x200) != 0) {
        f = *(f32 *)(d + 0x20) + D_00384594;
        *(f32 *)(d + 0x20) = f;
        if (1.0f < f) {
            *(f32 *)(d + 0x20) = 1.0f;
        }
    }
    fade = *(f32 *)(d + 0x20);
    r = (s32)(fade * 32.0f);
    g = (s32)(fade * 64.0f);
    b = (s32)(fade * 128.0f);
    func_002837C0(0, 0x80, 0x80, 0x80, r & 0xFF);
    func_00283800(0, 0x80, 0x80, 0x80, g & 0xFF);
    func_00283840(0, 0x80, 0x80, 0x80, b & 0xFF);
    func_00283770(0, d + 0x30, 0);
    func_00151FB0(ptr);
    func_0014A6D0(*(s32 *)obj, task, scene, 0);
    hit = func_00152200(scene, ptr) != 0;
    if (advance != 0) {
        task[1] = task[1] + 1;
    }
    flags = *(s32 *)d;
    if (hit == 0) {
        if ((flags & 2) != 0) {
            return BtlTask_SetDead(task);
        }
    }
    if ((flags & 1) != 0) {
        *(s32 *)d = flags | 2;
        return flags | 2;
    }
    cfg = *(u8 **)(obj + 0x20);
    if ((*(u32 *)(cfg + 0x30) & 1) == 0) {
        return 0;
    }
    if ((flags & 0x10) == 0) {
        return 0;
    }
    func_00152930(scene, ptr);
    func_0014A508(task);
    return 0;
}
