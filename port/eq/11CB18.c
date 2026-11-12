#include "common.h"

extern u8 *gBtlStage;
extern u8 D_00387E88;
extern s32 D_00387F28;

s32 ColMesh_WalkBox(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void *memset(void *arg0, s32 arg1, u32 arg2);

/* 0x0011CB18: builds a 16-byte walk mask in arg0 from table entries (stride 0x10) of
 * the stage's table at +0x5C; returns the first byte. */
s32 func_0011CB18(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *t2;
    u8 *s0;
    u8 *s4;
    u8 *e;
    s32 n;
    s32 i;
    s32 r;

    t2 = *(u8 **)(gBtlStage + 0x5C);
    s0 = t2 + *(s32 *)(arg1 + 0x18) * 4;
    s4 = t2 + *(s32 *)(gBtlStage + 0x48) * 4;
    memset(arg0, 0, 0x18);

    if (D_00387E88 == 0) {
        D_00387F28 = (s32)(*(u8 **)(gBtlStage + 0x5C) + *(s32 *)(arg1 + 0x4) * 4);   /* (asm: el sw va en el delay slot del jal: antes de la llamada) */
        r = ColMesh_WalkBox(*(u8 **)(gBtlStage + 0x5C) + *(s32 *)(arg1 + 0x4) * 4, arg2, arg3, arg4);
        if (r != 0) {
            *(u8 *)(arg0 + 1) = 1;
            *(u8 *)(arg0 + 0) = 1;
        }
    }

    n = *(s32 *)(arg1 + 0x14);
    i = 0;
    while (i < n) {
        e = s4 + *(s32 *)(s0 + 4) * 80;
        if (*(s32 *)s0 == 0) {
            if ((*(s32 *)e & 1) != 0) {
                i++;
                s0 += 0x10;
                continue;
            }
        } else {
            if ((*(s32 *)e & 1) == 0) {
                i++;
                s0 += 0x10;
                continue;
            }
            if (D_00387E88 == 1) {
                i++;
                s0 += 0x10;
                continue;
            }
        }

        D_00387F28 = (s32)(*(u8 **)(gBtlStage + 0x5C) + *(s32 *)(s0 + 0x8) * 4);
        r = ColMesh_WalkBox(*(u8 **)(gBtlStage + 0x5C) + *(s32 *)(s0 + 0x8) * 4, arg2, arg3, arg4);
        if (r != 0) {
            *(u8 *)(arg0 + 0) = 1;
            *(u64 *)(arg0 + 0x8) |= (u64)1 << (i & 63);
            *(u8 *)(arg0 + 0x2) = 1;
            if (*(s32 *)s0 == 0) {
                *(u8 *)(arg0 + 0x3) = 1;
                *(u64 *)(arg0 + 0x10) |= (u64)1 << (*(s32 *)(s0 + 4) & 63);
            }
        }
        i++;
        s0 += 0x10;
    }

    return *(u8 *)arg0;
}
