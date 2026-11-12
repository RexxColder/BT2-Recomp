#include "common.h"

void *memset(void *arg0, s32 arg1, s32 arg2);
void *memcpy(void *arg0, void *arg1, s32 arg2);
s32 BtlPool_GetCurrent(void);
s32 BtlPool_Alloc(s32 arg0, s32 arg1);
s32 EftTexSet_Load32(s32 arg0, s32 arg1);
s32 EftTexSet_Load16(s32 arg0, s32 arg1);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
s32 func_00126460(s32 arg0);
void func_001EC288(s32 arg0, s32 arg1);
void func_001EC308(s32 arg0, s32 arg1);
s32 func_001EC368(s32 arg0, s32 arg1);
extern u8 D_00387858[] __attribute__((section(".data")));
extern u8 D_0038785C[] __attribute__((section(".data")));
extern u8 D_00387860[] __attribute__((section(".rodata")));
extern u8 D_00387868[] __attribute__((section(".rodata")));

/* 0x001AE608: battle-side object setup (pool allocations at G+8, G+0x170,
 * a texture-id table at G+0x174 and the child task list). */
s32 func_001AE608(s32 a0) {
    u8 sp[0x20];
    s32 g;
    s32 i;
    s32 s2;
    s32 s3;
    s32 r;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 z;
    s32 w;

    g = *(s32 *)D_00387858;
    if (g == 0) {
        g = BtlPool_Alloc(BtlPool_GetCurrent(), 0x6B0);
        *(s32 *)D_00387858 = g;
        memset((void *)g, 0, 0x6B0);
    }
    g = *(s32 *)D_00387858;
    memset((void *)g, 0, 0x6B0);

    g = *(s32 *)D_00387858;
    if (*(s32 *)(g + 8) == 0) {
        *(s32 *)(g + 8) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x8C00);
        g = *(s32 *)D_00387858;
        memset((void *)*(s32 *)(g + 8), 0, 0x8C00);
        g = *(s32 *)D_00387858;
    }
    if (*(s32 *)(g + 0x170) == 0) {
        *(s32 *)(g + 0x170) = BtlPool_Alloc(BtlPool_GetCurrent(), 0x208);
        g = *(s32 *)D_00387858;
        memset((void *)*(s32 *)(g + 0x170), 0, 0x208);
        g = *(s32 *)D_00387858;
    }
    s3 = g + 0x590;

    for (i = 0; i < 16; i++) {
        *(s32 *)(g + i * 12 + 0xC) = 0;
        *(s32 *)(g + i * 12 + 0x10) = 0;
        *(s32 *)(g + i * 12 + 0x14) = 0;
    }
    for (i = 0; i < 2; i++) {
        *(s32 *)(g + i * 4 + 0xCC) = 0;
        *(s32 *)(g + i * 4 + 0xD4) = 0;
        *(s32 *)(g + i * 4 + 0xDC) = 0;
    }

    memcpy(sp, D_00387860, 8);
    memcpy(sp + 0x10, D_00387868, 8);

    r = func_00126460(0x2B);
    s2 = 0;
    EftTexSet_Load32(*(s32 *)(g + 0x170), r);
    r = func_00126460(0x2F);
    func_001EC288(g + 0xF0, r);
    func_001EC308(g + 0xF0, *(s32 *)(g + 0x170));
    func_001EC368(g + 0xF0, 1);

    for (i = 0; i < 2; i++) {
        z = func_00126460(*(s32 *)(sp + i * 4));
        EftTexSet_Load32(g + s2 + 0x180, z);
        s2 += 0x208;
        w = func_00126460(*(s32 *)(sp + 0x10 + i * 4));
        *(s32 *)(g + i * 4 + 0x174) = w;
    }

    r1 = func_00126460(0x2D);
    r2 = func_00126460(0x2C);
    *(s32 *)(s3 + 0x10C) = r1;
    r3 = func_00126460(0x2E);
    *(s32 *)(s3 + 0x110) = r2;
    *(s32 *)(s3 + 0x108) = r3;
    EftTexSet_Load16(s3, r3);

    r = BtlTask_CreateChildList(a0, 0x10, 0x1D0);
    *(s32 *)D_0038785C = r;
    return r;
}
