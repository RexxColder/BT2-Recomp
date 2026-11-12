#include "common.h"

extern u8 *D_00387E9C;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern f32 D_00385614;

s32 EftBurst_IsBusy(void);
void func_00128900(void *arg0, void *arg1);
f32 EftMath_WrapAngle(f32 farg0);
void Mtx_StoreIdentity(void *arg0);
void Mtx_RotateZ(void *arg0, void *arg1, f32 arg2);
void Mtx_Mul(void *arg0, void *arg1, void *arg2);
s32 func_00129C28(void *arg0, void *arg1);
void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00129C50(void *a0, void *a1, void *a2);
void func_001DA1B0(void *arg0, void *arg1, void *arg2);
s32 EftWater_IsOnScreen(void *arg0, s32 arg1);

/* 0x001DAA60: builds one GIF packet for a water quad (4 corners projected through a 3x4 matrix), links it into the
   table at D_00387AE0 and returns the old table entry. Early exits: IsBusy result, 0 (off screen), 0x80 (no packet). */
s32 func_001DAA60(u8 *a0, u8 *a1, u8 a2, u8 a3, u8 t0, u8 t1, u8 *t2, u8 t3,
                  f32 fA, f32 fB, f32 fC, f32 fD, f32 fE, f32 fF) {
    u8 sp[0x210];
    u8 *s6 = sp + 0x50;
    u8 *rot = sp + 0x110;
    u8 *corner;
    u8 *outv;
    u8 *wp;
    u8 *pkt;
    u8 *ent;
    u8 *ret;
    f32 h;
    s32 busy;
    s32 sum;
    s32 x;
    s32 k;
    s32 j;

    *(u64 *)(sp + 8) = *(u64 *)(a0 + 8);
    *(u64 *)(sp + 0) = *(u64 *)(a0 + 0);
    for (j = 0; j < 8; j++) {
        *(u64 *)(sp + 0x10 + 8 * j) = *(u64 *)(a1 + 8 * j);
    }

    busy = EftBurst_IsBusy();
    if (busy != 0) {
        return busy;
    }
    func_00128900(s6, D_00387E9C + 0x1450);
    if (fB != 0.0f) {
        Mtx_StoreIdentity(rot);
        Mtx_RotateZ(rot, rot, EftMath_WrapAngle((fB / 180.0f) * D_00385614));
        Mtx_Mul(s6, s6, rot);
    }

    h = fA * 0.5f;
    func_00129C28(sp + 0x80, sp);
    Vec4_Set(sp + 0x90, -h, -h, 0.0f, 1.0f);
    Vec4_Set(sp + 0xA0, h, -h, 0.0f, 1.0f);
    Vec4_Set(sp + 0xB0, -h, h, 0.0f, 1.0f);
    Vec4_Set(sp + 0xC0, h, h, 0.0f, 1.0f);

    for (k = 0; k < 4; k++) {
        corner = sp + 0x90 + 16 * k;
        outv = sp + 0xD0 + 16 * k;
        wp = sp + 0x9C + 16 * k;
        func_00129C50(corner, s6, corner);
        *(f32 *)wp = 1.0f;
        func_001DA1B0(outv, sp + 0x10, corner);
        if (EftWater_IsOnScreen(outv, 4) == 0) {
            return 0;
        }
    }

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x80;
    if (pkt == 0) {
        return 0x80;
    }

    *(u64 *)(pkt + 0x00) = 0xA0000007ull;
    *(u64 *)(pkt + 0x10) = 0xC400000000008001ull;
    *(u64 *)(pkt + 0x18) = 0xF42424242160ull;
    *(u64 *)(pkt + 0x20) = 0x54ull;
    pkt[0x30] = a2;
    pkt[0x31] = a3;
    pkt[0x32] = t0;
    pkt[0x33] = t1;
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(f32 *)(pkt + 0x4C) = fD;
    *(f32 *)(pkt + 0x58) = fC;
    *(f32 *)(pkt + 0x68) = fE;
    *(f32 *)(pkt + 0x6C) = fF;
    *(f32 *)(pkt + 0x38) = fC;
    *(f32 *)(pkt + 0x3C) = fD;
    *(f32 *)(pkt + 0x48) = fE;
    *(f32 *)(pkt + 0x5C) = fF;

    *(u16 *)(pkt + 0x40) = *(u16 *)(sp + 0xD0);
    *(u16 *)(pkt + 0x42) = *(u16 *)(sp + 0xD4);
    *(u64 *)(pkt + 0x40) = (*(u64 *)(pkt + 0x40) & 0xFF000000FFFFFFFFull)
                         | ((u64)(*(u32 *)(sp + 0xD8) & 0xFFFFFF) << 32);
    pkt[0x47] = 0xFF;

    *(u16 *)(pkt + 0x50) = *(u16 *)(sp + 0xE0);
    *(u16 *)(pkt + 0x52) = *(u16 *)(sp + 0xE4);
    *(u64 *)(pkt + 0x50) = (*(u64 *)(pkt + 0x50) & 0xFF000000FFFFFFFFull)
                         | ((u64)(*(u32 *)(sp + 0xE8) & 0xFFFFFF) << 32);
    pkt[0x57] = 0xFF;

    *(u16 *)(pkt + 0x60) = *(u16 *)(sp + 0xF0);
    *(u16 *)(pkt + 0x62) = *(u16 *)(sp + 0xF4);
    *(u64 *)(pkt + 0x60) = (*(u64 *)(pkt + 0x60) & 0xFF000000FFFFFFFFull)
                         | ((u64)(*(u32 *)(sp + 0xF8) & 0xFFFFFF) << 32);
    pkt[0x67] = 0xFF;

    *(u16 *)(pkt + 0x70) = *(u16 *)(sp + 0x100);
    *(u16 *)(pkt + 0x72) = *(u16 *)(sp + 0x104);
    *(u64 *)(pkt + 0x70) = (*(u64 *)(pkt + 0x70) & 0xFF000000FFFFFFFFull)
                         | ((u64)(*(u32 *)(sp + 0x108) & 0xFFFFFF) << 32);
    pkt[0x77] = 0xFF;

    *(u64 *)(pkt + 0x28) = *(u64 *)t2;
    sum = (s32)((u32)*(u32 *)(sp + 0xD8) + (u32)*(u32 *)(sp + 0x108)
              + (u32)*(u32 *)(sp + 0xF8) + (u32)*(u32 *)(sp + 0xE8));
    x = sum >> 10;
    if (x < 0) {
        ent = D_00387AE0 + (t3 << 3);
    } else if (x < 0x1000) {
        ent = D_00387AE0 + ((2 * x + t3) << 3);
    } else {
        ent = D_00387AE0 + (t3 << 3) + 0xFFF0;
    }
    ret = *(u8 **)(ent + 4);
    *(u8 **)(ret + 4) = pkt;
    *(u8 **)(ent + 4) = pkt;
    return (s32)ret;
}
