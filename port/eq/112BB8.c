#include "common.h"

void *Dma_BeginDirect(void);
void Dma_EndDirect(s32 arg0);
s32 func_00277E68(s32 arg0);

#define S16_AT(rec, off) (*(s16 *)((rec) + (off)))
#define S32_AT(rec, off) (*(s32 *)((rec) + (off)))
#define U8_AT(rec, off) (*(u8 *)((rec) + (off)))

/* Sprite packet builder: walks 96-byte records (flags at +0), emits one 80-byte GIF block
   (rgba tag, prim tag, four 16-byte vertices) for each visible record, then closes the packet. */
void func_00112BB8(u8 *arg0, s32 arg1) {
    s32 v2 = arg1 ? 8 : 0;
    s32 v4 = 0;
    u64 *v5;
    u64 *v7;
    u8 *v8;
    u8 *rec = arg0;
    s32 flags;
    s32 v18;
    s32 v19;
    s32 v20;
    s32 v21;
    s32 v22;
    s32 v23;
    s32 v24;
    s32 v25;
    u64 *v16;

    v5 = (u64 *)Dma_BeginDirect();
    v5[0] = 0;
    v5[1] = 0;
    v7 = v5;
    v8 = (u8 *)(v5 + 2);

    while ((S32_AT(rec, 0) & 2) == 0) {
        flags = S32_AT(rec, 0);
        if ((flags & 1) != 0) {
            if (flags >= 0) {
                s32 x0 = S16_AT(rec, 4);
                s32 x1 = S16_AT(rec, 6);
                s32 x2 = S16_AT(rec, 8);
                s32 x3 = S16_AT(rec, 10);
                S32_AT(rec, 52) = x1;
                S32_AT(rec, 64) = x0;
                S32_AT(rec, 80) = x2;
                S32_AT(rec, 84) = x3;
                S32_AT(rec, 32) = x0;
                S32_AT(rec, 36) = x1;
                S32_AT(rec, 48) = x2;
                S32_AT(rec, 68) = x3;
            }
            if ((flags & 0x20) != 0) {
                v20 = S16_AT(rec, 12);
                v18 = S16_AT(rec, 16);
                v24 = v20;
                v22 = v18;
            } else {
                v22 = S16_AT(rec, 12);
                v24 = S16_AT(rec, 16);
                v18 = v22;
                v20 = v24;
            }
            if ((S32_AT(rec, 0) & 0x40) != 0) {
                v23 = S16_AT(rec, 14);
                v19 = S16_AT(rec, 18);
                v25 = v23;
                v21 = v19;
            } else {
                v21 = S16_AT(rec, 14);
                v25 = S16_AT(rec, 18);
                v19 = v21;
                v23 = v25;
            }

            *(u64 *)v8 = (u64)U8_AT(rec, 22)
                       | ((u64)U8_AT(rec, 25) << 24)
                       | ((u64)U8_AT(rec, 24) << 16)
                       | ((u64)U8_AT(rec, 23) << 8);
            *(u64 *)(v8 + 8) = (S32_AT(rec, 0) & 0x80) != 0 ? 852 : 340;
            v16 = (u64 *)(v8 + 16);
            v4 += 1;

            v16[0] = (u64)(s64)(16 * v18 + v2) | ((u64)(s64)(16 * v19 + v2) << 16);
            v16[1] = (u64)(s64)(16 * S32_AT(rec, 32) + 28672)
                   | ((u64)(s64)(s32)(16 * func_00277E68(S32_AT(rec, 36)) + 29184) << 16);
            v16 += 2;
            v16[0] = (u64)(s64)(16 * v20 + v2) | ((u64)(s64)(16 * v21 + v2) << 16);
            v16[1] = (u64)(s64)(16 * S32_AT(rec, 48) + 28672)
                   | ((u64)(s64)(s32)(16 * func_00277E68(S32_AT(rec, 52)) + 29184) << 16);
            v16 += 2;
            v16[0] = (u64)(s64)(16 * v22 + v2) | ((u64)(s64)(16 * v23 + v2) << 16);
            v16[1] = (u64)(s64)(16 * S32_AT(rec, 64) + 28672)
                   | ((u64)(s64)(s32)(16 * func_00277E68(S32_AT(rec, 68)) + 29184) << 16);
            v16 += 2;
            v16[0] = (u64)(s64)(16 * v24 + v2) | ((u64)(s64)(16 * v25 + v2) << 16);
            v16[1] = (u64)(s64)(16 * S32_AT(rec, 80) + 28672)
                   | ((u64)(s64)(s32)(16 * func_00277E68(S32_AT(rec, 84)) + 29184) << 16);
            v8 = (u8 *)(v16 + 2);
        }
        rec += 96;
    }

    v7[0] = (u64)(s64)v4 | 0xA400000000008000ULL;
    v7[1] = 0x5353535301ULL;
    Dma_EndDirect((s32)v8);
}
