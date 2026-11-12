#include "common.h"

extern f32 D_0038411C;
extern f32 D_00384120;

void *func_001272E0();
void *func_00126040();
void *BtlChar_GetPos();
void func_00312650();
f32 sceVu0InnerProduct();
f32 func_0029DFD0();
f32 func_002086B0();
f32 EftHit_GetRadiusA();

/* 0x001247B0: per-frame nearest-hit scan over the 0x180-byte entries of the list returned by func_001272E0. */
void func_001247B0(void *arg0, s32 arg1) {
    u8 vecA[16];
    u8 vecB[16];
    u8 *st;
    u8 *list;
    u8 *ent;
    u8 *p;
    s32 i;
    s32 v1;
    s16 t;
    f32 lenA;
    f32 lenB;
    f32 d;
    f32 q;

    st = (u8 *)arg0 + 0x11B4;
    list = (u8 *)func_001272E0(arg0, arg1);
    *(s32 *)(st + 4) = 0;
    *(f32 *)(st + 0) = D_0038411C;
    *(s32 *)(st + 8) = 0;
    *(s32 *)(st + 0xC) = 0;
    *(s32 *)(st + 0x10) = 0;
    *(u8 *)(st + 0x14) = 0;

    ent = list;
    for (i = 0; i < *(s32 *)(list + 0x6000); i++, ent += 0x180) {
        if (*(s32 *)(ent + 0x54) == 1) {
            continue;
        }
        if (*(s32 *)ent == *(s32 *)arg0) {
            continue;
        }
        func_00312650(vecA, ent + 0x20, ent + 0x30);
        p = (u8 *)BtlChar_GetPos(func_00126040(arg0));
        func_00312650(vecB, p, ent + 0x20);
        if (sceVu0InnerProduct(vecB, vecA) < 0.0f) {
            continue;
        }
        lenB = func_0029DFD0(vecB);
        lenA = func_0029DFD0(vecA);
        if (lenA < D_00384120) {
            continue;
        }
        d = lenB - func_002086B0(*(s32 *)arg0);
        d = d - EftHit_GetRadiusA(ent);
        if (d < 0.0f) {
            d = 0.0f;
        }
        q = d / lenA;
        if (q < *(f32 *)st) {
            *(f32 *)st = q;
        }
        if (*(s32 *)(ent + 0xC) != 0) {
            p = *(u8 **)(ent + 0x64);
            if (p != NULL) {
                v1 = *(s32 *)(p + 4);
                if (v1 >= 0) {
                    if (v1 < 2) {
                        *(s32 *)(st + 0x10) += 1;
                    } else if (v1 < 5) {
                        *(s32 *)(st + 0xC) += 1;
                    }
                }
            }
        } else {
            p = *(u8 **)(ent + 0x68);
            if (p != NULL) {
                t = *(s16 *)(p + 0x18);
                if (t == 0 || t == 4 || t == 8) {
                    *(s32 *)(st + 4) += 1;
                } else {
                    *(s32 *)(st + 8) += 1;
                }
            }
        }
        *(u8 *)(st + 0x14) = 1;
    }
}
