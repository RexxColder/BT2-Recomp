#include "common.h"

s32 BtlTaskList_AddTail(s32 arg0, void *arg1, void *arg2);
s32 func_001C93F0(s32 arg0, s32 arg1);
void func_001C9358(void *arg0, void *arg1, s32 arg2);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern s32 D_00342C30 __attribute__((section(".data")));
extern u8 *D_003878B4;

void func_001C9448(s32 arg0) {
    s32 sp[16];
    u8 *a2;
    s32 found;
    s32 v0;
    s32 temp;

    memset(sp, 0, 0x40);
    sp[12] = arg0;
    if (D_003878B4 != NULL) {
        found = 0;
        a2 = *(u8 **)(D_003878B4 + 0x120);
        if (a2 != NULL) {
            v0 = *(s32 *)a2;
            for (;;) {
                if (v0 != 0 && *(s32 *)(a2 + 4) == arg0) {
                    found = 1;
                    break;
                }
                a2 = *(u8 **)(a2 + 0xC);
                if (a2 == NULL) {
                    break;
                }
                v0 = *(s32 *)a2;
            }
        }
        if (!found) {
            sp[0] = *(s32 *)D_003878B4;
            temp = BtlTaskList_AddTail(*(s32 *)(D_003878B4 + 0x164), &D_00342C30, sp);
            temp = func_001C93F0(temp, arg0);
            if (temp != 0) {
                func_001C9358(D_003878B4 + 0x120, D_003878B4 + 0x124, temp);
            }
        }
    }
}
