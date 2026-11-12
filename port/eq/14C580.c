#include "common.h"

u8 *func_001F3758(u8 *arg0);
s32 func_00208DE8(u8 *arg0, u8 *arg1, s32 arg2);
void func_00129C28(u8 *dst, u8 *src);
void func_0012D488(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);
s32 func_0014EAD8(u8 *arg0);
f32 EftVolleyAim_GetFighterDistSq(void);
f32 EftVolleyAim_Lerp(f32 a, f32 b, f32 t);
f32 Rand_FloatRange(f32 lo, f32 hi);
f32 func_0030D658(f32 a, f32 b);
f32 EftMath_WrapAngle(f32 x);
f32 sinf(f32 x);
f32 cosf(f32 x);
void EftVolleyAim_GetToOpponent(u8 *a0, u8 *out);
void func_001EEDB8(f32 *arg0, f32 *arg1, f32 farg0);
void func_00208860(u8 *a0, u8 *out);
s32 func_00129B28();
f32 func_00129E30(u8 *arg0);
f32 func_00272FA8(void);
u8 *func_00211288(u8 *arg0);
f32 func_00217330(u8 *arg0);
void Vec3_RotateY(u8 *a0, u8 *a1, f32 f12);
void Vec3_RotateAxis(u8 *a0, u8 *a1, u8 *a2, f32 f12);
s32 func_00182A80(u8 *a0, u8 *a1);
s32 func_0014BF78();

extern f32 D_003845C0, D_003845C4, D_003845C8, D_003845CC, D_003845D0, D_003845D4, D_003845D8;
extern f32 D_003845DC, D_003845E0, D_003845E4, D_003845E8, D_003845EC, D_003845F0, D_003845F4;
extern f32 D_003845F8, D_003845FC, D_00384600, D_00384604, D_00384608, D_0038460C, D_00384610;
extern f32 D_00384614, D_00384618, D_0038461C, D_00384620;
extern u32 D_003415F0, D_003415F4, D_003415F8;

