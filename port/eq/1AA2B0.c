#include "common.h"

/* Float to u32 as the MIPS code does it: trunc.w.s below 2^31, else the high bit is or-ed in. */
#define FTOU(x) ({ f32 ftou_x = (x); (ftou_x >= 2147483648.0f) ? ((u32)(s32)(ftou_x - 2147483648.0f) | 0x80000000u) : (u32)(s32)ftou_x; })

extern u8 *D_00387848;

/* EftSpr-style draw call (sub_1F0418): 4 colour bytes, 8 floats in f12..f19, then t0..t3 and 3 stack words. */
s32 func_001F0418(u32 r, u32 g, u32 b, u32 a, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                  s32 t0, s32 t1, s32 t2, s32 t3, s32 s0, s32 s1, u8 *out);

/* 0x001AA2B0: obj = arg0->+0x38. Entry = table[obj->+0x10] (16-byte entries, table = *(D_00387848 + 8)).
 * colour bytes = entry floats +0x10..+0x18, alpha = entry +0x1C * obj->+0x34; t0 = t1 = trunc of
 * entry+4 * 32 * obj->+0x2C * obj->+0x30; float args from obj +0x90/+0x94/+0x98 and +0xC0..+0xCC, f19 = 0.
 * Output pointer = D_00387848 + 8 + 16 + 16 * (18 * obj->+0x14 + obj->+0x10). Returns the callee result. */
s32 func_001AA2B0(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x38);
    u8 *tbl = *(u8 **)(D_00387848 + 8);
    s32 idx = *(s32 *)(obj + 0x10);
    s32 cnt = *(s32 *)(obj + 0x14);
    u8 *ent = tbl + 16 * idx;
    f32 scale = *(f32 *)(tbl + 4) * 32.0f * *(f32 *)(obj + 0x2C) * *(f32 *)(obj + 0x30);
    u32 r = FTOU(*(f32 *)(ent + 0x10)) & 0xFF;
    u32 g = FTOU(*(f32 *)(ent + 0x14)) & 0xFF;
    u32 b = FTOU(*(f32 *)(ent + 0x18)) & 0xFF;
    u32 a = FTOU(*(f32 *)(ent + 0x1C) * *(f32 *)(obj + 0x34)) & 0xFF;
    u8 *out = D_00387848 + 8 + 16 + 16 * (18 * cnt + idx);

    return func_001F0418(r, g, b, a,
                         *(f32 *)(obj + 0x90), *(f32 *)(obj + 0x94), *(f32 *)(obj + 0x98), *(f32 *)(obj + 0xC0),
                         *(f32 *)(obj + 0xC4), *(f32 *)(obj + 0xC8), *(f32 *)(obj + 0xCC), 0.0f,
                         FTOU(scale), FTOU(scale), 0, 4096, 0, 1, out);
}
