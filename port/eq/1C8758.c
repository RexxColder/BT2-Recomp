#include "common.h"

s32 *BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent(void);
void BtlPool_SetCurrent(s32 arg0);
void BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
s32 func_00126560(void);
s32 func_001F4588(void);
extern s32 D_00342A40[] __attribute__((section(".data")));
extern s32 D_00342A44[] __attribute__((section(".data")));
extern s32 *gEftLayer3;

void func_001C8758(s32 arg0) {
    s32 *s0;
    s32 s2;
    s32 *p;

    s2 = 0;
    BtlPool_SetCurrent(1);
    p = BtlPool_Alloc(BtlPool_GetCurrent(), 4);
    gEftLayer3 = p;
    *p = 0;
    *gEftLayer3 = BtlTask_CreateChildList(arg0, 0x3B, 0);

    s0 = D_00342A44;
    do {
        if (func_00126560() == 0) {
            if (s0[0] & 1) {
                BtlTaskList_AddTail(*gEftLayer3, *(s32 *)((u8 *)D_00342A40 + s2), 0);
            }
        } else {
            if (s0[0] & 2) {
                BtlTaskList_AddTail(*gEftLayer3, *(s32 *)((u8 *)D_00342A40 + s2), 0);
            }
            if ((s0[0] & 4) && (func_001F4588() != 0)) {
                BtlTaskList_AddTail(*gEftLayer3, *(s32 *)((u8 *)D_00342A40 + s2), 0);
            }
        }
        s0 += 2;
        s2 += 8;
    } while ((u8 *)s0 < (u8 *)D_00342A44 + 0x1D8);
}
