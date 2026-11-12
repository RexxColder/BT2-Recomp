#include "common.h"

#define F32AT(p, off) (*(f32 *)((u8 *)(p) + (off)))

void Mtx_StoreIdentity(s32 arg0);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
f32 func_00129E08(s32 arg0);
void func_00189EE8(s32 arg0, s32 arg1, s32 arg2);
void func_0018A2C8(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4);
extern s32 D_003877B4;

void func_0018BBC0(s32 arg0, s32 arg1) {
    u8 sp[0x50];
    u8 *self;
    u8 *s1;
    u8 *s2;
    u8 *node;
    u8 *mt;
    u8 *a1p;
    s32 v;
    s32 v1;
    s32 a0c;
    f32 ratio;
    f32 t;
    s32 r;

    a1p = (u8 *)arg1;
    *(s64 *)(sp + 0x0) = *(s64 *)(a1p + 0x0);
    *(s64 *)(sp + 0x8) = *(s64 *)(a1p + 0x8);
    memset(sp + 0x10, 0, 0x40);

    self = (u8 *)arg0;
    if (D_003877B4 != 0 && self != NULL && (s1 = *(u8 **)(self + 0x38)) != NULL
        && (*(s32 *)(s1 + 0x1D8) & 2) != 0) {
        s2 = *(u8 **)(s1 + 0x30);
        Mtx_StoreIdentity((s32)(sp + 0x10));
        F32AT(sp, 0xC) = 1.0f;
        v = *(s32 *)(s2 + 0xA4) & 1;
        if ((*(s32 *)(s2 + 0xA4) & 2) != 0) {
            *(s64 *)(s1 + 0x40) = *(s64 *)(sp + 0x0);
            *(s64 *)(s1 + 0x48) = *(s64 *)(sp + 0x8);
            node = *(u8 **)(s1 + 0x1E0);
            if (node != NULL) {
                do {
                    if ((*(s32 *)(s2 + 0xA4) & 8) != 0) {
                        func_0018A2C8((s32)node, (s32)(sp + 0x10), (s32)(s1 + 0x40),
                                      F32AT(s1, 0x88) * F32AT(s1, 0x80),
                                      F32AT(s1, 0x94), F32AT(s1, 0xA0),
                                      F32AT(s2, 0x34), F32AT(s2, 0x38));
                    }
                    node = *(u8 **)(node + 0xC0);
                } while (node != NULL);
            }
            v = *(s32 *)(s2 + 0xA4) & 1;
        }

        if (v != 0) {
            mt = s1 + 0x70;
            *(s64 *)(s1 + 0x60) = *(s64 *)(sp + 0x0);
            *(s64 *)(s1 + 0x68) = *(s64 *)(sp + 0x8);
            Vec3_Sub((s32)mt, (s32)(s1 + 0x60), (s32)(s1 + 0x50));
            F32AT(s1, 0xC4) = func_00129E08((s32)mt);
            Vec3_Normalize((s32)mt, (s32)mt);
            t = F32AT(s1, 0xB4);
            ratio = F32AT(s1, 0xC4) / t;
            if (!(ratio < 1.0f)) {
                node = *(u8 **)(s1 + 0x1E0);
                if (node != NULL) {
                    /* cvt.w.s truncates toward zero (saturating): plain cast */
                    r = (s32)ratio;
                    v1 = r;
                    if (v1 > 0) {
                        a0c = 0;
                        node = *(u8 **)(node + 0xC0);
                        for (;;) {
                            if (node == NULL) {
                                break;
                            }
                            a0c += 1;
                            if (!(a0c < v1)) {
                                break;
                            }
                            node = *(u8 **)(node + 0xC0);
                        }
                    }
                    if (node != NULL) {
                        *(u16 *)(node + 0xBE) = 0;
                        do {
                            func_00189EE8((s32)(s1 + 0x1E0), (s32)(s1 + 0x1E4), (s32)node);
                            node = *(u8 **)(node + 0xC0);
                            if (node != NULL) {
                                *(u16 *)(node + 0xBE) = 0;
                            }
                        } while (node != NULL);
                    }
                }
            }
        }
    }
}
