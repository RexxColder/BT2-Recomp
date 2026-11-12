#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

extern f32 EftStage_GetTintScale(void);
extern void Vec4_Sub(u8 *arg0, u8 *arg1, u8 *arg2);
extern void Vec3_Normalize(u8 *arg0, u8 *arg1);
extern void EftMath_MtxFromDir(u8 *arg0, u8 *arg1, f32 farg0);
extern void Vec4_Set(u8 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
extern void Mtx_MulVec4(u8 *arg0, u8 *arg1, u8 *arg2);
extern void Vec3_Add(u8 *arg0, u8 *arg1, u8 *arg2);
extern s32 func_001294B0(void *a0, void *a1, s32 a2, s32 a3);

extern f32 D_00384300;
extern f32 D_00384304;
extern f32 D_00384308;
extern f32 D_0038430C;
extern u8 *gBtlCamView;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

/* float -> u32 with the 2^31 split used by the game */
static u32 FloatToU32(f32 x) {
    if (x >= 2147483648.0f) {
        return (u32)(s32)(x - 2147483648.0f) | 0x80000000;
    }
    return (u32)(s32)x;
}

/* A projected vertex is off screen when z <= 0 or x/y fall outside 1..0xFFEF. */
static s32 VertOffscreen(s32 x, s32 y, s32 z) {
    if (z <= 0) return 1;
    if (x > 0xFFEF) return 1;
    if (x <= 0) return 1;
    if (y > 0xFFEF) return 1;
    return y < 1;
}

s32 EftSteam_DrawQuad(f32 *color, u8 *pos, s32 ot, u64 tex, f32 w, f32 h, f32 u0, f32 v0, f32 u1, f32 v1, f32 scale, f32 angle) {
    u8 sp[0xD0];
    f32 tint;
    f32 hh;
    f32 ww;
    u8 *pkt;
    s32 i;
    s32 z8;
    u8 *slot;
    u8 *node;

    tint = EftStage_GetTintScale();
    if (D_00384300 < angle) {
        angle = angle - D_00384304;
    } else if (angle < D_00384308) {
        angle = angle + D_0038430C;
    }
    hh = h * scale;
    ww = w * scale;
    hh = hh * 0.0625f;
    ww = ww * 0.0625f;

    Vec4_Sub(sp + 0x80, gBtlCamView + 0x1F0, pos);
    Vec3_Normalize(sp + 0x80, sp + 0x80);
    EftMath_MtxFromDir(sp + 0x90, sp + 0x80, angle);
    Vec4_Set(sp + 0x40, -ww, -hh, 0.0f, 1.0f);
    Vec4_Set(sp + 0x50, ww, -hh, 0.0f, 1.0f);
    Vec4_Set(sp + 0x60, -ww, hh, 0.0f, 1.0f);
    Vec4_Set(sp + 0x70, ww, hh, 0.0f, 1.0f);
    for (i = 0; i < 4; i++) {
        u8 *v = sp + 0x40 + i * 16;
        Mtx_MulVec4(v, sp + 0x90, v);
        Vec3_Add(v, v, pos);
        *(f32 *)(v + 0xC) = 1.0f;
    }
    func_001294B0(sp, sp + 0x40, 4, 1);

    for (i = 0; i < 4; i++) {
        if (VertOffscreen(*(s32 *)(sp + i * 16), *(s32 *)(sp + i * 16 + 4), *(s32 *)(sp + i * 16 + 8))) {
            return 1;
        }
    }

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x80;
    *(u64 *)(pkt + 0x20) = 0x54;
    *(u64 *)(pkt + 0x18) = 0xF42424242160ULL;
    *(u64 *)(pkt + 0x28) = tex;
    if ((u32)(*(u64 *)(pkt + 0x28) >> 32) == 0 && (u32)*(u64 *)(pkt + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 13AD28 %llx", (unsigned long long)*(u64 *)(pkt + 0x28)); /* TEMP TEX0 */
    *(u64 *)(pkt + 0x00) = 0xA0000007ULL;
    *(u64 *)(pkt + 0x10) = 0xC400000000008001ULL;
    *(u8 *)(pkt + 0x30) = (u8)FloatToU32(color[0] * tint);
    *(u8 *)(pkt + 0x31) = (u8)FloatToU32(color[1] * tint);
    *(u8 *)(pkt + 0x32) = (u8)FloatToU32(color[2] * tint);
    *(u8 *)(pkt + 0x33) = (u8)FloatToU32(color[3]);
    *(f32 *)(pkt + 0x34) = 1.0f;
    *(f32 *)(pkt + 0x4C) = v0;
    *(f32 *)(pkt + 0x58) = u0;
    *(f32 *)(pkt + 0x68) = u1;
    *(f32 *)(pkt + 0x6C) = v1;
    *(f32 *)(pkt + 0x38) = u0;
    *(f32 *)(pkt + 0x3C) = v0;
    *(f32 *)(pkt + 0x48) = u1;
    *(f32 *)(pkt + 0x5C) = v1;
    for (i = 0; i < 4; i++) {
        u8 *vert = pkt + 0x40 + i * 0x10;
        *(u16 *)(vert + 0) = *(u16 *)(sp + i * 16);
        *(u16 *)(vert + 2) = *(u16 *)(sp + i * 16 + 4);
        *(u32 *)(vert + 4) = (*(u32 *)(sp + i * 16 + 8) & 0xFFFFFF) | 0xFF000000;
    }

    z8 = *(s32 *)(sp + 8) >> 8;
    if (z8 < 0) {
        slot = D_00387AE0 + ot * 8;
        node = *(u8 **)(slot + 4);
    } else if (z8 < 0x1000) {
        slot = D_00387AE0 + (z8 * 2 + ot) * 8;
        node = *(u8 **)(slot + 4);
    } else {
        slot = D_00387AE0 + ot * 8 + 0xFFF0;
        node = *(u8 **)(slot + 4);
    }
    *(u8 **)(node + 4) = pkt;
    *(u8 **)(slot + 4) = pkt;
    return (s32)node;
}
