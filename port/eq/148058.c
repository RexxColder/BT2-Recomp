#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define ST32(p, off, v) (*(s32 *)((u8 *)(p) + (off)) = (s32)(v))

void *memset(void *dst, s32 c, u32 n);
void *memcpy(void *dst, const void *src, u32 n);
void BtlPool_SetCurrent(s32 arg0);
s32 BtlPool_GetCurrent(void);
s32 BtlPool_Alloc(s32 arg0, s32 arg1);
s32 func_00126580(void);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);

extern u8 *D_00387760;
extern u8 D_00387768[] __attribute__((section(".data")));
extern u8 D_00340248[] __attribute__((section(".data")));
extern u8 D_00341D20[] __attribute__((section(".data")));

/* 0x00148058: sets up the list block D_00387760 (0xC bytes: a task list entry +0, a pool block of 624 bytes per
 * item +4, an item count +8 from func_00126580). Clears the pool block, creates a child list under arg0 and
 * queues two entries (from D_00340248 with an 8-byte image of D_00387768) into it. */
void func_00148058(s32 arg0) {
    u8 sp[0x20];
    s32 g;
    s32 n;
    s32 sz;
    s32 p;
    s32 r;

    BtlPool_SetCurrent(3);
    g = BtlPool_Alloc(BtlPool_GetCurrent(), 0xC);
    D_00387760 = (u8 *)(s32)g;
    memset((void *)(s32)g, 0, 0xC);

    ST32(g, 0x8, func_00126580());
    n = LD32(g, 0x8);
    sz = n * 624;
    p = BtlPool_Alloc(BtlPool_GetCurrent(), sz);
    ST32(g, 0x4, p);
    memset((void *)(s32)p, 0, sz);

    ST32(g, 0x0, BtlTask_CreateChildList(arg0, LD32(g, 0x8) + 1, 0));
    BtlTaskList_AddTail(LD32(g, 0x0), (s32)D_00341D20, 0);

    memset(sp, 0, 8);
    memcpy(sp + 0x10, D_00387768, 8);

    r = BtlTaskList_AddTail(LD32(g, 0x0), (s32)D_00340248, (s32)(s32)sp);
    ST32(p, 0x25C, r);
    r = BtlTaskList_AddTail(LD32(g, 0x0), (s32)D_00340248, (s32)(s32)(sp + 0x10));
    ST32(p, 0x270 + 0x25C, r);
}
