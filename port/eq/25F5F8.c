#include "common.h"

extern f32 D_00386E84;
s32 func_0025FBE8(u8 *arg0, s64 arg1);
s32 BtlObjAnim_GetEventArg(u8 *arg0, s64 arg1);
s32 BtlObjAnim_MaskToNode(s32 arg0);

s32 func_0025F5F8(u8 *arg0) {
    u8 *s0 = arg0 + 0xD60;
    u8 *ent;
    u8 *p;
    u8 *ptrs;
    u8 *src;
    s32 n;
    s32 i;
    s32 j;
    s32 t2 = 0;
    s32 t0 = 0;
    s32 A;
    s32 H;
    s32 s1 = 0;
    s32 t9 = 0;
    s32 t8 = 0;
    s32 t5 = 0;
    s32 cur8;
    s32 result;
    u64 key;
    f32 f3;
    f32 base;

    result = -1;
    *(u8 *)(s0 + 0x1D) = 0xFF;
    *(u8 *)(s0 + 0x1C) = 0;

    ent = *(u8 **)(arg0 + 0xBF8);
    if (ent == NULL) {
        return result;
    }

    base = D_00386E84;
    A = (s32)(*(f32 *)(arg0 + 0xBE0) + base);
    H = (s32)(*(f32 *)(arg0 + 0xBE4) + base);
    if (A == H) {
        H = H - 1;
    }

    n = ent[1];
    ptrs = ent + 0x94;
    if (n != 0) {
        for (i = 0, p = ptrs; i < n; i++, p += 16) {
            key = *(u64 *)p;
            if (key & 1) {
                s1 = *(u16 *)(p + 8);
                t8 = *(s32 *)(p + 12);
                t5 = (s32)((key >> 32) & 1);
                t9 = *(u16 *)(p + 10);
                t2++;
            }
            if (!(key & 2)) {
                continue;
            }
            t0++;
            if (t2 != t0) {
                continue;
            }
            *(u8 *)(s0 + 0x1C) += 1;
            if ((s8)*(u8 *)(s0 + 0x1D) < 0) {
                if (A >= s1) {
                    cur8 = *(u16 *)(p + 8);
                    if (H < cur8) {
                        src = ent + 4 * t9;
                        f3 = *(f32 *)(s0 + 0x24);
                        *(u32 *)(s0 + 0x00) = *(u32 *)(src + 0x00);
                        *(u32 *)(s0 + 0x04) = *(u32 *)(src + 0x04);
                        *(u32 *)(s0 + 0x08) = *(u32 *)(src + 0x08);
                        *(f32 *)(s0 + 0x10) = *(f32 *)(src + 0x10) * f3;
                        *(f32 *)(s0 + 0x14) = *(f32 *)(src + 0x14) * f3;
                        *(f32 *)(s0 + 0x18) = *(f32 *)(src + 0x18) * f3;
                        *(u8 *)(s0 + 0x1D) = (u8)(t0 - 1);
                        *(s32 *)(s0 + 0x0C) = t8;
                        *(u8 *)(s0 + 0x1F) = (u8)t5;
                    }
                }
            }
        }
    }

    /* L25F784 */
    if ((s8)*(u8 *)(s0 + 0x1C) > 0) {
        i = 0;
        if ((s8)*(u8 *)(s0 + 0x1D) < 0) {
            *(u8 *)(s0 + 0x1D) = 0xFF;
            if (n == 0) {
                t2 = 0;
                goto L25F938;
            }
            p = ptrs;
            if (!(*(u32 *)p & 1)) {
                i = 1;
            } else if (A < *(u16 *)(p + 8)) {
                goto L25F824;
            } else {
                *(u8 *)(s0 + 0x1D) = (u8)(*(u8 *)(s0 + 0x1D) - 1);
                i = 1;
            }
            while (i < n) {
                p = ptrs + 16 * i;
                if (!(*(u32 *)p & 1)) {
                    i++;
                    continue;
                }
                if (A >= *(u16 *)(p + 8)) {
                    *(u8 *)(s0 + 0x1D) = (u8)(*(u8 *)(s0 + 0x1D) - 1);
                    i++;
                    continue;
                }
                break;
            }
            i = 0;
        }
    }

L25F824:
    t2 = 0;
    if (n == 0) {
        goto L25F938;
    }
    for (i = 0, p = ptrs; i < n; i++, p += 16) {
        key = *(u64 *)p;
        if ((key & ~(u64)1) == 0) {
            continue;
        }
        cur8 = *(u16 *)(p + 8);
        if (A < cur8) {
            continue;
        }
        if (H > 0) {
            if (H >= cur8) {
                continue;
            }
        } else {
            if (cur8 < H) {
                continue;
            }
        }
        if (t2 >= 8) {
            continue;
        }
        for (j = 0; j < t2; j++) {
            if (*(u64 *)(s0 + 0x28 + 8 * j) == key) {
                break;
            }
        }
        if (j != t2) {
            *(u32 *)(s0 + 0x68 + 4 * j) |= *(u32 *)(p + 12);
        } else {
            *(u64 *)(s0 + 0x28 + 8 * t2) = key;
            *(u32 *)(s0 + 0x68 + 4 * t2) = *(u32 *)(p + 12);
            t2++;
        }
    }

L25F938:
    *(u8 *)(s0 + 0x1E) = (u8)t2;
    if (func_0025FBE8(arg0, 0x400000000LL) == 0) {
        return 0;
    }
    result = BtlObjAnim_GetEventArg(arg0, 0x400000000LL);
    result = BtlObjAnim_MaskToNode(result);
    *(s32 *)(s0 + 0x20) = result;
    return result;
}
