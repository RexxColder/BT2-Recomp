#include "common.h"

/* 0x00148568: s0 = *(D_00387760 + 4) + 624*a0 + 80*a1; if (s0->+0x1C == 0) return 0;
   idx = *(s32 *)s0->+0x20; v0 = 12*idx; t = *(D_00340260 + 12*idx); if (!t) return v0;
   v0 = BtlTaskList_AddTail(*(s32 *)(a3 + 0x258), t, s0); s0->+0x28 = v0; return v0. */
extern u8 *D_00387760;
extern u8 D_00340260[];
s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);

s32 func_00148568(s32 a0, s32 a1) {
    u8 *a3;
    u8 *s0;
    u8 *v1;
    s32 idx;
    s32 v0;

    if (D_00387760 == NULL) {
        return 0;
    }
    a3 = *(u8 **)(D_00387760 + 4) + a0 * 624;
    s0 = a3 + a1 * 80;
    v0 = *(s32 *)(s0 + 0x1C);
    if (v0 == 0) {
        return 0;
    }
    v1 = *(u8 **)(s0 + 0x20);
    idx = *(s32 *)v1;
    v0 = idx * 12;
    v1 = *(u8 **)(D_00340260 + v0);
    if (v1 == NULL) {
        return v0;
    }
    v0 = BtlTaskList_AddTail(*(s32 *)(a3 + 0x258), (s32)v1, (s32)s0);
    *(s32 *)(s0 + 0x28) = v0;
    return v0;
}
