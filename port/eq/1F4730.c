#include "common.h"

s32 func_001F4300();
s32 func_001F4280(s32 arg0);
s32 func_001F4598(s32 arg0);
void *func_001F49E8(s32 arg0, s32 arg1);
s32 BtlPool_Alloc(s32 arg0, s32 arg1);
s32 BtlPool_GetCurrent(void);
void BtlPool_SetCurrent(s32 arg0);
s32 BtlTask_CreateChildList(s32 arg0, s32 arg1, s32 arg2);
s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
void func_001489A8(void);
void *memset(void *s, s32 c, u32 n);
extern s32 *D_00387920;
extern s32 D_0038792C;

void func_001F4730(s32 arg0) {
    s32 count;
    s32 sp4;
    u8 *s0;
    s32 s1;

    if (func_001F4598(func_001F4300(arg0)) != 0) {
        D_0038792C |= 2;
    }
    BtlPool_SetCurrent(0);
    D_00387920 = (s32 *)BtlPool_Alloc(BtlPool_GetCurrent(), 0x70);
    memset(D_00387920, 0, 0x70);
    s0 = (u8 *)func_001F49E8(func_001F4300(), (s32)&count);
    if (s0 != NULL) {
        s1 = 0;
        *D_00387920 = BtlTask_CreateChildList(arg0, count, 0);
        func_001489A8();
        sp4 = 0;
        sp4 = func_001F4280(func_001F4300());
        if (count > 0) {
            do {
                if (*(s32 *)s0 != 0) {
                    if (func_001F4300() == *(s32 *)(s0 + 8)) {
                        ((s32 *)D_00387920)[s1 + 1] = BtlTaskList_AddTail(*D_00387920, *(s32 *)s0, (s32)&sp4);
                    }
                }
                s1++;
                s0 += 0xC;
            } while (s1 < count);
        }
    }
}
