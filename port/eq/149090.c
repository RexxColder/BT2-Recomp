#include "common.h"

extern u8 *func_001F3758(u8 *task);
extern s32 func_0020B3D0(s32 obj);
extern s32 BtlScene_IsCharStopped(s32 obj);
extern s32 func_0020AB90(s32 obj);
extern void func_00126DE0(void *req);
extern void func_00152530(u8 *a, u8 *b);
extern s32 EftShot_TestBits(s32 obj, s32 bits);
extern void func_00208DE8(s32 obj, u8 *dst, s32 idx);
extern void func_0012D3A0(u8 *dst, u8 *src, s32 obj);
extern void func_00129C28(u8 *dst, u8 *src);
extern void func_00129BD0(u8 *dst, u8 *src, f32 s);
extern void func_00129BB8(u8 *dst, u8 *src, f32 s);
extern void func_0020D3B0(s32 obj, u8 *vec, f32 s);
extern void Vec3_Sub(u8 *dst, u8 *a, u8 *b);
extern void Vec3_Normalize(u8 *dst, u8 *src);
extern f32 func_00129CD8(u8 *a, u8 *b);
extern void func_0012A360(u8 *dst, u8 *dir, u8 *base, f32 len);
extern void func_0019F8D0(u8 *p);
extern void func_001DBF28(u8 *pkt);
extern void func_00151FB0(u8 *p);
extern void func_00148E20(s32 obj, u8 *task, u8 *scene);
extern s32 func_00152200(u8 *scene, u8 *p);
extern s32 func_0020A758(s32 obj);
extern void func_00148C50(u8 *task);
extern s32 BtlTask_SetDead(u8 *task);
extern u8 D_0036DE40[0x20];

/* Beam/shot effect task update: a 6-state machine (task[1]) that follows the owner object's bone points,
   with a flash packet in state 4; ends the task when the effect finishes. */
