#include "common.h"

u8 *Dma_BeginDirect(u8 *arg0, u8 *arg1);
s32 Dma_EndDirect(u8 *end);
s32 Tex_Log2Size(s32 size);
s32 func_002668A8(u8 *obj, f32 *out);

#define PQ(lo, hi)                    \
    do {                              \
        *(u64 *)dl = (u64)(lo);       \
        *(u64 *)(dl + 8) = (u64)(hi); \
        dl += 0x10;                   \
    } while (0)

/* 0x002634F0: builds a GIF packet list for a textured fade quad (obj, tex, params, mode, alpha) */
s32 func_002634F0(u8 *obj, u8 *tex, u8 *params, u32 mode, f32 alpha) {
    u8 sp[0x20] __attribute__((aligned(16)));
    u8 *dl;
    u64 base;
    s32 flag = mode & 0xFF;
    s32 l0, l1;
    u32 q;

    dl = Dma_BeginDirect(obj, tex);
    base = (u64)(s64)(*(s32 *)(tex + 0xC0) >> 5);
    PQ(0x100000000000000CULL, 0xE);
    PQ(base | 0x10000ULL, 0x4C);
    PQ(0x1310000E0ULL, 0x4E);
    PQ(0x7E0000007E00ULL, 0x18);
    PQ(0x3F0000003F0000ULL, 0x40);
    PQ(0xFC000FC00AULL, 8);
    PQ(0x30000ULL, 0x47);
    PQ(0x8000000064ULL, 0x42);
    PQ(0, 0x14);
    PQ(0, 0x3F);
    l0 = Tex_Log2Size(0x40);
    l1 = Tex_Log2Size(0x40);
    PQ((u64)(s64)(((*(s32 *)(tex + 0xC0) + 0x40) | 0x4000)) | 0x800000000ULL | ((u64)(s64)l0 << 30) |
           0x400000000ULL | ((u64)(s64)l1 << 26),
       6);
    PQ(0x156, 0);
    PQ(0x3F80000080808080ULL, 1);

    if (flag != 0) {
        PQ(0x1000000000000003ULL, 0xE);
        PQ(0x46, 0);
        PQ(0x3F800000FF000000ULL, 1);
        PQ(0x44, 0x42);
        PQ(0x2400000000000001ULL, 0x55);
        PQ(0x7E007E00ULL, 0x82008200ULL);
    } else {
        PQ(0x4400000000000001ULL, 0x5353);
        PQ(0, 0x7E007E00ULL);
        PQ(0x4000400ULL, 0x82008200ULL);
        PQ(0x1000000000000004ULL, 0xE);
        PQ(base | 0x10000ULL | 0xFF00000000000000ULL, 0x4C);
        q = (u32)*(f32 *)(params + 0x34);
        PQ(((u64)(q & 0xFF) << 32) | 0x64, 0x42);
        PQ(0, 0x3F);
        l0 = Tex_Log2Size(0x40);
        l1 = Tex_Log2Size(0x40);
        PQ((u64)(s64)((*(s32 *)(tex + 0xC0) + 0x80) | 0x4000) | ((u64)(s64)l0 << 26) | ((u64)(s64)l1 << 30), 6);
        PQ(0x4400000000000001ULL, 0x5353);
        PQ(0, 0x7E007E00ULL);
        PQ(0x4000400ULL, 0x82008200ULL);
    }

    if (func_002668A8(obj, (f32 *)(sp + 0x10))) {
        f32 f = *(f32 *)(sp + 0x10) * 70.0f;
        PQ(0x1000000000000004ULL, 0xE);
        PQ(base | 0x10000ULL | 0xFF00000000000000ULL, 0x4C);
        PQ(0x46, 0);
        PQ(0x3F800000006644FFULL, 1);
        PQ(((u64)(s64)(s32)f << 32) | 0x64, 0x42);
        PQ(0x2400000000000001ULL, 0x55);
        PQ(0x7E007E00ULL, 0x82008200ULL);
    }

    if (*(u32 *)(obj + 0xAF0) & 0x400000) {
        sp[0] = (u8)(u32) * (f32 *)(obj + 0xBC0);
        sp[1] = (u8)(u32) * (f32 *)(obj + 0xBC4);
        sp[2] = (u8)(u32) * (f32 *)(obj + 0xBC8);
        sp[3] = (u8)(u32) * (f32 *)(obj + 0xBCC);
        PQ(0x1000000000000004ULL, 0xE);
        PQ(base | 0x10000ULL | 0xFF00000000000000ULL, 0x4C);
        PQ(0x46, 0);
        PQ((u64)sp[0] | ((u64)sp[2] << 16 | (u64)sp[1] << 8) | 0x3F80000000000000ULL, 1);
        PQ(((u64)sp[3] << 32) | 0x64, 0x42);
        PQ(0x2400000000000001ULL, 0x55);
        PQ(0x7E007E00ULL, 0x82008200ULL);
    }

    if (0.0f < alpha) {
        s32 a = (s32)(alpha * 128.0f);
        if (a > 0x80) {
            a = 0x80;
        }
        PQ(0x1000000000000004ULL, 0xE);
        PQ(base | 0x10000ULL | 0xFF00000000000000ULL, 0x4C);
        PQ(0x46, 0);
        PQ(0x3F8000000000FFFFULL, 1);
        PQ(((u64)(s64)a << 32) | 0x68, 0x42);
        PQ(0x2400000000000001ULL, 0x55);
        PQ(0x7E007E00ULL, 0x82008200ULL);
    }
    return Dma_EndDirect(dl);
}
