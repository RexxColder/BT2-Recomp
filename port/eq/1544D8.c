#include "common.h"

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))

extern f32 D_0038468C;

extern s32 func_001F3758(u8 *obj);
extern s32 BtlScene_IsCharStopped(s32 arg0);
extern void func_00152530(u8 *s5, u8 *p);
extern s32 EftShot_TestBits(s32 arg0, s32 arg1);
extern s32 func_00208DE8(s32 a0, u8 *a1, s32 a2);
extern void func_00129C28(u8 *dst, u8 *src);
extern void func_0012D3A0(u8 *a0, u8 *a1, s32 a2);
extern s32 func_0020B3D0(s32 arg0);
extern void Vec3_Sub(u8 *dst, u8 *a, u8 *b);
extern void Vec3_ScaleAdd(u8 *dst, u8 *a, u8 *b, f32 s);
extern void Vec4_Sub(u8 *dst, u8 *a, u8 *b);
extern f32 Vec3_Dot(u8 *a, u8 *b);
extern void Vec3_Normalize(u8 *dst, u8 *src);
extern void Vec3_Scale(u8 *dst, u8 *src, f32 s);
extern void Vec3_Add(u8 *dst, u8 *a, u8 *b);
extern void func_00147FB8(s32 arg0);
extern void *EftBlastObj_Create(u8 *arg);
extern s32 func_001919C8(void *task);
extern s32 func_00191728(s32 task);
extern void func_00151FB0(u8 *p);
extern void func_00154260(s32 a0, u8 *obj, s32 a2, s32 a3);
extern s32 func_00152200(s32 a0, u8 *a1);
extern s32 BtlTask_SetDead(u8 *obj);
extern void func_00152930(s32 a0, u8 *a1);
extern void func_00154098(u8 *obj);

/* Blast/beam effect task update: state machine on obj[1] (0..5) driven by EftShot_TestBits(owner, bit), then
   spawns 8 blast objects once and retires the task when all of them are dead. */
