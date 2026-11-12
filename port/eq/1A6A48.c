#include "common.h"

s32 func_001267E8(s32 objId, u8 kind);
void func_00128EF0(void);
void func_00128F08(void);
void func_00128F90(u8 *mtx);
void func_00129C28(u8 *dst, u8 *src);
void func_00129B58(u8 *dst, u8 *a, u8 *b);
void Vec3_Cross(u8 *dst, u8 *a, u8 *b);
void Vec3_Normalize(u8 *dst, u8 *src);
void func_0012A360(u8 *dst, u8 *dir, u8 *base, f32 scale);
f32 Vec3_Dot(u8 *a, u8 *b);
void Vec3_Scale(u8 *dst, u8 *src, f32 s);
f32 func_00129E50(u8 *a, u8 *b);
s32 func_001294B0(void *out, void *in, s32 n, s32 flag);
void func_00129660(u8 *vtx, u8 *pos, u8 *uv, u8 *color);
s32 func_0012D170(u8 *vtx, s32 n, u8 a2, u8 a3, u8 a4, s64 tex0, s32 z);
void func_001A7390(u8 r, u8 g, u8 b, u8 a, f32 x, f32 y, f32 z, f32 w, f32 h, f32 u0, f32 v0, f32 u1,
                   f32 v1, f32 scale, f32 rot, s32 layer, u64 tex0);

extern u8 *gBtlCamView;
extern u8 D_0036EA40[];
extern f32 D_00384E98, D_00384E9C, D_00384EA0, D_00384EA4, D_00384EA8;
extern s32 D_00387838;

