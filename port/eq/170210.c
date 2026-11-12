#include "common.h"

extern u8 *func_001F3758(u8 *task);
extern s32 func_0020B3D0(s32 obj);
extern s32 BtlScene_IsCharStopped(s32 obj);
extern s32 EftShot_TestBits(s32 obj, s32 bits);
extern void func_00152530(u8 *a, u8 *b);
extern f32 BtlCharApi_GetHeight(s32 obj);
extern void func_00208DE8(s32 obj, u8 *dst, s32 idx);
extern void Vec3_Sub(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Add(u8 *dst, u8 *a, u8 *b);
extern void func_00129BD0(u8 *dst, u8 *src, f32 s);
extern void func_00129C28(u8 *dst, u8 *src);
extern void func_0012D3A0(u8 *dst, u8 *src, s32 obj);
extern void func_0012D488(u8 *own, u8 *dst, u8 *src, s32 obj);
extern void func_0012D5D8(u8 *dst, u8 *a, u8 *b, s32 obj, f32 s, f32 t);
extern f32 func_0020A068(s32 obj);
extern void func_00151FB0(u8 *p);
extern void func_0016FFE0(s32 obj, u8 *task, u8 *scene, s32 z);
extern s32 func_00152200(u8 *scene, u8 *p);
extern s32 BtlTask_SetDead(u8 *task);
extern void func_00152930(u8 *scene, u8 *p);
extern s32 func_0016FEC0(u8 *task);
extern f32 D_003848B0;
extern f32 D_003848B4;

/* Projectile/beam effect task update (variant with a trailing point, flag 0x200 = follow bone 0x34):
   state machine in task[1] (0..5), same shape as 149090. */
s32 func_00170210(u8 *task) {
    u8 *fx = *(u8 **)(task + 0x38);
    u8 *own = *(u8 **)(fx + 0xD0);
    u8 *scene = *(u8 **)(func_001F3758(task) + 0x38);
    s32 advance = 0;
    s32 stopped;
    s32 done;
    u8 *vec;
    u32 flags;
    u8 tmp[0x10];
    u8 t10[0x10];
    u8 t20[0x10];
    u8 t30[0x10];

    stopped = BtlScene_IsCharStopped(*(s32 *)own);
    if (stopped != 0) {
        return stopped;
    }
    func_00152530(own, fx + 0x880);

    if ((*(u32 *)fx & 0x200) != 0) {
        if (EftShot_TestBits(*(s32 *)own, 0x10) != 0) {
            *(u32 *)fx |= 0x400;
        }
        if (EftShot_TestBits(*(s32 *)own, 0x20) != 0) {
            *(u32 *)fx |= 1;
        }
        if ((*(u32 *)fx & 1) != 0) {
            Vec3_Sub(t30, fx + 0x70, fx + 0x80);
            func_00129C28(fx + 0x80, fx + 0x70);
            Vec3_Add(fx + 0x70, fx + 0x70, t30);
        } else {
            s32 obj = func_0020B3D0(*(s32 *)own);
            f32 s = BtlCharApi_GetHeight(obj) / D_003848B0;
            if (s < D_003848B4) {
                s = D_003848B4;
            }
            func_00208DE8(obj, t20, 0);
            func_00208DE8(*(s32 *)own, fx + 0x70, 0x34);
            func_00208DE8(*(s32 *)own, t10, 0);
            Vec3_Sub(fx + 0x70, fx + 0x70, t10);
            func_00129BD0(fx + 0x70, fx + 0x70, s * 1.5f);
            func_00129C28(fx + 0x80, fx + 0x70);
            Vec3_Add(fx + 0x70, fx + 0x70, t20);
        }
    }

    if ((*(u32 *)fx & 0x80) == 0) {
        if (EftShot_TestBits(*(s32 *)own, 2) != 0) {
            task[1] = 0;
            *(u32 *)fx |= 0x80;
        } else if (EftShot_TestBits(*(s32 *)own, 4) != 0) {
            task[1] = 2;
            *(u32 *)fx |= 0x80;
        }
    }

    if ((*(u32 *)fx & 0x80) != 0) {
        switch (task[1]) {
        case 0:
            if (EftShot_TestBits(*(s32 *)own, 2) != 0) {
                *(s32 *)(fx + 4) = *(s32 *)(fx + 0x890);
                func_00208DE8(*(s32 *)own, tmp, *(s32 *)(fx + 0x890));
                func_00129C28(fx + 0x40, tmp);
                func_0012D3A0(fx + 0x30, fx + 0x40, *(s32 *)own);
                task[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            advance = 1;
            break;
        case 2: {
            f32 h = func_0020A068(*(s32 *)own);
            *(f32 *)(fx + 0x20) = h;
            *(f32 *)(fx + 0x18) = *(f32 *)(fx + 0x14) * (h + 1.0f);
            func_00208DE8(*(s32 *)own, tmp, *(s32 *)(fx + 4));
            func_00129C28(fx + 0x40, tmp);
            if (EftShot_TestBits(*(s32 *)own, 0x40) != 0) {
                *(s32 *)(fx + 0xC) = *(s32 *)(fx + 0x9D0);
                func_00208DE8(*(s32 *)own, tmp, *(s32 *)(fx + 0x9D0));
                func_00129C28(fx + 0x60, tmp);
                *(u32 *)fx |= 0x40;
            }
            if (EftShot_TestBits(*(s32 *)own, 4) != 0) {
                s32 idx = *(s32 *)(fx + 0x8D0);
                *(u32 *)fx |= 0x10;
                *(s32 *)(fx + 8) = idx;
                func_00208DE8(*(s32 *)own, tmp, idx);
                func_00129C28(fx + 0x50, tmp);
                func_00129C28(fx + 0x90, fx + 0x50);
                func_00129C28(fx + 0xA0, fx + 0x90);
                func_00208DE8(*(s32 *)own, fx + 0xB0, 0x11);
                func_0012D488(own, fx + 0x30, fx + 0xA0, *(s32 *)own);
                func_00129BD0(fx + 0xC0, fx + 0x30, *(f32 *)(fx + 0x10));
                task[1] = 3;
            }
            break;
        }
        case 4: {
            u8 *p30 = fx + 0x30;
            u8 *pA0 = fx + 0xA0;
            u8 *pC0 = fx + 0xC0;
            func_00129C28(fx + 0xB0, pA0);
            if ((*(u32 *)fx & 0x200) != 0) {
                func_00129C28(pA0, fx + 0x70);
            } else if ((*(u32 *)(*(u8 **)(*(u8 **)(fx + 0xD0) + 0x20) + 0x30) & 2) != 0) {
                /* nothing */
            } else if ((*(u32 *)fx & 0x20) != 0) {
                /* nothing */
            } else {
                f32 w = *(f32 *)(*(u8 **)(own + 0x24) + 0x10);
                if (0.0f < w) {
                    func_0012D5D8(p30, pA0, p30, *(s32 *)own, *(f32 *)(fx + 0x10), w);
                    func_00129BD0(pC0, p30, *(f32 *)(fx + 0x10));
                }
                Vec3_Add(pA0, pA0, pC0);
            }
            func_00208DE8(*(s32 *)own, tmp, *(s32 *)(fx + 8));
            func_00129C28(fx + 0x50, tmp);
            if (EftShot_TestBits(*(s32 *)own, 8) != 0) {
                *(u32 *)fx |= 9;
                task[1] = 5;
            }
            break;
        }
        default:
            break;
        }
    }

    vec = fx + 0xD4;
    if (EftShot_TestBits(*(s32 *)own, 0x80) != 0) {
        if ((*(u32 *)fx & 8) == 0) {
            *(u32 *)fx |= 4;
        }
        *(u32 *)fx |= 1;
    }
    func_00151FB0(vec);
    func_0016FFE0(*(s32 *)own, task, scene, 0);
    done = func_00152200(scene, vec) != 0;
    if (advance != 0) {
        task[1] += 1;
    }
    flags = *(u32 *)fx;
    if (!done && (flags & 2) != 0) {
        return BtlTask_SetDead(task);
    }
    if ((flags & 1) != 0) {
        *(u32 *)fx = flags | 2;
        return flags | 2;
    }
    if ((*(u32 *)(*(u8 **)(own + 0x20) + 0x30) & 1) != 0 && (flags & 0x10) != 0) {
        func_00152930(scene, vec);
        return func_0016FEC0(task);
    }
    return 0;
}
