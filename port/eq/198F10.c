#include "common.h"

extern u8 *gEftGlow;
extern u8 *gEftGlowCfg;
extern u8 *gEftGlowCfg2;
extern f32 D_00384D40;

void func_00197680(u8 *arg0, s32 arg1);
void func_00128900(u8 *arg0, u8 *arg1);
void func_00129C50(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00129B28(u8 *arg0, u8 *arg1, u8 *arg2);
void EftGlow_GetShapePoint(u8 *arg0, s32 arg1, s32 arg2, f32 arg3);
void EftGlow_GetShapeDir(u8 *arg0, s32 arg1, s32 arg2, f32 arg3);
void Mtx_StoreIdentity(u8 *arg0);
void Mtx_RotateZ(u8 *arg0, u8 *arg1, f32 arg2);
void func_00129BD0(u8 *arg0, u8 *arg1, f32 arg2);
void Vec3_Normalize(u8 *arg0, u8 *arg1);
f32 EftGlow_CalcWidth(u8 *arg0, s32 arg1);
f32 EftGlow_CalcLength(u8 *arg0, s32 arg1);
void func_00129D68(u8 *arg0, u8 *arg1, f32 arg2, f32 arg3);

void func_00198F10(u8 *arg0, s32 arg1) {
    u8 frame[0xC0];
    u8 *link;
    u8 *node;
    u8 *s0;
    u8 *s1;
    u8 *s3;
    u8 *s5;
    s32 flags;
    s32 t;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f12;
    f32 f20;
    f32 f22;

    *(s32 *)(arg0 + 0x30) = 0;
    func_00197680(frame + 0xA0, arg1);
    f22 = 1.0f;

    link = gEftGlow + 0x10;
    node = *(u8 **)link;
    if (node == 0) {
        return;
    }
    while (node != 0) {
        if (*(u8 *)(node + 7) != arg1) {
            link = node + 0xB0;
            goto next;
        }
        f20 = 0.0f;
        f0 = *(f32 *)(node + 0x10);
        if (!(f20 < f0)) {
            /* dead node: unlink, push onto the free list */
            *(u8 **)link = *(u8 **)(node + 0xB0);
            *(u8 **)(node + 0xB0) = *(u8 **)(gEftGlow + 0xC);
            *(u8 **)(gEftGlow + 0xC) = node;
            goto next;
        }

        /* live node of this type */
        func_00128900(frame + 0x40, arg0 + (*(u8 *)(node + 8) << 6) + 0x50);
        t = *(u8 *)(node + 8) + 1;
        if ((t & 0xFF) < 5) {
            *(u8 *)(node + 8) = t;
        } else {
            *(u8 *)(node + 8) = 4;
        }
        func_00129C50(frame + 0x80, frame + 0x40, node + 0x70);

        s1 = node + 0x40;
        s0 = node + 0x80;
        s5 = node + 0x90;
        func_00129B28(s1, arg0 + (*(u8 *)(node + 0xD) << 4) + 0x1B0, frame + 0x80);

        f12 = *(f32 *)(arg0 + 0x48) * *(f32 *)(node + 0x34);
        EftGlow_GetShapePoint(s0, arg1, *(u8 *)(node + 0xE), f12);
        EftGlow_GetShapeDir(s5, arg1, *(u8 *)(node + 0xE), *(f32 *)(node + 0x3C));

        Mtx_StoreIdentity(frame);
        Mtx_RotateZ(frame, frame, (*(f32 *)(node + 0x38) / 180.0f) * D_00384D40);

        func_00129C50(frame + 0x90, frame, node + 0x80);
        func_00129C50(node + 0x90, frame, node + 0x90);
        func_00129C50(frame + 0x90, frame + 0x40, frame + 0x90);
        func_00129B28(s1, s1, frame + 0x90);
        *(f32 *)(node + 0x4C) = 1.0f;

        s3 = node + 0xA0;
        func_00129C50(s3, frame + 0x40, s5);

        flags = *(s32 *)node;
        if (!(flags & 2)) {
            func_00129B28(s3, s3, frame + 0xA0);
            Vec3_Normalize(s3, s3);
            flags = *(s32 *)node;
        }
        f1 = *(f32 *)(node + 0x1C);

        /* 199144: integrate the two counters */
        f2 = *(f32 *)(node + 0x2C);
        f3 = *(f32 *)(node + 0x20);
        f1 = f1 + f2;
        f0 = *(f32 *)(node + 0x30);
        f3 = f3 + f0;
        *(f32 *)(node + 0x1C) = f1;
        *(f32 *)(node + 0x20) = f3;
        if (f1 < f20) {
            *(f32 *)(node + 0x1C) = 0.0f;
        }
        if (*(f32 *)(node + 0x20) < f20) {
            *(f32 *)(node + 0x20) = 0.0f;
        }

        /* 199180 */
        flags = *(s32 *)node;
        if (!(flags & 4)) {
            f2 = *(f32 *)(node + 0x10);
            f3 = *(f32 *)(node + 0x14);
            if (*(f32 *)gEftGlowCfg2 < 1.0f - f2 / f3) {
                f0 = EftGlow_CalcWidth(node, 2);
                f1 = *(f32 *)(node + 0x1C);
                f2 = *(f32 *)(node + 0x10);
                f0 = (f0 - f1) / f2;
                *(f32 *)(node + 0x2C) = f0;
                f0 = EftGlow_CalcLength(node, 2);
                f1 = *(f32 *)(node + 0x20);
                f2 = *(f32 *)(node + 0x10);
                f0 = f0 - f1;
                *(s32 *)node = *(s32 *)node | 4;
                f3 = *(f32 *)(node + 0x14);
                f0 = f0 / f2;
                *(f32 *)(node + 0x30) = f0;
            } else {
                f3 = *(f32 *)(node + 0x14);
            }
        } else {
            f2 = *(f32 *)(node + 0x10);
            f3 = *(f32 *)(node + 0x14);
        }
        f1 = f3 - f2;

        /* 199220 */
        if (f1 < *(f32 *)(gEftGlowCfg + 0x1A8)) {
            s0 = node + 0x50;
            goto L9288;
        }
        s0 = node + 0x50;
        if (!(f2 <= *(f32 *)(gEftGlowCfg + 0x1AC))) {
            *(f32 *)(node + 0x6C) = 0.0f;
            goto L9288;
        }

        flags = *(s32 *)node;
        if (!(flags & 1)) {
            f1 = f2 + f22;
            f2 = *(f32 *)(arg0 + 0x1AC);
            f0 = *(f32 *)(node + 0x5C);
            *(s32 *)node = flags | 1;
            f0 = f0 - f2;
            f1 = f22 / f1;
            f0 = -f0;
            f0 = f0 * f1;
            *(f32 *)(node + 0x6C) = f0;
        }
        goto L928C;

    L9288:
        /* 19928C: a2 is node+0x60 on every path here */
    L928C:
        func_00129B28(s0, s0, node + 0x60);
        func_00129D68(s0, s0, 0.0f, 1.0f);

        /* 1992B0 */
        flags = *(s32 *)node;
        if (flags & 2) {
            f32 x;
            f32 g;
            x = *(f32 *)(node + 0x10) / *(f32 *)(node + 0x14);
            f2 = *(f32 *)(node + 0x7C) * *(f32 *)(arg0 + 0x48);
            f1 = *(f32 *)(gEftGlowCfg2 + 0x18);
            f0 = x * x;
            f0 = f0 * x;
            f12 = x * f0;
            f12 = f12 * f2;
            g = f1 * f12;
            func_00129BD0(frame + 0xB0, s5, g);
            func_00129B28(node + 0x70, node + 0x70, frame + 0xB0);
        }

        /* 19931C */
        *(u8 *)(node + 0xB) = *(u8 *)(node + 0xB) + 1;
        t = *(u8 *)(node + 0xB);
        f1 = (f32)t;
        f0 = *(f32 *)(gEftGlowCfg2 + 4);
        if (f0 <= f1) {
            *(u8 *)(node + 0xB) = 0;
            t = *(u8 *)(node + 0xA) + 1;
            *(u8 *)(node + 0xA) = t;
            if (!((t & 0xFF) < 2)) {
                *(u8 *)(node + 0xA) = 0;
            }
        }

        /* 19936C */
        f0 = *(f32 *)(node + 0x10) - f22;
        *(f32 *)(node + 0x10) = f0;
        *(s32 *)(arg0 + 0x30) = *(s32 *)(arg0 + 0x30) + 1;
        link = node + 0xB0;

    next:
        node = *(u8 **)link;
    }
}
