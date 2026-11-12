#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
s32 BtlScene_IsEffectStopped(u8 *arg0, s32 arg1);
void Mtx_StoreIdentity(u8 *arg0);
void Vec3_Sub(u8 *arg0, u8 *arg1, u8 *arg2);
f32 func_00129E08(u8 *arg0);
void Vec3_Normalize(u8 *arg0, u8 *arg1);
void func_00184F18(u8 *arg0);
void Vec3_Add(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00187568(u8 *arg0, f32 arg1, f32 arg2);
f32 EftMath_WrapAngle(f32 arg0);
void func_00186040(u8 *arg0, u8 *arg1, u8 *arg2, f32 arg3, f32 arg4, f32 arg5);
void func_00185D50(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, f32 arg4, f32 arg5, f32 arg6);
void func_00185C68(u8 *arg0, u8 *arg1, u8 *arg2);
void BtlTask_SetDead(u8 *arg0);

void func_00184208(u8 *arg0) {
    u8 frame[0x40];
    u8 *ctx;
    u8 *s3;
    u8 *s4;
    u8 *node;
    u8 *head;
    s32 v1;
    s32 flags;
    s32 rem;
    s32 divisor;
    s32 cnt;
    s32 fl;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f20;

    ctx = *(u8 **)(arg0 + 0x38);
    s3 = *(u8 **)(ctx + 0x30);
    memset(frame, 0, 0x40);
    if (BtlScene_IsEffectStopped(*(u8 **)(ctx + 0x94), *(u8 *)(ctx + 0x1A0))) {
        return;
    }
    Mtx_StoreIdentity(frame);

    f1 = *(f32 *)(ctx + 0x8C);
    if (0.0f < f1) {
        *(f32 *)(ctx + 0x8C) = f1 - 1.0f;
        return;
    }
    s4 = ctx + 0x70;
    Vec3_Sub(s4, ctx + 0x60, ctx + 0x50);
    *(f32 *)(ctx + 0x88) = func_00129E08(s4);
    Vec3_Normalize(s4, s4);

    flags = *(s32 *)(ctx + 0x19C);
    if (flags & 4) {
        f1 = *(f32 *)(ctx + 0x90);
        if (0.0f < f1) {
            func_00184F18(ctx);
            f1 = *(f32 *)(ctx + 0x90);
        } else {
            *(s32 *)(ctx + 0x19C) = flags | 0x10;
        }
        *(f32 *)(ctx + 0x90) = f1 - 1.0f;
    } else {
        func_00184F18(ctx);
    }

    /* 184310 */
    head = *(u8 **)(ctx + 0x1A4);
    if (head == 0) {
        goto L45E8;
    }
    node = head;
    while (node != 0) {
        f1 = *(f32 *)(node + 0xB4);
        if (0.0f <= f1) {
            *(f32 *)(node + 0xB4) = f1 - 1.0f;
        } else {
            fl = *(u16 *)(node + 0xBE);
            if (!(fl & 2)) {
                if (*(s32 *)(ctx + 0x19C) & 0x10) {
                    *(u16 *)(node + 0xBE) = 0;
                    func_00185C68(ctx + 0x1A4, ctx + 0x1A8, node);
                    fl = *(u16 *)(node + 0xBE);
                }
            }
            f0 = *(f32 *)(node + 0xB0);
            f20 = f0 / *(f32 *)(node + 0xB8);
            if (fl & 2) {
                if (f20 < *(f32 *)(s3 + 0x78)) {
                    fl = fl | 0x40;
                } else {
                    fl = fl & 0xFFBF;
                }
                *(u16 *)(node + 0xBE) = fl;
                if (*(f32 *)(s3 + 0x7C) <= f20 && f20 < 1.0f) {
                    fl = fl | 0x80;
                    *(u16 *)(node + 0xBE) = fl;
                }
                if (*(f32 *)(s3 + 0x80) <= f20) {
                    fl = (fl & 0xFFFE) | 8;
                    *(u16 *)(node + 0xBE) = fl;
                }
            }
            if (fl & 0x40) {
                *(f32 *)(node + 0x2C) = *(f32 *)(node + 0x2C) + *(f32 *)(node + 0x80);
            }
            if (fl & 0x80) {
                *(f32 *)(node + 0x2C) = *(f32 *)(node + 0x2C) - *(f32 *)(node + 0x84);
            }
            if (!(fl & 0x100)) {
                Vec3_Add(node + 0x20, node + 0x20, node + 0x30);
            }
            func_00187568(node + 0x20, 0.0f, 255.0f);

            fl = *(u16 *)(node + 0xBE);
            if (fl & 1) {
                f0 = *(f32 *)(node + 0x88) + *(f32 *)(node + 0x90);
                f1 = *(f32 *)(node + 0x8C) + *(f32 *)(node + 0x98);
                *(f32 *)(node + 0x88) = f0;
                *(f32 *)(node + 0x8C) = f1;
            }
            if (fl & 8) {
                f0 = *(f32 *)(node + 0x88) + *(f32 *)(node + 0x94);
                f1 = *(f32 *)(node + 0x8C) + *(f32 *)(node + 0x9C);
                *(f32 *)(node + 0x88) = f0;
                *(f32 *)(node + 0x8C) = f1;
            }
            f1 = *(f32 *)(node + 0xA4);
            *(f32 *)(node + 0xA4) = EftMath_WrapAngle(f1 + *(f32 *)(node + 0xA8));

            v1 = *(s32 *)(s3 + 0xA4);
            if ((v1 & 2) && (v1 & 8)) {
                func_00186040(node, frame, ctx + 0x40, *(f32 *)(ctx + 0x80), *(f32 *)(s3 + 0x34), *(f32 *)(s3 + 0x38));
                v1 = *(s32 *)(s3 + 0xA4);
            }
            if ((v1 & 1) && (v1 & 0x20)) {
                func_00185D50(node, frame, ctx + 0x40, ctx + 0x70, *(f32 *)(ctx + 0x80), *(f32 *)(s3 + 0x34), *(f32 *)(s3 + 0x38));
            }

            /* 18453C */
            f2 = *(f32 *)(node + 0xB0);
            divisor = *(u8 *)(s3 + 0xA2);
            {
                s32 q = (s32)f2;
                f32 t = f2;
                s32 i = (s32)t;
                f32 d = t - (f32)i;
                if (d > 0.5f || (d == 0.5f && (i & 1))) {
                    i++;
                } else if (d < -0.5f || (d == -0.5f && (i & 1))) {
                    i--;
                }
                q = i;
                rem = q % divisor;
            }
            if (rem == 0) {
                *(u8 *)(node + 0xBD) = *(u8 *)(node + 0xBD) + 1;
            }
            cnt = *(u8 *)(node + 0xBD);
            if (!(cnt < *(u8 *)(ctx + 0x199))) {
                *(u8 *)(node + 0xBD) = 0;
            }

            f0 = *(f32 *)(node + 0xB0) + 1.0f;
            *(f32 *)(node + 0xB0) = f0;
            if (*(f32 *)(node + 0xB8) <= f0) {
                fl = *(u16 *)(node + 0xBE);
                if (fl & 2) {
                    *(u16 *)(node + 0xBE) = fl & 0xFFFD;
                }
            }
        }
        node = *(u8 **)(node + 0xC0);
    }

L45E8:
    v1 = *(s32 *)(ctx + 0x1A4);
    flags = *(s32 *)(ctx + 0x19C);
    if (!(flags & 4)) {
        f1 = *(f32 *)(ctx + 0x84);
        if (0.0f < f1) {
            f0 = f1 - 1.0f;
            *(f32 *)(ctx + 0x84) = f0;
            if (f0 <= 0.0f) {
                flags = flags | 4;
                *(f32 *)(ctx + 0x84) = 0.0f;
                *(s32 *)(ctx + 0x19C) = flags;
            }
        }
    }
    if (flags & 0x20) {
        node = *(u8 **)(ctx + 0x1A4);
        if (node != 0) {
            *(u16 *)(node + 0xBE) = 0;
            while (node != 0) {
                func_00185C68(ctx + 0x1A4, ctx + 0x1A8, node);
                node = *(u8 **)(node + 0xC0);
                if (node != 0) {
                    *(u16 *)(node + 0xBE) = 0;
                }
            }
            v1 = *(s32 *)(ctx + 0x1A4);
        }
    }

    /* 184678 */
    if (v1 != 0) {
        return;
    }
    if (*(s32 *)(ctx + 0x19C) & 0x10) {
        *(s32 *)(ctx + 0x19C) = 0;
        BtlTask_SetDead(arg0);
    }
}