void func_001A6A48(u8 *task) {
    u8 *w = *(u8 **)(task + 0x38);
    f32 width = *(f32 *)(w + 0x1C);
    f32 limit = D_00384E98;
    f32 sideLimit = D_00384E9C;
    f32 side[4];
    f32 prevSide[4];
    f32 mid[4];
    f32 color[4];
    f32 camPos[4];
    f32 toCam[4];
    f32 quad[16];
    f32 prev[8];
    s32 scr[16];
    f32 uv[16];
    f32 vtx[116] __attribute__((aligned(16))); /* asm: sp+0x20..0x1EF (0x1D0 bytes); 12D170 clips into it (was 36: stack smash) */
    u8 *p;
    s32 first = 1;
    s32 i;
    s32 j;
    s32 seg;
    s32 z;
    f32 bias;

    __builtin_memcpy(uv, D_0036EA40, 0x40);
    if (func_001267E8(*(s32 *)(w + 4), *(u8 *)(w + 8))) {
        return;
    }
    p = w + 0x70;
    func_00128EF0();
    i = 0;
    func_00128F90(gBtlCamView + 0x100);
    func_00129C28((u8 *)camPos, gBtlCamView + 0x1F0);
    for (; i < *(s32 *)(w + 0x1B0) - 1; i++) {
        seg = 1;
        if (i == 0) {
            seg = 2;
        }
        if (i == *(s32 *)(w + 0x1B0) - 2) {
            seg = 0;
        }
        func_00129C28((u8 *)color, w + 0x60);
        func_00129B58((u8 *)side, p + 0x10, p);
        func_00129B58((u8 *)toCam, p, (u8 *)camPos);
        Vec3_Cross((u8 *)side, (u8 *)side, (u8 *)toCam);
        Vec3_Normalize((u8 *)side, (u8 *)side);
        if (first) {
            func_0012A360((u8 *)&quad[0], (u8 *)side, p, width);
            func_0012A360((u8 *)&quad[4], (u8 *)side, p, -width);
            first = 0;
        } else {
            if (Vec3_Dot((u8 *)side, (u8 *)prevSide) < 0.0f) {
                Vec3_Scale((u8 *)side, (u8 *)side, -1.0f);
            }
            if (__builtin_fabsf(Vec3_Dot((u8 *)side, (u8 *)prevSide)) < limit) {
                color[3] = 0.0f;
                if (*(u32 *)(w + 0x28) & 1) {
                    color[3] = *(f32 *)(w + 0x6C);
                }
                if (func_00129E50(p, p + 0x10) > sideLimit) {
                    bias = (f32)D_00387838;
                    mid[0] = (*(f32 *)(p + 0) + *(f32 *)(p + 0x10)) * 0.5f;
                    mid[1] = (*(f32 *)(p + 4) + *(f32 *)(p + 0x14)) * 0.5f;
                    mid[2] = (*(f32 *)(p + 8) + *(f32 *)(p + 0x18)) * 0.5f;
                    func_001A7390((u8)(u32)(*(f32 *)(w + 0x60) + bias), (u8)(u32)(*(f32 *)(w + 0x64) + bias),
                                  (u8)(u32)(*(f32 *)(w + 0x68) + bias), (u8)(u32)(*(f32 *)(w + 0x6C) * sideLimit),
                                  *(f32 *)(p + 0), *(f32 *)(p + 4), *(f32 *)(p + 8), D_00384EA0, D_00384EA0,
                                  0.0f, 0.0f, 1.0f, 1.0f, *(f32 *)(w + 0x1C), 0.0f, 1, *(u64 *)(w + 0x218));
                    func_001A7390((u8)(u32)(*(f32 *)(w + 0x60) + bias), (u8)(u32)(*(f32 *)(w + 0x64) + bias),
                                  (u8)(u32)(*(f32 *)(w + 0x68) + bias), (u8)(u32)(*(f32 *)(w + 0x6C) * sideLimit),
                                  mid[0], mid[1], mid[2], D_00384EA4, D_00384EA4,
                                  0.0f, 0.0f, 1.0f, 1.0f, *(f32 *)(w + 0x1C), 0.0f, 1, *(u64 *)(w + 0x218));
                    func_001A7390((u8)(u32)(*(f32 *)(w + 0x60) + bias), (u8)(u32)(*(f32 *)(w + 0x64) + bias),
                                  (u8)(u32)(*(f32 *)(w + 0x68) + bias), (u8)(u32)(*(f32 *)(w + 0x6C) * sideLimit),
                                  *(f32 *)(p + 0x10), *(f32 *)(p + 0x14), *(f32 *)(p + 0x18), D_00384EA8,
                                  D_00384EA8, 0.0f, 0.0f, 1.0f, 1.0f, *(f32 *)(w + 0x1C), 0.0f, 1,
                                  *(u64 *)(w + 0x218));
                }
            }
            func_00129C28((u8 *)&quad[0], (u8 *)&prev[0]);
            func_00129C28((u8 *)&quad[4], (u8 *)&prev[4]);
        }
        func_0012A360((u8 *)&quad[8], (u8 *)side, p + 0x10, width);
        func_0012A360((u8 *)&quad[12], (u8 *)side, p + 0x10, -width);
        func_00129C28((u8 *)prevSide, (u8 *)side);
        func_00129C28((u8 *)&prev[0], (u8 *)&quad[8]);
        func_00129C28((u8 *)&prev[4], (u8 *)&quad[12]);
        quad[15] = 1.0f;
        quad[11] = 1.0f;
        quad[7] = 1.0f;
        quad[3] = 1.0f;
        func_001294B0(scr, quad, 4, 1);
        z = (scr[2] + scr[6] + scr[10] + scr[14]) >> 10;
        for (j = 0; j < 2; j++) {
            func_00129660((u8 *)&vtx[0], (u8 *)&quad[j * 4], (u8 *)&uv[j * 4], (u8 *)color);
            func_00129660((u8 *)&vtx[12], (u8 *)&quad[j * 4 + 4], (u8 *)&uv[j * 4 + 4], (u8 *)color);
            func_00129660((u8 *)&vtx[24], (u8 *)&quad[j * 4 + 8], (u8 *)&uv[j * 4 + 8], (u8 *)color);
            func_0012D170((u8 *)vtx, 1, 0, 0, 0, *(s64 *)(w + 0x200 + seg * 8), z);
        }
        p = p + 0x10;
    }
    func_00128F08();
}