void func_0014C580(u8 *obj) {
    u8 sp[0xB0] __attribute__((aligned(16)));
    u8 *ctx = *(u8 **)(obj + 0x38);
    u8 *view = *(u8 **)(func_001F3758(obj) + 0x38);
    u8 *cfg = *(u8 **)(ctx + 0xB0);
    s32 frames;
    s32 mode;
    s32 n;
    s32 parity;
    f32 dist;
    f32 f;
    f32 ampX, ampY, offX, offY, angA, angB;
    u8 flag;

    if (*(s32 *)(ctx + 0xB14) == 0) {
        u32 idx = (u32)(*(s32 *)(ctx + 0x8) - 0x12);
        if (idx < 0x25) {
            *(u8 *)(ctx + 0xB19) = (idx >= 14 && idx <= 27) ? 1 : 0;
        } else {
            *(u8 *)(ctx + 0xB19) = 0;
        }
    }

    flag = (*(u8 *)(ctx + 0xB18) != 0);
    sp[0] = flag;
    if (*(s32 *)(ctx + 0xB14) + 1 == *(s16 *)(*(u8 **)(cfg + 0x20) + 0x34)) {
        sp[0] = flag | 4;
    }
    sp[2] = 0;
    sp[1] = *(u8 *)(ctx + 0xB14);
    ampX = D_003845C0;
    offX = D_003845C4;
    ampY = ampX;
    offY = offX;
    angB = 1.0f;
    *(s16 *)(sp + 4) = (s16)(s32)(*(f32 *)(cfg + 0x10) * 30.0f);
    *(f32 *)(sp + 8) = *(f32 *)(*(u8 **)(cfg + 0x24) + 4);
    *(u8 **)(sp + 0x24) = view;
    sp[0x12] = 1;
    *(f32 *)(sp + 0xC) = 1.0f;
    *(u8 **)(sp + 0x18) = (u8 *)func_0014BF78;
    *(u8 **)(sp + 0x20) = obj;
    sp[0x10] = 0;
    sp[0x11] = 0;
    sp[0x13] = 0;
    sp[0x14] = 0;
    sp[0x15] = 0;
    *(u32 *)(sp + 0x1C) = 0;
    *(u8 **)(sp + 0x28) = cfg;

    func_00208DE8(*(u8 **)cfg, sp + 0x30, *(s32 *)(ctx + 8));
    func_00129C28(sp + 0x40, sp + 0x30);
    func_00208DE8(*(u8 **)cfg, sp + 0x50, 0x11);
    func_0012D488(cfg, sp + 0x60, ctx + 0x70, *(u8 **)cfg);
    frames = *(s16 *)(*(u8 **)(cfg + 0x20) + 0x34);
    mode = func_0014EAD8(view);
    dist = EftVolleyAim_GetFighterDistSq();
    if (mode == 7) {
        ampX = D_003845C8;
        ampY = ampX;
    }
    if (*(u8 *)(ctx + 0xB18) != 0) {
        ampX = ampX + ampX;
        ampY = ampY + ampY;
    }

    if (**(s32 **)(cfg + 0x20) == 0x153) {
        f = 10.0f;
        mode = 8;
        ampX = ampX * f;
    } else if (*(s32 *)(ctx + 0xB14) == 0) {
        f = D_003845CC;
        ampY = ampY * f;
        ampX = ampX * f;
    } else if (dist < D_003845D0) {
        if (D_003845D4 < dist) {
            f = EftVolleyAim_Lerp(0.5f, angB, (dist - D_003845D4) / D_003845D8);
            ampY = ampY * f;
        } else {
            f = 0.5f;
            ampY = ampY * f;
        }
        ampX = ampX * f;
    }

    if ((u32)mode >= 9) {
        angB = 0.0f;
        angA = angB;
    } else {
        switch (mode) {
        case 0:
            angA = Rand_FloatRange(-ampX - offX, ampX + offX);
            angB = Rand_FloatRange(-ampY - offY, ampY + offY);
            break;
        case 1: {
            f32 r = Rand_FloatRange(-offX, D_003845DC);
            f32 t = (ampX + ampX) / (f32)frames;
            t = t * (f32)*(s32 *)(ctx + 0xB14);
            t = t - ampX;
            angA = t + r;
            angB = Rand_FloatRange(-ampY - offY, ampY + offY);
            break;
        }
        case 2: {
            s32 c = *(s32 *)(ctx + 0xB14);
            f32 r;
            if (c >= 4) {
                f32 g = func_0030D658(0.5f, (f32)(c / 4));
                ampY = ampY * g;
                ampX = ampX * g;
            }
            r = Rand_FloatRange(-offX, D_003845E0);
            c = *(s32 *)(ctx + 0xB14);
            angA = ampX + r;
            if (c % 2 != *(u8 *)(ctx + 0xB19)) {
                angA = -angA;
            }
            angB = Rand_FloatRange(-ampY - offY, ampY + offY);
            break;
        }
        case 3: {
            f32 r2;
            offY = Rand_FloatRange(D_003845E4, D_003845E8);
            offX = -offX;
            angB = Rand_FloatRange(offX, D_003845EC);
            r2 = angB;
            angA = ampX * sinf(offY) + r2;
            angB = Rand_FloatRange(offX, D_003845F0);
            angB = ampY * cosf(offY) + angB;
            break;
        }
        case 4:
        case 5:
        case 6:
            n = *(s32 *)(ctx + 0xB14);
            if (mode == 4) {
                f32 base = D_003845F4;
                s32 half = n / 2;
                parity = n % 2;
                offY = base / (f32)(frames + 2);
                if (parity == *(u8 *)(ctx + 0xB19)) {
                    offY = offY * (f32)(half + 1) + D_003845F8;
                } else {
                    offY = EftMath_WrapAngle(D_003845FC - offY * (f32)(half + 1));
                }
            } else if (mode == 5) {
                s32 half = n / 2;
                f32 base = D_00384600;
                offY = base / (f32)(frames - 1);
                parity = n % 2;
                if (parity == *(u8 *)(ctx + 0xB19)) {
                    offY = offY * (f32)half;
                } else {
                    offY = base - offY * (f32)half;
                }
            } else {
                s32 half = n / 2;
                f32 base = D_00384604;
                offY = base / (f32)(frames - 1);
                parity = n % 2;
                if (parity == *(u8 *)(ctx + 0xB19)) {
                    offY = offY * (f32)half;
                } else {
                    offY = base - offY * (f32)half;
                }
                if (((half / 2) * 2) == half - 1) {
                    ampY = ampY * 0.5f;
                    ampX = ampX * 0.5f;
                }
            }
            angB = -offX;
            angA = Rand_FloatRange(angB, D_00384608);
            angA = ampX * cosf(offY) + angA;
            angB = Rand_FloatRange(angB, D_0038460C);
            angB = ampY * sinf(offY) + angB;
            break;
        case 7: {
            u32 w;
            angA = Rand_FloatRange(-ampX - offX, ampX + offX);
            offX = angA;
            angB = Rand_FloatRange(-ampY - offY, ampY + offY);
            *(u32 *)(sp + 0x64) = 0;
            w = D_003415F0;
            angB = angB + D_00384610;
            *(u32 *)(ctx + 0xB1C) = w;
            break;
        }
        case 8: {
            f32 len;
            *(u32 *)(sp + 0x94) = 0;
            EftVolleyAim_GetToOpponent(*(u8 **)cfg, sp + 0x90);
            func_001EEDB8((f32 *)(sp + 0x90), (f32 *)(sp + 0x90), 800.0f);
            func_00208860(*(u8 **)cfg, sp + 0xA0);
            *(u32 *)(sp + 0xA4) = 0;
            func_00129B28(sp + 0x90, sp + 0x90, sp + 0xA0);
            len = func_00129E30(sp + 0x90);
            f = func_00272FA8();
            if (len < f * f) {
                *(u32 *)(ctx + 0xB1C) = D_003415F4;
                angB = Rand_FloatRange(-ampY - offY, ampY + offY) + D_00384614;
            } else {
                *(u32 *)(ctx + 0xB1C) = D_003415F8;
                angB = Rand_FloatRange(-ampY - offY, ampY + offY) + D_00384618;
            }
            angA = Rand_FloatRange(-ampX - offX, ampX + offX);
            *(u32 *)(sp + 0x64) = 0;
            break;
        }
        }
    }

    if ((u32)(mode - 7) >= 2) {
        f32 d = func_00217330(func_00211288(*(u8 **)cfg));
        if (d < 30.0f) {
            if (angB < 0.0f) {
                angB = angB * D_0038461C;
            }
        }
    }

    Vec3_RotateY(sp + 0x80, sp + 0x60, D_00384620);
    Vec3_RotateY(sp + 0x60, sp + 0x60, angA);
    Vec3_RotateAxis(sp + 0x60, sp + 0x60, sp + 0x80, angB);
    *(f32 *)(sp + 0x70) = *(f32 *)(*(u8 **)(cfg + 0x24) + 8);
    *(f32 *)(sp + 0x74) = *(f32 *)(*(u8 **)(cfg + 0x24) + 8);
    *(f32 *)(sp + 0x78) = *(f32 *)(*(u8 **)(cfg + 0x20) + 0x18);
    *(f32 *)(sp + 0x7C) = *(f32 *)(*(u8 **)(cfg + 0x20) + 0x18);
    if (**(s32 **)(cfg + 0x20) == 0x153) {
        func_00129C28(ctx + 0x30, sp + 0x60);
    }
    n = *(s32 *)(ctx + 0xB14);
    *(s32 *)(ctx + 0xAB0 + n * 4) = func_00182A80(sp, sp + 0x60);
    n = *(s32 *)(ctx + 0xB14);
    if (*(s32 *)(ctx + 0xAB0 + n * 4) != 0) {
        *(s32 *)(ctx + 0xB10) = *(s32 *)(ctx + 0xB10) + 1;
    }
    *(s32 *)(ctx + 0xB14) = n + 1;
}
