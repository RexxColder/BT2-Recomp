#include "common.h"

extern u8 *func_001F3758(void *a0);
extern void func_0012D488(void *arg0, void *arg1, void *arg2, s32 arg3);
extern f32 Mathf_Asin(f32 farg0);
extern f32 atan2f(f32 farg0, f32 farg1);
extern void Mtx_StoreIdentity(void *arg0);
extern void Mtx_RotateX(f32 farg0, void *arg0, void *arg1);
extern void Mtx_RotateY(f32 farg0, void *arg0, void *arg1);
extern void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
extern void func_00129C50(void *arg0, void *arg1, void *arg2);
extern s32 rand(void);
extern void Vec3_Add(void *arg0, void *arg1, void *arg2);
extern u8 *func_0016F2B0(u8 *arg0);
extern void func_00129C28(void *arg0, void *arg1);
extern s32 func_00191600(void *arg0);
extern void func_001919C8(s32 arg0);
extern f32 D_003848A4;
extern f32 D_003848A8;
extern f32 D_003848AC;

void func_0016F438(u8 *task) {
    u8 sp[0x110];
    u8 *rotMtx = sp;
    u8 *tmpMtx = sp + 0x40;
    u8 *pos = sp + 0x80;
    u8 *dir = sp + 0x90;
    u8 *blk = sp + 0xD0;
    u8 *blkCopy = sp + 0xA0;
    u8 *st;
    u8 *owner;
    u8 *fx;
    u8 *center;
    u8 *other;
    f32 pitch;
    f32 yaw;
    f32 k;
    s32 i;
    s32 r1;
    s32 r2;
    s32 h;

    other = *(u8 **)(func_001F3758(task) + 0x38);
    st = *(u8 **)(task + 0x38);
    owner = *(u8 **)(st + 0xB0);
    center = st + 0x50;
    func_0012D488(owner, st + 0x30, st + 0x70, *(s32 *)owner);
    pitch = Mathf_Asin(-*(f32 *)(st + 0x34));
    yaw = atan2f(*(f32 *)(st + 0x30), *(f32 *)(st + 0x38));
    Mtx_StoreIdentity(rotMtx);
    Mtx_RotateX(pitch, rotMtx, rotMtx);
    Mtx_RotateY(yaw, rotMtx, rotMtx);
    for (i = 0; i < 3; i++) {
        k = (f32)i - 1.0f;
        Vec4_Set(dir, 0.0f, 0.0f, 1.0f, 1.0f);
        Mtx_StoreIdentity(tmpMtx);
        Mtx_RotateY((k * D_003848A8) * D_003848AC, tmpMtx, tmpMtx);
        func_00129C50(dir, tmpMtx, dir);
        func_00129C50(dir, rotMtx, dir);
        r1 = rand();
        r2 = rand();
        Vec4_Set(pos, k * 1.0f, (((f32)r1 / D_003848A4) - ((f32)r2 / D_003848A4)) * 8.0f, 0.0f, 1.0f);
        func_00129C50(pos, rotMtx, pos);
        Vec3_Add(pos, pos, center);
        fx = func_0016F2B0(st);
        if (fx != 0) {
            __builtin_memcpy(fx + 0x10, st + 0x860, 0x250);
            func_00129C28(fx + 0x70, pos);
            *(u8 **)(blk + 0x00) = owner;
            *(u8 **)(blk + 0x04) = other;
            *(u8 **)(blk + 0x08) = fx + 0x10;
            *(u8 **)(blk + 0x0C) = pos;
            *(u8 **)(blk + 0x10) = dir;
            *(s32 *)(blk + 0x14) = 0;
            *(s32 *)(blk + 0x18) = 0x19;
            *(s32 *)(blk + 0x1C) = 2;
            *(s32 *)(blk + 0x20) = 1;
            *(s32 *)(blk + 0x24) = 0;
            *(f32 *)(blk + 0x28) = *(f32 *)(st + 0x1C);
            *(f32 *)(blk + 0x2C) = *(f32 *)(st + 0x14);
            __builtin_memcpy(blkCopy, blk, 0x30);
            h = func_00191600(blkCopy);
            *(s32 *)(fx + 0x260) = h;
            if (!(*(s32 *)(st + 0x10) < *(s16 *)(*(u8 **)(owner + 0x20) + 0x34))) {
                func_001919C8(h);
            }
        }
    }
}
