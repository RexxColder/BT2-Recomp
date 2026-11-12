#include "common.h"

void FlushCache(s32 arg0);
void sceGsSyncPath(s32 arg0, s32 arg1);
void sceGsSetDefStoreImage(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void sceGsExecStoreImage(s32 arg0, s32 arg1);

#define PK_W(base, off, val) (*(u32 *)((u8 *)(base) + (off)) = (u32)(val))

s64 func_0027A448(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 store_image[112];
    u32 w = (u16)arg2;
    u32 h = (u16)arg3;
    s32 n;
    s32 n16;
    s32 n3;
    s32 v13;
    s32 v14;
    s32 v15;
    s32 v16;
    s32 v18;
    s32 result;
    u8 *slot;
    u8 *pk;
    u8 *ent;

    /* store-image setup: read back the frame region into a scratch packet */
    sceGsSetDefStoreImage((s32)store_image, (s16)arg1, w >> 6, 1, 0, 0, (s16)w, (s16)h);
    FlushCache(0);
    slot = arg0 + 8 + 4 * arg4;
    pk = *(u8 **)slot;
    sceGsExecStoreImage((s32)store_image, (s32)(pk + 0x70));
    sceGsSyncPath(0, 0);

    /* packet size math from the element count (3 * w * h), rounded for the 16-byte quadword */
    n = 3 * (s32)(w * h);
    n16 = (n < 0) ? n + 15 : n;
    v13 = n16 >> 4;
    v14 = v13 + 0x50000008;
    v15 = v13 | 0x8000;
    n3 = (n < 0) ? n + 3 : n;
    v18 = (n3 >> 2) << 2;
    v16 = n + 144;
    if (v16 < 0) {
        v16 = n + 159;
    }

    /* the GIF/DMA packet */
    pk = *(u8 **)slot;
    PK_W(pk, 0, 0);
    PK_W(pk, 4, 0);
    PK_W(pk, 8, 0);
    PK_W(pk, 12, v14);
    PK_W(pk, 16, 0x8004);
    PK_W(pk, 20, 0x10000000);
    PK_W(pk, 24, 14);
    PK_W(pk, 28, 0);
    PK_W(pk, 32, 0);
    PK_W(pk, 36, 0);
    PK_W(pk, 40, 80);
    PK_W(pk, 44, 0);
    PK_W(pk, 48, 0);
    PK_W(pk, 52, 0);
    PK_W(pk, 56, 81);
    PK_W(pk, 60, 0);
    PK_W(pk, 64, w);
    PK_W(pk, 68, h);
    PK_W(pk, 72, 82);
    PK_W(pk, 76, 0);
    PK_W(pk, 80, 0);
    PK_W(pk, 84, 0);
    PK_W(pk, 88, 83);
    PK_W(pk, 92, 0);
    PK_W(pk, 96, v15);
    PK_W(pk, 100, 0x08000000);
    PK_W(pk, 104, 0);
    PK_W(pk, 108, 0);
    PK_W(pk, v18 + 112, 0x8001);
    PK_W(pk, v18 + 116, 0x10000000);
    PK_W(pk, v18 + 120, 14);
    PK_W(pk, v18 + 124, 0);
    PK_W(pk, v18 + 128, 0);
    PK_W(pk, v18 + 132, 0);
    PK_W(pk, v18 + 136, 63);
    PK_W(pk, v18 + 140, 0);

    /* per-entry record in the caller's table */
    result = *(s32 *)(arg0 + 4 * arg4);
    ent = arg0 + 32 * arg4;
    PK_W(ent, 16, (v16 >> 4) + 0x30000000);
    PK_W(ent, 20, result);
    PK_W(ent, 24, 0);
    PK_W(ent, 28, 0);
    PK_W(ent, 32, 0x70000000);
    PK_W(ent, 36, 0);
    PK_W(ent, 40, 0);
    PK_W(ent, 44, 0);

    return (s64)result;
}
