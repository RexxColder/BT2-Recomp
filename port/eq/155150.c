#include "common.h"

extern f32 D_00384694;

u8 *func_001F3758(void *a0);
s32 BtlScene_IsCharStopped(s32 a0);
void func_00152530(u8 *a0, u8 *a1);
s32 EftShot_TestBits(s32 a0, s32 a1);
s32 func_00208DE8(s32 a0, u8 *a1, s32 a2);
void func_00129C28(u8 *dst, u8 *src);
f32 func_0020A068(s32 a0);
void func_00152960(s32 a0, u8 *a1);
s32 func_0012D3A0(u8 *a0, u8 *a1, s32 a2);
void Mtx_StoreIdentity(u8 *a0);
f32 Mathf_Asin(f32 x);
f32 EftMath_WrapAngle(f32 x);
f32 atan2f(f32 y, f32 x);
void Mtx_RotateX(u8 *dst, u8 *src, f32 ang);
void Mtx_RotateY(u8 *dst, u8 *src, f32 ang);
void func_00129C50(u8 *a0, u8 *a1, u8 *a2);
void func_00129BD0(u8 *dst, u8 *src, f32 f12);
void Vec4_Set(u8 *dst, f32 x, f32 y, f32 z, f32 w);
void func_0012D5D8(u8 *a0, u8 *a1, u8 *a2, s32 a3, f32 f12, f32 f13);
void Vec3_Add(u8 *dst, u8 *a, u8 *b);
void func_00151FB0(u8 *a0);
s32 func_00154ED8(s32 a0, u8 *a1, u8 *a2, s32 a3);
s32 func_00152200(u8 *a0, u8 *a1);
void func_00152930(u8 *a0, u8 *a1);
s32 func_00154D10(u8 *a0);
s32 BtlTask_SetDead(u8 *a0);

s32 func_00155150(u8 *task) {
    u8 sp[0x70];
    u8 *buf = sp;
    f32 *vec = (f32 *)(sp + 0x10);
    u8 *mat = sp + 0x20;
    u8 *d = *(u8 **)(task + 0x38);
    u8 *obj = *(u8 **)(d + 0xB0);
    u8 *scene = *(u8 **)(func_001F3758(task) + 0x38);
    u8 *ptr;
    u8 *cfg;
    u8 *p30;
    u8 *p80;
    s32 advance = 0;
    s32 res;
    s32 flags;
    s32 hit;
    s32 st;
    f32 rx;
    f32 ry;
    f32 fy;

    __builtin_memset(vec, 0, 0x10);
    __builtin_memset(mat, 0, 0x40);
    *(s32 *)(sp + 0x60) = 0;
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
                *(s32 *)(d + 4) = 0x2F;
                *(s32 *)(d + 0x870) = 0x2F;
                func_00208DE8(*(s32 *)obj, buf, 0x2F);
                func_00129C28(d + 0x40, buf);
                task[1] = 1;
            }
            break;
        case 1:
            advance = 1;
            break;
        case 2:
            *(f32 *)(d + 0x1C) = func_0020A068(*(s32 *)obj);
            *(f32 *)(d + 0x18) = *(f32 *)(d + 0x14) * (*(f32 *)(d + 0x1C) + 1.0f);
            func_00208DE8(*(s32 *)obj, buf, *(s32 *)(d + 4));
            func_00129C28(d + 0x40, buf);
            if (EftShot_TestBits(*(s32 *)obj, 0x40) != 0) {
                *(s32 *)(d + 0xC) = *(s32 *)(d + 0x9B0);
                func_00208DE8(*(s32 *)obj, buf, *(s32 *)(d + 0xC));
                func_00129C28(d + 0x60, buf);
                *(u32 *)d |= 0x40;
            }
            if (EftShot_TestBits(*(s32 *)obj, 4) != 0) {
                *(s32 *)(d + 0x8B0) = 0x2F;
                func_00152960(*(s32 *)obj, obj);
                *(s32 *)(d + 8) = *(s32 *)(d + 0x8B0);
                *(u32 *)d |= 0x10;
                func_00208DE8(*(s32 *)obj, buf, *(s32 *)(d + 8));
                func_00129C28(d + 0x50, buf);
                func_00129C28(d + 0x70, d + 0x50);
                func_00129C28(d + 0x80, d + 0x70);
                func_00208DE8(*(s32 *)obj, d + 0x90, 0x11);
                func_0012D3A0((u8 *)vec, d + 0x80, *(s32 *)obj);
                Mtx_StoreIdentity(mat);
                rx = EftMath_WrapAngle(Mathf_Asin(-vec[1]));
                ry = EftMath_WrapAngle(atan2f(vec[0], vec[2]));
                Mtx_RotateX(mat, mat, rx);
                Mtx_RotateY(mat, mat, ry);
                func_00129C50(d + 0x30, mat, d + 0x30);
                func_00129BD0(d + 0xA0, d + 0x30, *(f32 *)(d + 0x10));
                task[1] = 3;
            }
            break;
        case 3:
            *(s32 *)(sp + 0x60) = 1;
            Vec4_Set(d + 0x30, 0.0f, 0.0f, 1.0f, 1.0f);
            break;
        case 4:
            p80 = d + 0x80;
            func_00129C28(d + 0x90, p80);
            cfg = *(u8 **)(*(u8 **)(d + 0xB0) + 0x20);
            if ((*(u32 *)(cfg + 0x30) & 2) == 0 && (*(u32 *)d & 0x20) == 0) {
                p30 = d + 0x30;
                ptr = d + 0xA0;
                if (0.0f < *(f32 *)(cfg + 0x18)) {
                    func_0012D5D8(p30, p80, p30, *(s32 *)obj, *(f32 *)(d + 0x10), *(f32 *)(cfg + 0x18));
                    func_00129BD0(ptr, p30, *(f32 *)(d + 0x10));
                }
                fy = *(f32 *)(d + 0xA4);
                *(f32 *)(d + 0xA4) = fy + D_00384694;
                Vec3_Add(p80, p80, ptr);
            }
            func_00208DE8(*(s32 *)obj, buf, *(s32 *)(d + 8));
            func_00129C28(d + 0x50, buf);
            if (EftShot_TestBits(*(s32 *)obj, 8) != 0) {
                *(u32 *)d |= 9;
                task[1] = 5;
            }
            break;
        case 5:
            *(s32 *)(sp + 0x60) = 1;
            break;
        }
    }

    ptr = d + 0xB4;
    if (EftShot_TestBits(*(s32 *)obj, 0x80) != 0) {
        flags = *(s32 *)d;
        if ((flags & 8) == 0) {
            flags |= 4;
        }
        *(s32 *)d = flags | 1;
    }
    func_00151FB0(ptr);
    func_00154ED8(*(s32 *)obj, task, scene, 0);
    hit = func_00152200(scene, ptr) != 0;
    if (*(s32 *)(sp + 0x60) != 0) {
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
        return flags & 1;
    }
    if ((flags & 0x10) == 0) {
        return 0;
    }
    func_00152930(scene, ptr);
    return func_00154D10(task);
}
