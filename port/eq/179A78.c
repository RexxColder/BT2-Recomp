#include "common.h"

#define F32(p, off) (*(f32 *)((p) + (off)))
#define S32(p, off) (*(s32 *)((p) + (off)))
#define PTR(p, off) (*(u8 **)((p) + (off)))

extern u8 *gEftAuraPool;

/* EftSpr_DrawRot: 21 arguments (4 colour bytes, 8 floats in f12..f19, then t0..t3 and 5 stack words). */
void func_001F0EE8(u32 r, u32 g, u32 b, u32 a, f32 posX, f32 posY, f32 posZ, f32 uvX, f32 uvY, f32 uvZ, f32 uvW,
                   f32 rot, s32 p12, s32 p13, s32 p14, s32 p15, s32 p16, u32 size, s32 p18, s32 unk7, u8 *tex);

/* Float to u32 as the MIPS code does it: trunc.w.s below 2^31, else the high bit is or-ed in. */
#define FTOU(x) ({ f32 ftou_x = (x); (ftou_x >= 2147483648.0f) ? ((u32)(s32)(ftou_x - 2147483648.0f) | 0x80000000u) : (u32)(s32)ftou_x; })

/* 0x00179A78: draws every spark of the aura's used list whose objId byte equals objId (a1), with the
 * colour from the spark * 255 (times the draw alpha for the alpha channel). The draw alpha is alpha (a2,
 * f12) when aura->flags has 0x20, else aura->+0x3C * aura->+0x54 * alpha. Sparks link through +0xA0. */
void EftAura_DrawSparks(u8 *aura, s32 objId, f32 alpha) {
    u8 *pool = gEftAuraPool;
    u8 *tex = pool + 0x288;
    u8 *spark;
    f32 a;

    if (S32(aura, 0x00) & 0x20) {
        a = alpha;
    } else {
        a = F32(aura, 0x3C) * F32(aura, 0x54) * alpha;
    }

    spark = PTR(pool, 0x20);
    while (spark != NULL) {
        if (*(u8 *)(spark + 4) == objId) {
            func_001F0EE8(FTOU(F32(spark, 0x70) * 255.0f) & 0xFF, FTOU(F32(spark, 0x74) * 255.0f) & 0xFF,
                          FTOU(F32(spark, 0x78) * 255.0f) & 0xFF, FTOU(F32(spark, 0x7C) * 255.0f * a) & 0xFF,
                          F32(spark, 0x30), F32(spark, 0x34), F32(spark, 0x38),
                          F32(spark, 0x90), F32(spark, 0x94), F32(spark, 0x98), F32(spark, 0x9C),
                          F32(spark, 0x10), 0, 0, 0x40, 0x40, 0,
                          FTOU(F32(spark, 0x18) * 4096.0f), 0, *(u8 *)(spark + 7), tex);
        }
        spark = PTR(spark, 0xA0);
    }
}
