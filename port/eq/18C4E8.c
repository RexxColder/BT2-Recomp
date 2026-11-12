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
extern void func_0018D298(void *arg0, void *arg1, void *arg2, void *arg3, f32 f12);
extern void func_0018D680(void *arg0);
extern void func_0018D760(void *arg0, void *arg1, void *arg2);
extern void func_0018DE48(void *arg0, f32 f12, f32 f13);
extern void *memset(void *, s32, u32);
extern f32 D_00384C04;

void func_0018C4E8(void *arg0) {
    f32 sp[16];
    f32 sp40[4];
    u8 *s2;
    u8 *s1;
    u8 *pt;
    s32 fl;
    u16 tfl;
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
    if (BtlScene_IsEffectStopped(*(s32 *)(s2 + 0x50), *(u8 *)(s2 + 0x54)) == 0) {
        Mtx_StoreIdentity(sp);
        func_00128C58(sp, sp, *(f32 *)(s2 + 0x30));
        f22 = 1.0f - *(f32 *)(s1 + 0x3C);
        f24 = 1.0f - *(f32 *)(s1 + 0x34);
        f25 = 1.0f - *(f32 *)(s1 + 0x38);
        if (0.0f < *(f32 *)(s2 + 0x3C)) {
            *(f32 *)(s2 + 0x3C) = *(f32 *)(s2 + 0x3C) - 1.0f;
            return;
        }

        if (*(u16 *)(s2 + 0x56) & 4) {
            if (*(f32 *)(s2 + 0x40) > 0.0f) {
                if (CVT_W_S(*(f32 *)(s2 + 0x38)) % *(s32 *)(s1 + 0xA4) == 0) {
                    i = 0;
                    if (*(s32 *)(s1 + 0xA0) > 0) {
                        do {
                            i += 1;
                            func_0018D680(s2);
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
                    func_0018D680(s2);
                } while (i < *(s32 *)(s1 + 0xA0));
            }
        }

        pt = *(u8 **)(s2 + 0x158);
        if (pt != NULL) {
            do {
                r1 = *(f32 *)(pt + 0xE0);
                r = 0.0f;
                if (!(r1 <= 0.0f)) {
                    r = r1 / *(f32 *)(pt + 0xB4);
                }
                if (f22 < r) {
                    *(s32 *)(pt + 0xEC) = *(s32 *)(pt + 0xEC) | 1;
                }
                if ((r <= f22) && (0.0f < r)) {
                    fl = *(s32 *)(pt + 0xEC);
                    if (fl & 1) {
                        fl = fl ^ 1;
                        *(s32 *)(pt + 0xEC) = fl;
                    }
                    fl = fl | 8;
                    *(s32 *)(pt + 0xEC) = fl;
                }
                if (!(f24 < r)) {
                    fl = *(s32 *)(pt + 0xEC);
                    if (fl & 0x40) {
                        fl = fl ^ 0x40;
                        *(s32 *)(pt + 0xEC) = fl;
                    }
                } else {
                    fl = *(s32 *)(pt + 0xEC) | 0x40;
                    *(s32 *)(pt + 0xEC) = fl;
                }
                if (r < f25) {
                    fl = *(s32 *)(pt + 0xEC) | 0x80;
                    *(s32 *)(pt + 0xEC) = fl;
                }
                fl = *(s32 *)(pt + 0xEC);
                if (r <= 0.0f) {
                    fl = 0x10;
                    *(s32 *)(pt + 0xEC) = fl;
                }
                if (fl & 1) {
                    *(f32 *)(pt + 0xBC) = *(f32 *)(pt + 0xBC) + *(f32 *)(pt + 0xC0);
                    *(f32 *)(pt + 0xD4) = *(f32 *)(pt + 0xD4) + *(f32 *)(pt + 0xD8);
                }
                if (fl & 8) {
                    *(f32 *)(pt + 0xBC) = *(f32 *)(pt + 0xBC) + *(f32 *)(pt + 0xC4);
                    *(f32 *)(pt + 0xD4) = *(f32 *)(pt + 0xD4) + *(f32 *)(pt + 0xDC);
                }
                r12 = *(f32 *)(pt + 0xBC);
                if (r12 < 0.0f) {
                    *(f32 *)(pt + 0xBC) = 1.0f;
                    r12 = 1.0f;
                }
                f1v = *(f32 *)(pt + 0xD4);
                if (f1v < 0.0f) {
                    *(f32 *)(pt + 0xD4) = 1.0f;
                    f1v = 1.0f;
                }
                *(f32 *)(pt + 0xCC) = *(f32 *)(pt + 0xD0) * f1v;
                *(f32 *)(pt + 0x68) = *(f32 *)(pt + 0x68) + *(f32 *)(pt + 0xB0);
                f20 = *(f32 *)(pt + 0xB8) * r12;
                if (!(*(s32 *)(pt + 0xEC) & 0x100)) {
                    Vec3_Add(pt + 0x40, pt + 0x40, pt + 0x50);
                }
                s0 = pt + 0x20;
                Vec3_Add(s0, s0, pt + 0x30);
                func_00129BD0(sp40, s0, f20);
                Vec3_Add(pt, pt, sp40);
                func_00129BD0(sp40, s2 + 0x20, -1.0f);
                tfl = *(u16 *)(s2 + 0x56);
                if (tfl & 0x800) {
                    func_0018D298(pt, sp, pt + 0x10, sp40, *(f32 *)(s2 + 0x30));
                } else {
                    func_0018D298(pt, sp, s2 + 0x10, sp40, *(f32 *)(s2 + 0x30));
                }
                fl = *(s32 *)(pt + 0xEC);
                if (fl & 0x40) {
                    *(f32 *)(pt + 0x4C) = *(f32 *)(pt + 0x4C) + *(f32 *)(pt + 0xE4);
                }
                if (fl & 0x80) {
                    *(f32 *)(pt + 0x4C) = *(f32 *)(pt + 0x4C) - *(f32 *)(pt + 0xE8);
                }
                func_0018DE48(pt + 0x40, 0.0f, 255.0f);
                *(f32 *)(pt + 0xE0) = *(f32 *)(pt + 0xE0) - D_00384C04;
                if (*(s32 *)(pt + 0xEC) & 0x10) {
                    *(s32 *)(pt + 0xEC) = 0;
                    func_0018D760(s2 + 0x158, s2 + 0x15C, pt);
                }
                pt = *(u8 **)(pt + 0xF4);
            } while (pt != NULL);
        }

        if (*(u16 *)(s2 + 0x56) & 0x20) {
            pt = *(u8 **)(s2 + 0x158);
            if (pt != NULL) {
                do {
                    *(s32 *)(pt + 0xEC) = 0;
                    func_0018D760(s2 + 0x158, s2 + 0x15C, pt);
                    pt = *(u8 **)(pt + 0xF4);
                } while (pt != NULL);
            }
        }

        f1v = *(f32 *)(s2 + 0x34);
        if (0.0f < f1v) {
            r = f1v - 1.0f;
            *(f32 *)(s2 + 0x34) = r;
            if (r <= 0.0f) {
                *(f32 *)(s2 + 0x34) = 0.0f;
                *(u16 *)(s2 + 0x56) = (u16)(*(u16 *)(s2 + 0x56) | 4);
            }
        }
        *(f32 *)(s2 + 0x38) = *(f32 *)(s2 + 0x38) + 1.0f;
        if ((*(u8 **)(s2 + 0x158) == NULL) && (*(u16 *)(s2 + 0x56) & 4)) {
            *(u16 *)(s2 + 0x56) = 0;
            BtlTask_SetDead(arg0);
        }
    }
}
