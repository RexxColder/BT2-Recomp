#include "common.h"

extern u8 *gEftSurf;
extern u8 *D_003876A0;
extern u8 *gBtlCamView;

s64 EftVram_AddImage(u8 *arg0, s32 arg1, s32 arg2);
s64 EftVram_AddClut(u8 *arg0);
void func_0012A4B0(u8 *dst, u8 *src, u8 *pal, u32 r, u32 g, u32 b);
void func_0012A610(u8 *dst, u8 *src, u8 *m, u8 *vecs, u8 *nrm, f32 scale);
extern s32 sceVu0UnitMatrix();
extern void sceVu0CopyMatrix(u8 *dst, u8 *src);

/* byte copy; optnone so clang does not turn it into memcpy on game pointers */
__attribute__((noinline, optnone)) static void blob_copy(u8 *d, u8 *s, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

__attribute__((noinline, optnone)) static void blob_clear(u8 *d, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) {
        d[i] = 0;
    }
}

#define FP(p, o) (*(f32 *)((p) + (o)))
#define PP(p, o) (*(u8 **)((p) + (o)))

void EftSurf_RenderPalettes(void) {
    u8 m[0x40];
    u8 *surf;
    u8 *s;
    u8 *pal;
    u8 *ent;
    u8 *entClut;
    u8 *ent2;
    u32 r, g, b;

    surf = gEftSurf;
    if (surf == NULL) {
        return;
    }
    s = surf + 0x240;
    if ((*(u32 *)(s + 0x1114) & 8) == 0) {
        return;
    }

    ent = PP(s, 0x1078) + *(s32 *)(s + 0x1100) * 16;
    blob_copy(PP(s, 0x490), PP(PP(ent, 8), 0x3C) + 0x60, 0x400);
    pal = s + 0xE40;
    blob_clear(PP(s, 0x950), 0x400);
    r = (u32)FP(s, 0x1090) & 0xFF;
    g = (u32)FP(s, 0x1094) & 0xFF;
    b = (u32)FP(s, 0x1098) & 0xFF;
    func_0012A4B0(PP(s, 0x950), PP(s, 0x490), pal, r, g, b);
    blob_clear(PP(s, 0xE10), 0x400);
    sceVu0UnitMatrix(m);
    if (*(u64 *)(D_003876A0 + 0x4D8) & 2) {
        FP(m, 0x18) = 0.5f;
    } else {
        sceVu0CopyMatrix(m, gBtlCamView);
    }
    func_0012A610(PP(s, 0xE10), PP(s, 0x490), m, s + 0x10C0, pal, FP(s, 0x10B0));
    *(s64 *)ent = EftVram_AddImage(ent, 1, 0);

    ent2 = PP(s, 0x1078) + (*(s32 *)(s + 0x1108) + *(s32 *)(s + 0x1110)) * 16;
    blob_copy(PP(PP(ent2, 8), 0x3C) + 0x60, PP(s, 0x950), 0x400);
    *(s64 *)ent2 = (*(s64 *)ent & (s64)0xFFF8001FFFFFFFFFLL) | (EftVram_AddClut(ent2) << 37);

    entClut = PP(s, 0x1078) + (*(s32 *)(s + 0x110C) + *(s32 *)(s + 0x1110)) * 16;
    blob_copy(PP(PP(entClut, 8), 0x3C) + 0x60, PP(s, 0xE10), 0x400);
    *(s64 *)entClut = (*(s64 *)ent & (s64)0xFFF8001FFFFFFFFFLL) | (EftVram_AddClut(entClut) << 37);
}
