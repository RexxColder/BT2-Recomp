#include "common.h"

/* 0x00105F30: memset(a0, 0, 0x10); v = *(D_003876A0 ptr)->+0xC0 (s32); *(u16 *)(a0 + 0xC) = D_0033F408[v] (halfword table). */
extern u8 D_003876A0[];
extern u8 D_0033F408[];

void func_00105F30(void *a0) {
    u8 *p;
    s32 idx;

    memset(a0, 0, 0x10);
    p = *(u8 **)D_003876A0;
    idx = *(s32 *)(p + 0xC0);
    *(u16 *)((u8 *)a0 + 0xC) = *(u16 *)(D_0033F408 + (idx << 1));
}
