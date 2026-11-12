#include "common.h"

extern u8 *gEftDust;
extern f32 D_003844F8;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

void func_003126C8(void *arg0, s32 arg1);
void func_001405D0(s32 *arg0, f32 *arg1, f32 *arg2);
s32 func_001420F0(void);
s32 EftShotFx_IsOnScreen(s32 arg0, s32 arg1);
f32 EftMath_WrapAngle(f32 farg0);
void sceVu0CopyMatrix(s32 arg0, s32 arg1);
void sceVu0UnitMatrix(void *arg0);
void sceVu0RotMatrixZ(f32 *arg0, f32 *arg1, f32 arg2);
void sceVu0MulMatrix(f32 *arg0, f32 *arg1, f32 *arg2);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);

#define P(x) ((s32)(u32)(x))

/* links a GIF packet into the ordering table: bucket by depth (clamped), slot = (depth * 2 + slot) * 8 */
static void ot_link(u8 *pkt, s32 depth, s32 slot) {
    u8 *link;
    u8 *prev;

    if (depth < 0) {
        link = D_00387AE0 + slot * 8;
        prev = *(u8 **)(link + 4);
    } else if (depth < 0x1000) {
        link = D_00387AE0 + (depth * 2 + slot) * 8;
        prev = *(u8 **)(link + 4);
    } else {
        link = D_00387AE0 + slot * 8 + 0xFFF0;
        prev = *(u8 **)(link + 4);
    }
    *(u8 **)(prev + 4) = pkt;
    *(u8 **)(link + 4) = pkt;
}

static void corner_pack(u8 *pkt, s32 *pt) {
    u64 v;

    *(u16 *)(pkt + 0) = (u16)pt[0];
    *(u16 *)(pkt + 2) = (u16)pt[1];
    v = *(u64 *)pkt;
    *(u64 *)pkt = (v & 0xFF000000FFFFFFFFULL) | ((u64)((u32)pt[2] & 0xFFFFFF) << 32);
    pkt[7] = 0xFF;
}

void func_001407D0(s32 arg0, f32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u64 *arg7,
                   f32 farg0, f32 farg1, s32 stk0) {
    f32 m[16];
    f32 rot[16];
    f32 quad[16];
    s32 out[16];
    f32 half = farg0 * 0.5f;
    s32 i, key, slot = (u8)stk0;
    u8 r = (u8)arg2;
    u8 g = (u8)arg3;
    u8 b = (u8)arg4;
    u8 a = (u8)arg5;
    s32 extra = (u8)arg6;
    u8 *pkt;
    u8 *pk2;

    sceVu0CopyMatrix(P(m), P(gEftDust + 0x70));
    if (farg1 != 0.0f) {
        sceVu0UnitMatrix(rot);
        sceVu0RotMatrixZ(rot, rot, EftMath_WrapAngle((farg1 / 180.0f) * D_003844F8));
        sceVu0MulMatrix(m, m, rot);
    }
    func_003126C8(&m[12], arg0);
    quad[0] = -half;
    quad[1] = -half;
    quad[2] = 0.0f;
    quad[3] = 1.0f;
    quad[4] = half;
    quad[5] = -half;
    quad[6] = 0.0f;
    quad[7] = 1.0f;
    quad[8] = -half;
    quad[9] = half;
    quad[10] = 0.0f;
    quad[11] = 1.0f;
    quad[12] = half;
    quad[13] = half;
    quad[14] = 0.0f;
    quad[15] = 1.0f;
    for (i = 0; i < 4; i++) {
        sceVu0ApplyMatrix(P(&quad[i * 4]), P(m), P(&quad[i * 4]));
        func_001405D0(&out[i * 4], arg1, &quad[i * 4]);
        if (EftShotFx_IsOnScreen(P(&out[i * 4]), 2) == 0) {
            return;
        }
    }

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x80;
    if (pkt == NULL) {
        return;
    }
    *(u64 *)(pkt + 0x10) = 0xC400000000008001ULL;
    *(u64 *)(pkt + 0x18) = 0xF42424242160ULL;
    *(f32 *)(pkt + 0x6C) = 1.0f;
    *(u64 *)(pkt + 0x20) = 0x54;
    *(u64 *)(pkt + 0x00) = 0xA0000007ULL;
    pkt[0x30] = r;
    pkt[0x31] = g;
    pkt[0x32] = b;
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(f32 *)(pkt + 0x48) = 1.0f;
    *(f32 *)(pkt + 0x5C) = 1.0f;
    *(f32 *)(pkt + 0x68) = 1.0f;
    pkt[0x33] = a;
    *(u32 *)(pkt + 0x38) = 0;
    *(u32 *)(pkt + 0x3C) = 0;
    *(u32 *)(pkt + 0x4C) = 0;
    *(u32 *)(pkt + 0x58) = 0;
    corner_pack(pkt + 0x40, &out[0]);
    corner_pack(pkt + 0x50, &out[4]);
    corner_pack(pkt + 0x60, &out[8]);
    corner_pack(pkt + 0x70, &out[12]);
    key = (out[2] + out[14] + (out[10] + out[6])) >> 10;
    if (func_001420F0() == 0) {
        key = key + 500;
    } else {
        key = key - 500;
    }
    *(u64 *)(pkt + 0x28) = *arg7;
    if (extra != 0) {
        pk2 = D_00387AD8;
        D_00387AD8 = pk2 + 0x30;
        if (pk2 == NULL) {
            return;
        }
        *(u64 *)(pk2 + 0x00) = 0xA0000002ULL;
        *(u64 *)(pk2 + 0x10) = 0x1000000000008001ULL;
        *(u64 *)(pk2 + 0x18) = 0xE;
        *(u64 *)(pk2 + 0x20) = ((u64)extra << 4) | 0x5000D;
        *(u64 *)(pk2 + 0x28) = 0x47;
        ot_link(pk2, key, slot);
    }
    ot_link(pkt, key, slot);
    if (extra != 0) {
        pk2 = D_00387AD8;
        D_00387AD8 = pk2 + 0x30;
        if (pk2 == NULL) {
            return;
        }
        *(u64 *)(pk2 + 0x00) = 0xA0000002ULL;
        *(u64 *)(pk2 + 0x10) = 0x1000000000008001ULL;
        *(u64 *)(pk2 + 0x18) = 0xE;
        *(u64 *)(pk2 + 0x20) = 0x50000;
        *(u64 *)(pk2 + 0x28) = 0x47;
        ot_link(pk2, key, slot);
    }
}