void func_001544D8(u8 *obj) {
    u8 sp[0x40];
    u8 *st;
    u8 *owner;
    s32 scene;
    s32 stepFlag = 0;
    s32 anyAlive = 0;
    u8 *vec = sp;
    s32 i;
    s32 flags;
    s32 busy;
    u8 *blast;
    u8 *entry;
    f32 len;

    scene = W((u8 *)func_001F3758(obj), 0x38);
    st = *(u8 **)(obj + 0x38);
    owner = *(u8 **)(st + 0xC0);
    if (BtlScene_IsCharStopped(W(owner, 0))) {
        return;
    }
    func_00152530(owner, st + 0x870);

    if (!(W(st, 0) & 0x80)) {
        if (EftShot_TestBits(W(owner, 0), 2)) {
            obj[1] = 0;
            W(st, 0) |= 0x80;
        } else if (EftShot_TestBits(W(owner, 0), 4)) {
            obj[1] = 2;
            W(st, 0) |= 0x80;
        }
    }
    if (W(st, 0) & 0x80) {
        switch (obj[1]) {
        case 0:
            if (EftShot_TestBits(W(owner, 0), 2)) {
                W(st, 4) = W(st, 0x880);
                func_00208DE8(W(owner, 0), vec, W(st, 0x880));
                func_00129C28(st + 0x40, vec);
                func_0012D3A0(st + 0x30, st + 0x40, W(owner, 0));
                obj[1] = 1;
            }
            break;
        case 1:
        case 3:
        case 5:
            stepFlag = 1;
            break;
        case 2:
            func_00208DE8(W(owner, 0), vec, W(st, 4));
            func_00129C28(st + 0x40, vec);
            if (EftShot_TestBits(W(owner, 0), 0x40)) {
                W(st, 0xC) = W(st, 0x9C0);
                func_00208DE8(W(owner, 0), vec, W(st, 0x9C0));
                func_00129C28(st + 0x60, vec);
                W(st, 0) |= 0x40;
            }
            if (EftShot_TestBits(W(owner, 0), 4)) {
                W(st, 8) = W(st, 0x8C0);
                func_00208DE8(W(owner, 0), vec, W(st, 0x8C0));
                func_00129C28(st + 0x50, vec);
                func_00129C28(st + 0x80, st + 0x50);
                func_00129C28(st + 0x90, st + 0x80);
                func_00208DE8(W(owner, 0), st + 0xA0, 0x11);
                func_0012D3A0(st + 0x30, st + 0x90, W(owner, 0));
                func_00208DE8(func_0020B3D0(W(owner, 0)), st + 0x70, 0x11);
                Vec3_Sub(st + 0x70, st + 0x70, st + 0x80);
                Vec3_ScaleAdd(st + 0x70, st + 0x70, st + 0x80, D_0038468C);
                F(st, 0x74) = F(st, 0x74) - 200.0f;
                Vec4_Sub(st + 0x30, st + 0x70, st + 0x80);
                F(st, 0x3C) = 1.0f;
                len = __builtin_sqrtf(Vec3_Dot(st + 0x30, st + 0x30));
                F(st, 0x14) = len / F(st, 0x1C);
                Vec3_Normalize(st + 0x30, st + 0x30);
                obj[1] = 3;
            }
            break;
        case 4:
            func_00129C28(st + 0xA0, st + 0x90);
            if (!(W(*(u8 **)(*(u8 **)(st + 0xC0) + 0x20), 0x30) & 2) && !(W(st, 0) & 0x20) && F(st, 0x20) > 0.0f) {
                Vec3_Scale(st + 0xB0, st + 0x30, F(st, 0x14));
                Vec3_Add(st + 0x90, st + 0x90, st + 0xB0);
                F(st, 0x20) = F(st, 0x20) - 1.0f;
            }
            func_00208DE8(W(owner, 0), vec, W(st, 8));
            func_00129C28(st + 0x50, vec);
            if (EftShot_TestBits(W(owner, 0), 8)) {
                W(st, 0) |= 9;
                obj[1] = 5;
            }
            break;
        default:
            break;
        }
    }

    if (EftShot_TestBits(W(owner, 0), 0x80)) {
        flags = W(st, 0);
        if (!(flags & 8)) {
            W(st, 0) = flags | 4;
            flags |= 4;
        }
        W(st, 0) = flags | 1;
    }
    flags = W(st, 0);

    if (!(flags & 1) && F(st, 0x20) <= 0.0f && !(flags & 0x200)) {
        func_00147FB8(W(owner, 0));
        entry = st + 0xAC4;
        for (i = 0; i < 8; i++) {
            u8 blk[0x30];

            *(u8 **)(blk + 0x00) = owner;
            W(blk, 0x04) = scene;
            *(u8 **)(blk + 0x08) = st + 0x870;
            *(u8 **)(blk + 0x0C) = st + 0x90;
            *(u8 **)(blk + 0x10) = st + 0x30;
            W(blk, 0x14) = i;
            W(blk, 0x18) = 8;
            W(blk, 0x1C) = 4;
            W(blk, 0x20) = 2;
            W(blk, 0x24) = 0;
            F(blk, 0x28) = F(st, 0x18);
            F(blk, 0x2C) = F(*(u8 **)(owner + 0x24), 8);
            blast = EftBlastObj_Create(blk);
            *(u8 **)entry = blast;
            entry += 8;
            func_001919C8(blast);
        }
        W(st, 0) |= 0x200;
        flags = W(st, 0);
    }
    if (flags & 0x200) {
        entry = st + 0xAC0;
        for (i = 7; i >= 0; i--) {
            if (func_00191728(W(entry, 4))) {
                anyAlive = 1;
            } else {
                W(entry, 4) = 0;
            }
            entry += 8;
        }
        if (!anyAlive) {
            W(st, 0) |= 1;
        }
    }

    func_00151FB0(st + 0xC4);
    func_00154260(W(owner, 0), obj, scene, 0);
    busy = func_00152200(scene, st + 0xC4) != 0;
    if (stepFlag) {
        obj[1] = obj[1] + 1;
    }
    flags = W(st, 0);
    if (!anyAlive && !busy) {
        if (flags & 2) {
            BtlTask_SetDead(obj);
            return;
        }
    }
    if (flags & 1) {
        W(st, 0) = flags | 2;
    } else if ((W(*(u8 **)(owner + 0x20), 0x30) & 1) && (flags & 0x10)) {
        func_00152930(scene, st + 0xC4);
        func_00154098(obj);
    }
}
