#include "common.h"

extern s32 func_00126058(u8 *obj, s32 a1, s32 a2);
extern void func_00208DE8(s32 arg0, void *out, s32 arg2);
extern s32 func_00121698(u8 *obj);
extern u8 *func_00126040(u8 *obj);
extern void func_003126C8(void *dst, void *src);
extern f32 BtlCharApi_GetHeight(s32 arg0);
extern f32 func_00207F38(s32 arg0);
extern f32 func_00273000(void);
extern void sceVu0InterVector(void *out, void *a, void *b, f32 t);
extern void func_00312650(void *dst, void *a, void *b);
extern f32 sceVu0InnerProduct(void *a, void *b);
extern void sceVu0Normalize(void *out, void *in);
extern f32 Mathf_Asin(f32 x);
extern f32 func_00121678(u8 *obj);
extern f32 func_00121680(u8 *obj);
extern s32 func_001216A0(u8 *obj);
extern f32 func_00121688(u8 *obj);
extern void BtlOpp_GetDelta(u8 *opp, void *out);
extern void func_00312680(void *dst, void *src, f32 t);
extern void func_00312638(void *dst, void *a, void *b);
extern f32 D_003840E8, D_003840EC, D_003840F0, D_003840F4, D_003840F8, D_003840FC, D_00384100;

#define FY(off) (*(f32 *)(sp + (off)))

/* Camera/frame limit solver: derives lower/upper angle limits (f21/f23) from the character's frame
   rectangles and updates the min/max values stored in the state block at obj+0xFE0. */
