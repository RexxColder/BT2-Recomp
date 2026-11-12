#include "common.h"

extern u8 *D_00387E9C;
extern f32 D_00385618;
extern f32 D_0038561C;
extern f32 D_00385620;
extern f32 D_00385624;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

s32 EftBurst_IsBusy(void);
void func_00128900(void *arg0, void *arg1);
void Mtx_StoreIdentity(u8 *arg0);
f32 EftMath_WrapAngle(f32 farg0);
void Mtx_RotateZ(f32 farg0, void *arg0, void *arg1);
void Mtx_Mul(u8 *arg0, u8 *arg1, u8 *arg2);
void func_001DA1B0(void *arg0, void *arg1, void *arg2);
s32 EftWater_IsOnScreen(void *arg0, s32 arg1);
void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00129C28(u8 *arg0, u8 *arg1);
void func_00129C50(u8 *arg0, u8 *arg1, u8 *arg2);

/* 0x001DB4B8: draws a rotated square sprite (size = f12, roll angle in degrees = f13) at the point pos (16 bytes).
   cam (64 bytes, copied) is the projection used by func_001DA1B0; the four corners are rejected with
   EftWater_IsOnScreen, otherwise a GS sprite packet (from the bump pointer D_00387AD8) with colors (r,g,b,a) is linked
   into the ordering table at index ot, depth from the summed projected z. tagp = pointer to the 8-byte GIF tag. */
s32 func_001DB4B8(u8 *pos, u8 *cam, u32 cr, u32 cg, u32 cb, u32 ca, s64 *tagp, u32 ot, f32 size, f32 angle) {
    u8 sp[0x160];   /* tamano de locales del original (antes 0x150) */
    u8 *mtx = sp + 0x50;
    u8 *rot = sp + 0x110;
    u8 *pkt;
    u8 *link;
    u8 *prev;
    u8 *p;
    u8 *q;
    f32 a;
    f32 hx;
    f32 vy0;
    f32 vy1;
    f32 w;
    s32 i;
    s32 depth;
    s32 r;
    u32 bR = cr & 0xFF;
    u32 bG = cg & 0xFF;
    u32 bB = cb & 0xFF;
    u32 bA = ca & 0xFF;
    u32 otIdx = ot & 0xFF;

    __builtin_memcpy(sp + 0x00, pos, 16);
    __builtin_memcpy(sp + 0x10, cam, 64);
    r = EftBurst_IsBusy();
    if (r != 0) {
        return r;
    }
    func_00128900(mtx, D_00387E9C + 0x1450);
    if (angle != 0.0f) {
        Mtx_StoreIdentity(rot);
        a = EftMath_WrapAngle(angle / 180.0f * D_00385618);
        Mtx_RotateZ(a, rot, rot);
        Mtx_Mul(mtx, mtx, rot);
    }
    func_00129C28(sp + 0x80, sp);
    vy0 = size * D_0038561C;
    hx = size * 0.5f * D_00385620;
    w = size * D_00385624;
    vy0 = 0.0f - vy0;
    vy1 = w;
    Vec4_Set(sp + 0x90, 0.0f - hx, vy0, 0.0f, 1.0f);
    Vec4_Set(sp + 0xA0, hx, vy0, 0.0f, 1.0f);
    Vec4_Set(sp + 0xB0, 0.0f - hx, vy1, 0.0f, 1.0f);
    Vec4_Set(sp + 0xC0, hx, vy1, 0.0f, 1.0f);
    i = 0;
    do {
        p = sp + 0x90 + i * 16;
        q = sp + 0xD0 + i * 16;
        i = i + 1;
        func_00129C50(p, mtx, p);
        func_001DA1B0(q, sp + 0x10, p);
        r = EftWater_IsOnScreen(q, 4);
        if (r == 0) {
            return r;
        }
    } while (i < 4);

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x80;
    if (pkt == 0) {
        return (s32)(pkt + 0x80);
    }
    *(s64 *)(pkt + 0x10) = (s64)0xC400000000008001ULL;
    *(s64 *)(pkt + 0x18) = 0xF42424242160LL;
    *(s64 *)(pkt + 0x20) = 0x54;
    *(s64 *)(pkt + 0x00) = 0xA0000007;
    pkt[0x30] = (u8)bR;
    pkt[0x31] = (u8)bG;
    pkt[0x33] = (u8)bA;
    pkt[0x32] = (u8)bB;
    *(f32 *)(pkt + 0x6C) = 1.0f;
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(u32 *)(pkt + 0x38) = 0;
    *(u32 *)(pkt + 0x3C) = 0;
    *(f32 *)(pkt + 0x48) = 1.0f;
    *(u32 *)(pkt + 0x4C) = 0;
    *(u32 *)(pkt + 0x58) = 0;
    *(f32 *)(pkt + 0x5C) = 1.0f;
    *(f32 *)(pkt + 0x68) = 1.0f;
    *(u16 *)(pkt + 0x40) = *(u16 *)(sp + 0xD0);
    *(u16 *)(pkt + 0x42) = *(u16 *)(sp + 0xD4);
    *(u64 *)(pkt + 0x40) = (*(u64 *)(pkt + 0x40) & 0xFF000000FFFFFFFFULL) | ((u64)(*(u32 *)(sp + 0xD8) & 0xFFFFFF) << 32);
    pkt[0x47] = 0xFF;
    *(u16 *)(pkt + 0x50) = *(u16 *)(sp + 0xE0);
    *(u16 *)(pkt + 0x52) = *(u16 *)(sp + 0xE4);
    *(u64 *)(pkt + 0x50) = (*(u64 *)(pkt + 0x50) & 0xFF000000FFFFFFFFULL) | ((u64)(*(u32 *)(sp + 0xE8) & 0xFFFFFF) << 32);
    pkt[0x57] = 0xFF;
    *(u16 *)(pkt + 0x60) = *(u16 *)(sp + 0xF0);
    *(u16 *)(pkt + 0x62) = *(u16 *)(sp + 0xF4);
    *(u64 *)(pkt + 0x60) = (*(u64 *)(pkt + 0x60) & 0xFF000000FFFFFFFFULL) | ((u64)(*(u32 *)(sp + 0xF8) & 0xFFFFFF) << 32);
    pkt[0x67] = 0xFF;
    *(u16 *)(pkt + 0x70) = *(u16 *)(sp + 0x100);
    *(u16 *)(pkt + 0x72) = *(u16 *)(sp + 0x104);
    *(u64 *)(pkt + 0x70) = (*(u64 *)(pkt + 0x70) & 0xFF000000FFFFFFFFULL) | ((u64)(*(u32 *)(sp + 0x108) & 0xFFFFFF) << 32);
    pkt[0x77] = 0xFF;
    depth = (*(s32 *)(sp + 0xD8) + *(s32 *)(sp + 0x108)) + (*(s32 *)(sp + 0xF8) + *(s32 *)(sp + 0xE8));
    depth = depth >> 10;
    *(s64 *)(pkt + 0x28) = *tagp;
    if (depth < 0) {
        link = D_00387AE0 + (otIdx << 3);
        prev = *(u8 **)(link + 4);
    } else if (depth < 0x1000) {
        link = D_00387AE0 + ((depth * 2 + otIdx) << 3);
        prev = *(u8 **)(link + 4);
    } else {
        link = D_00387AE0 + (otIdx << 3) + 0xFFF0;
        prev = *(u8 **)(link + 4);
    }
    *(u8 **)(prev + 4) = pkt;
    *(u8 **)(link + 4) = pkt;
    return (s32)prev;
}