s32 func_00149090(u8 *task) {
    u8 *fx = *(u8 **)(task + 0x38);
    u8 *own = *(u8 **)(fx + 0x90);
    u8 *scene = *(u8 **)(func_001F3758(task) + 0x38);
    s32 obj;
    s32 owner;
    u8 *dir;
    u8 *org;
    u8 *p60;
    u8 *p20;
    u8 *vec;
    s32 advance = 0;
    s32 done;
    s32 stopped;
    u32 req[3];
    u8 v20[0x10];
    u8 v30[0x10];
    u8 cst[0x20];
    u8 pkt[0x30];
    static const u8 idxs[5] = {0, 3, 10, 14, 21};

    owner = func_0020B3D0(*(s32 *)own);
    stopped = BtlScene_IsCharStopped(*(s32 *)own);
    if (stopped != 0) {
        return stopped;
    }
    if (func_0020AB90(*(s32 *)own) != 0 && (*(u32 *)fx & 0x80) == 0) {
        req[0] = *(u32 *)(scene + 0x1E80);
        req[1] = *(u32 *)own;
        req[2] = **(u32 **)(own + 0x20);
        func_00126DE0(req);
        *(u32 *)fx |= 0x80;
    }
    if ((*(u32 *)fx & 0x80) != 0) {
        *(s32 *)(fx + 0x10) += 1;
    }
    func_00152530(own, fx + 0x840);

    obj = *(s32 *)own;
    switch (task[1]) {
    case 0:
        if (EftShot_TestBits(obj, 2) != 0) {
            *(s32 *)(fx + 4) = 0x15;
            func_00208DE8(*(s32 *)own, fx + 0x30, 0x15);
            func_0012D3A0(fx + 0x20, fx + 0x30, *(s32 *)own);
            task[1] = 1;
        }
        break;
    case 1:
        advance = 1;
        break;
    case 2:
        func_00208DE8(*(s32 *)own, fx + 0x30, *(s32 *)(fx + 4));
        if (EftShot_TestBits(*(s32 *)own, 4) != 0) {
            *(s32 *)(fx + 8) = 0x15;
            func_00208DE8(*(s32 *)own, fx + 0x40, 0x15);
            func_00129C28(fx + 0x50, fx + 0x40);
            func_00129C28(fx + 0x60, fx + 0x50);
            func_00129C28(fx + 0x70, fx + 0x60);
            func_0012D3A0(fx + 0x20, fx + 0x60, *(s32 *)own);
            func_00129BD0(fx + 0x80, fx + 0x20, *(f32 *)(fx + 0x14));
            *(u32 *)fx |= 0x100;
            task[1] = 3;
        }
        break;
    case 3:
        advance = 1;
        break;
    case 4:
        dir = fx + 0x20;
        if ((*(u32 *)(*(u8 **)(own + 0x20) + 0x30) & 0x10) != 0) {
            func_00129BB8(v20, dir, -1.0f);
            func_0020D3B0(*(s32 *)own, v20, 4.0f);
        }
        if (EftShot_TestBits(*(s32 *)own, 0x10) != 0) {
            *(u32 *)fx |= 0x400;
        }
        org = fx + 0x40;
        p60 = fx + 0x60;
        func_00208DE8(*(s32 *)own, org, *(s32 *)(fx + 8));
        func_00129C28(fx + 0x70, p60);
        if ((*(u32 *)fx & 0x400) != 0) {
            func_00208DE8(*(s32 *)own, p60, 0x1F);
            Vec3_Sub(v30, p60, org);
            Vec3_Normalize(v30, v30);
            func_0012A360(p60, v30, org, 30.0f);
        } else {
            f32 len;
            func_00208DE8(owner, p60, 3);
            Vec3_Sub(v30, p60, org);
            len = __builtin_sqrtf(__builtin_fabsf(func_00129CD8(v30, v30))) + 30.0f;
            Vec3_Normalize(v30, v30);
            func_0012A360(p60, v30, org, len);
        }
        func_00129C28(dir, v30);
        if (EftShot_TestBits(owner, 0x40) != 0) {
            u32 idx;
            __builtin_memcpy(cst, D_0036DE40, 0x20);
            func_0019F8D0(cst);
            *(f32 *)(pkt + 0x00) = *(f32 *)(fx + 0x40);
            *(f32 *)(pkt + 0x04) = *(f32 *)(fx + 0x44);
            *(f32 *)(pkt + 0x08) = *(f32 *)(fx + 0x48);
            *(f32 *)(pkt + 0x0C) = 1.0f;
            *(u32 *)(pkt + 0x10) = *(u32 *)own;
            *(u32 *)(pkt + 0x14) = 0x47;
            *(u32 *)(pkt + 0x18) = 1;
            *(u32 *)(pkt + 0x1C) = 1;
            *(u32 *)(pkt + 0x24) = 0;
            for (idx = 0; idx < 5; idx++) {
                *(u32 *)(pkt + 0x20) = idxs[idx];
                func_001DBF28(pkt);
            }
        }
        if (EftShot_TestBits(*(s32 *)own, 8) != 0) {
            *(u32 *)fx |= 9;
            task[1] = 5;
        }
        break;
    case 5:
        advance = 1;
        break;
    default:
        break;
    }

    if (EftShot_TestBits(*(s32 *)own, 0x80) != 0) {
        if ((*(u32 *)fx & 8) == 0) {
            *(u32 *)fx |= 4;
        }
        *(u32 *)fx |= 1;
    }
    vec = fx + 0x94;
    func_00151FB0(vec);
    func_00148E20(*(s32 *)own, task, scene);
    done = func_00152200(scene, vec) != 0;
    if (advance != 0) {
        task[1] += 1;
    }
    if (func_0020A758(*(s32 *)own) != 0) {
        func_00148C50(task);
    }
    if (!done && (*(u32 *)fx & 2) != 0) {
        return BtlTask_SetDead(task);
    }
    if ((*(u32 *)fx & 1) == 0) {
        return 0;
    }
    *(u32 *)fx |= 2;
    return *(u32 *)fx;
}
