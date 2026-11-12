#include "common.h"

/* cvt.w.s truncates toward zero (saturating): plain cast */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(x) ((s32)(x))

extern s32 BtlScene_IsEffectStopped(s32 arg0, u8 arg1);
extern void BtlTask_SetDead(void *arg0);
extern void Mtx_StoreIdentity(void *arg0);
extern void Vec3_Add(void *arg0, void *arg1, void *arg2);
extern void func_00128C58(void *arg0, void *arg1, f32 f12);
extern void func_00129BD0(void *arg0, void *arg1, f32 f12);
extern void func_0018F780(void *arg0, void *arg1, void *arg2, void *arg3, f32 f12);
extern void func_0018FBB0(void *arg0);
extern void func_0018FC88(void *arg0, void *arg1, void *arg2);
extern void func_00190330(void *arg0, f32 f12, f32 f13);
extern void *memset(void *, s32, u32);
extern f32 D_00384C1C;

void func_0018E9B0(void *arg0) {
    f32 sp[16];
    f32 sp40[4];
    u8 *s2;
    u8 *s1;
    u8 *pt;
    u16 fl;
    s32 i;
    f32 r;
    f32 r1;
    f32 r12;
    f32 f1v;
    f32 f22;
    f32 f24;
    f32 f25;
    f32 f20;
    u8 *s0;

    s2 = *(u8 **)((u8 *)arg0 + 0x38);
    s1 = *(u8 **)(s2 + 4);
    memset(sp, 0, 0x40);
    memset(sp40, 0, 0x10);
    if (BtlScene_IsEffectStopped(*(s32 *)(s2 + 0x54), *(u8 *)(s2 + 0x58)) == 0) {
        Mtx_StoreIdentity(sp);
        func_00128C58(sp, sp, *(f32 *)(s2 + 0x30));
        f22 = 1.0f - *(f32 *)(s1 + 0x3C);
        f24 = 1.0f - *(f32 *)(s1 + 0x34);
        f25 = 1.0f - *(f32 *)(s1 + 0x38);
        if (0.0f < *(f32 *)(s2 + 0x3C)) {
            *(f32 *)(s2 + 0x3C) = *(f32 *)(s2 + 0x3C) - 1.0f;
            return;
        }

        if (*(u16 *)(s2 + 0x44) & 4) {
            if (*(f32 *)(s2 + 0x40) > 0.0f) {
                if (CVT_W_S(*(f32 *)(s2 + 0x38)) % *(s32 *)(s1 + 0xA4) == 0) {
                    i = 0;
                    if (*(s32 *)(s1 + 0xA0) > 0) {
                        do {
                            i += 1;
                            func_0018FBB0(s2);
                        } while (i < *(s32 *)(s1 + 0xA0));
                    }
                }
                *(f32 *)(s2 + 0x40) = *(f32 *)(s2 + 0x40) - 1.0f;
            }
        } else if (CVT_W_S(*(f32 *)(s2 + 0x38)) % *(s32 *)(s1 + 0xA4) == 0) {
            i = 0;
            if (*(s32 *)(s1 + 0xA0) > 0) {
                do {
                    i += 1;
                    func_0018FBB0(s2);
                } while (i < *(s32 *)(s1 + 0xA0));
            }
        }

        pt = *(u8 **)(s2 + 0x5C);
        if (pt != NULL) {
            do {
                r1 = *(f32 *)(pt + 0xF0);
                r = 0.0f;
                if (!(r1 <= 0.0f)) {
                    r = r1 / *(f32 *)(pt + 0xC4);
                }
                if (f22 < r) {
                    *(u16 *)(pt + 0xFC) = (u16)(*(u16 *)(pt + 0xFC) | 1);
                }
                if ((r <= f22) && (0.0f < r)) {
                    fl = *(u16 *)(pt + 0xFC);
                    if (fl & 1) {
                        fl = (u16)(fl ^ 1);
                        *(u16 *)(pt + 0xFC) = fl;
                    }
                    fl = (u16)(fl | 8);
                    *(u16 *)(pt + 0xFC) = fl;
                }
                if (!(f24 < r)) {
                    fl = *(u16 *)(pt + 0xFC);
                    if (fl & 0x40) {
                        fl = (u16)(fl ^ 0x40);
                        *(u16 *)(pt + 0xFC) = fl;
                    }
                } else {
                    fl = (u16)(*(u16 *)(pt + 0xFC) | 0x40);
                    *(u16 *)(pt + 0xFC) = fl;
                }
                if (r < f25) {
                    fl = (u16)(*(u16 *)(pt + 0xFC) | 0x80);
                    *(u16 *)(pt + 0xFC) = fl;
                }
                fl = *(u16 *)(pt + 0xFC);
                if (r <= 0.0f) {
                    fl = 0x10;
                    *(u16 *)(pt + 0xFC) = fl;
                }
                if (fl & 1) {
                    *(f32 *)(pt + 0xCC) = *(f32 *)(pt + 0xCC) + *(f32 *)(pt + 0xD0);
                    *(f32 *)(pt + 0xE4) = *(f32 *)(pt + 0xE4) + *(f32 *)(pt + 0xE8);
                }
                if (fl & 8) {
                    *(f32 *)(pt + 0xCC) = *(f32 *)(pt + 0xCC) + *(f32 *)(pt + 0xD4);
                    *(f32 *)(pt + 0xE4) = *(f32 *)(pt + 0xE4) + *(f32 *)(pt + 0xEC);
                }
                r12 = *(f32 *)(pt + 0xCC);
                if (r12 < 0.0f) {
                    *(f32 *)(pt + 0xCC) = 1.0f;
                    r12 = 1.0f;
                }
                f1v = *(f32 *)(pt + 0xE4);
                if (f1v < 0.0f) {
                    *(f32 *)(pt + 0xE4) = 1.0f;
                    f1v = 1.0f;
                }
                *(f32 *)(pt + 0xDC) = *(f32 *)(pt + 0xE0) * f1v;
                *(f32 *)(pt + 0x58) = *(f32 *)(pt + 0x58) + *(f32 *)(pt + 0xC0);
                f20 = *(f32 *)(pt + 0xC8) * r12;
                Vec3_Add(pt + 0x60, pt + 0x60, pt + 0x70);
                if (!(*(u16 *)(pt + 0xFC) & 0x100)) {
                    Vec3_Add(pt + 0x30, pt + 0x30, pt + 0x40);
                }
                s0 = pt + 0x10;
                Vec3_Add(s0, s0, pt + 0x20);
                func_00129BD0(sp40, s0, f20);
                Vec3_Add(pt, pt, sp40);
                func_00129BD0(sp40, s2 + 0x20, -1.0f);
                func_0018F780(pt, sp, s2 + 0x10, sp40, *(f32 *)(s2 + 0x30));
                fl = *(u16 *)(pt + 0xFC);
                if (fl & 0x40) {
                    *(f32 *)(pt + 0x3C) = *(f32 *)(pt + 0x3C) + *(f32 *)(pt + 0xF4);
                }
                if (fl & 0x80) {
                    *(f32 *)(pt + 0x3C) = *(f32 *)(pt + 0x3C) - *(f32 *)(pt + 0xF8);
                }
                func_00190330(pt + 0x30, 0.0f, 255.0f);
                *(f32 *)(pt + 0xF0) = *(f32 *)(pt + 0xF0) - D_00384C1C;
                if (*(u16 *)(pt + 0xFC) & 0x10) {
                    *(u16 *)(pt + 0xFC) = 0;
                    func_0018FC88(s2 + 0x5C, s2 + 0x60, pt);
                }
                pt = *(u8 **)(pt + 0x100);
            } while (pt != NULL);
        }

        if (*(u16 *)(s2 + 0x44) & 0x20) {
            pt = *(u8 **)(s2 + 0x5C);
            if (pt != NULL) {
                do {
                    *(u16 *)(pt + 0xFC) = 0;
                    func_0018FC88(s2 + 0x5C, s2 + 0x60, pt);
                    pt = *(u8 **)(pt + 0x100);
                } while (pt != NULL);
            }
        }

        f1v = *(f32 *)(s2 + 0x34);
        if (0.0f < f1v) {
            r = f1v - 1.0f;
            *(f32 *)(s2 + 0x34) = r;
            if (r <= 0.0f) {
                *(f32 *)(s2 + 0x34) = 0.0f;
                *(u16 *)(s2 + 0x44) = (u16)(*(u16 *)(s2 + 0x44) | 4);
            }
        }
        *(f32 *)(s2 + 0x38) = *(f32 *)(s2 + 0x38) + 1.0f;
        if ((*(u8 **)(s2 + 0x5C) == NULL) && (*(u16 *)(s2 + 0x44) & 4)) {
            *(u16 *)(s2 + 0x44) = 0;
            BtlTask_SetDead(arg0);
        }
    }
}