void func_00121B68(u8 *obj) {
    u8 sp[0xf0];   /* tamano de locales del original (antes 0xd0) */
    u8 *tab = obj + 0xBE0;
    u8 *st = obj + 0xFE0;
    s32 idx, hasRange;
    s32 idxA, idxB;
    f32 curMin, curMax, limLo = 0.0f, limHi = 0.0f;
    f32 lo[2], hi[2];
    s32 i, k;
    f32 r1, r2, ang;

    *(u32 *)(st + 0x28) = *(u32 *)(st + 0x28) & 0xFFFFFFFC;
    if (func_00126058(obj, 0, 2)) {
        func_00208DE8(*(s32 *)obj, sp + 0x20, 3);
    } else if (func_00121698(obj)) {
        func_00208DE8(*(s32 *)obj, sp + 0x20, 3);
    } else {
        u8 *p = func_00126040(obj);

        func_003126C8(sp + 0x20, *(u8 **)(p + 0x1530) + 0xE60);
    }
    idx = *(s32 *)(st + 8);
    hasRange = st[4];
    idxA = idx;
    idxB = idx;
    curMin = D_003840E8;
    curMax = D_003840EC;
    if (hasRange) {
        u8 *rec;
        f32 h;

        curMax = (f32)*(s16 *)(tab + idx * 2 + 0x260);
        h = BtlCharApi_GetHeight(*(s32 *)obj);
        curMin = (f32)*(s16 *)(tab + idx * 2 + 0x220);
        curMax = curMax + h;
        h = func_00207F38(*(s32 *)obj);
        if (curMin < FY(0x24) - h) {
            limLo = D_003840F0;
        }
        if (FY(0x24) < curMax) {
            limHi = D_003840F4;
        }
        rec = tab + idx * 16 + 0x20;
        func_003126C8(sp + 0x10, rec);
        FY(0x14) = curMin;
        FY(0x1C) = 1.0f;
        func_003126C8(sp + 0, rec);
        FY(0xC) = 1.0f;
        FY(4) = curMax;
    }
    i = idx;
    if (i > 0) {
        u8 *p16 = tab + i * 16;
        u8 *hp = tab + i * 2 + 0x25E;

        do {
            s32 found = 0;

            for (k = 0; k < 2; k++) {
                hi[k] = D_003840F8;
                lo[k] = D_003840FC;
            }
            if (i < *(s32 *)(st + 8) || *(f32 *)(st + 0xC) < 0.5f) {
                lo[0] = (f32)*(s16 *)(hp + 0x102);
            }
            hi[0] = func_00273000();
            hi[1] = (f32)*(s16 *)hp;
            lo[1] = (f32)*(s16 *)(hp - 0x40);
            {
                f32 sum = hi[1] + BtlCharApi_GetHeight(*(s32 *)obj);

                hi[1] = sum;
                if (lo[1] < sum) {
                    hi[1] = lo[1];
                }
            }
            for (k = 0; k < 2; k++) {
                f32 newMin = curMin, newMax = curMax;
                s32 newA = idxA, newB = idxB;
                s32 fMin = 0, fMax = 0;
                f32 h;

                if (lo[k] < curMin) {
                    newMin = lo[k];
                    newA = i;
                    fMin = 1;
                }
                if (newMax < hi[k]) {
                    newMax = hi[k];
                    newB = i;
                    fMax = 1;
                }
                if (newMin < newMax) {
                    found = 1;
                    break;
                }
                h = func_00207F38(*(s32 *)obj);
                if (lo[k] < FY(0x24) - h) {
                    if (k == 0) {
                        sceVu0InterVector(sp + 0x30, p16 + 0x10, p16 + 0x20, 0.5f);
                        FY(0x34) = lo[k];
                        func_003126C8(sp + 0x50, p16 + 0x20);
                        FY(0x54) = lo[k];
                    } else if (k == 1) {
                        func_003126C8(sp + 0x30, p16 + 0x10);
                        FY(0x34) = lo[1];
                        sceVu0InterVector(sp + 0x50, p16 + 0x10, p16 + 0x20, 0.5f);
                        FY(0x54) = lo[k];
                    }
                    func_00312650(sp + 0x40, sp + 0x50, sp + 0x20);
                    func_00312650(sp + 0x60, sp + 0x30, sp + 0x50);
                    if (sceVu0InnerProduct(sp + 0x40, sp + 0x60) < 0.0f) {
                        ang = -1.0f;
                    } else {
                        sceVu0Normalize(sp + 0x40, sp + 0x40);
                        ang = FY(0x44);
                    }
                    if (ang < limLo) {
                        limLo = ang;
                    }
                }
                if (FY(0x24) < hi[k]) {
                    if (k == 0) {
                        sceVu0InterVector(sp + 0x30, p16 + 0x10, p16 + 0x20, 0.5f);
                        FY(0x34) = hi[0];
                        func_003126C8(sp + 0x50, p16 + 0x20);
                        FY(0x54) = hi[0];
                    } else if (k == 1) {
                        func_003126C8(sp + 0x30, p16 + 0x10);
                        FY(0x34) = hi[1];
                        sceVu0InterVector(sp + 0x50, p16 + 0x10, p16 + 0x20, 0.5f);
                        FY(0x54) = hi[k];
                    }
                    func_00312650(sp + 0x40, sp + 0x50, sp + 0x20);
                    func_00312650(sp + 0x60, sp + 0x30, sp + 0x50);
                    if (sceVu0InnerProduct(sp + 0x40, sp + 0x60) < 0.0f) {
                        if (limHi < 1.0f) {
                            limHi = 1.0f;
                        }
                    } else {
                        sceVu0Normalize(sp + 0x40, sp + 0x40);
                        if (FY(0x44) < limLo) {
                            limLo = FY(0x44);
                        }
                    }
                    func_00312650(sp + 0x40, sp + 0x30, sp + 0x20);
                    sceVu0Normalize(sp + 0x40, sp + 0x40);
                    if (limHi < FY(0x44)) {
                        limHi = FY(0x44);
                    }
                }
                curMin = newMin;
                curMax = newMax;
                idxA = newA;
                idxB = newB;
                if (fMin) {
                    if (k == 0) {
                        sceVu0InterVector(sp + 0x10, p16 + 0x10, p16 + 0x20, 0.5f);
                        FY(0x14) = curMin;
                    } else if (k == 1) {
                        func_003126C8(sp + 0x10, p16 + 0x10);
                        FY(0x14) = curMin;
                    }
                    FY(0x1C) = 1.0f;
                }
                if (fMax) {
                    if (k == 0) {
                        sceVu0InterVector(sp + 0, p16 + 0x10, p16 + 0x20, 0.5f);
                        FY(4) = curMax;
                    } else if (k == 1) {
                        func_003126C8(sp + 0, p16 + 0x10);
                        FY(4) = curMax;
                    }
                    FY(0xC) = 1.0f;
                }
            }
            if (found) {
                break;
            }
            i--;
            p16 -= 16;
            hp -= 2;
        } while (i > 0);
    }
    limLo = Mathf_Asin(-limLo);
    limHi = Mathf_Asin(-limHi);
    r1 = func_00121678(obj);
    r2 = func_00121680(obj);
    if (r1 < limLo) {
        u32 flags = *(u32 *)(st + 0x28);

        *(f32 *)(st + 0x40) = curMin;
        *(u32 *)(st + 0x28) = flags | 1;
        if (func_00126058(obj, 0, 1)) {
            if (func_001216A0(obj)) {
                f32 t, dd;

                func_003126C8(sp + 0x30, sp + 0x20);
                FY(0x34) = curMin;
                BtlOpp_GetDelta(func_00126040(obj), sp + 0x40);
                *(s32 *)(sp + 0x4C) = 0;
                func_003126C8(sp + 0xB0, sp + 0x40);
                *(s32 *)(sp + 0xB4) = 0;
                sceVu0Normalize(sp + 0xB0, sp + 0xB0);
                FY(0xBC) = -sceVu0InnerProduct(sp + 0xB0, sp + 0x10);
                dd = sceVu0InnerProduct(sp + 0xB0, sp + 0x40);
                if (D_00384100 < __builtin_fabsf(dd)) {
                    t = -(sceVu0InnerProduct(sp + 0xB0, sp + 0x30) + FY(0xBC)) / dd;
                    if (0.0f < t && t < 1.0f) {
                        func_00312680(sp + 0xC0, sp + 0x40, t);
                        func_00312638(sp + 0xC0, sp + 0xC0, sp + 0x30);
                        if (FY(0x14) < FY(0xC4)) {
                            *(f32 *)(st + 0x40) = *(f32 *)(st + 0x40) - (FY(0xC4) - FY(0x14));
                        }
                    }
                }
            }
        }
        *(f32 *)(st + 0x40) = *(f32 *)(st + 0x40) + func_00121688(obj);
        if (*(f32 *)(st + 0x40) < curMax) {
            *(f32 *)(st + 0x40) = curMax;
        }
    } else if (limHi < r2) {
        if (!func_00126058(obj, 0, 4)) {
            *(u32 *)(st + 0x28) = *(u32 *)(st + 0x28) | 2;
            *(f32 *)(st + 0x44) = curMax;
        }
    }
}
