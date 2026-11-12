#include "common.h"

s32 BtlCharApi_GetAuraType(s32 arg0);
s32 BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
void func_001CDBA8(s32 arg0, s32 arg1, s32 arg2);
s32 func_001CDC40(s32 arg0, s32 arg1);
void memset(void *arg0, s32 arg1, u32 arg2);
extern u8 D_00342EB0[] __attribute__((section(".data")));
extern u8 *D_003878C8;

void func_001CDC98(s32 arg0, s32 arg1) {
    s32 sp[4];
    s32 buf10[4];
    s32 buf20[4];
    s32 aura;
    s32 r;
    s32 r3;
    u8 *s1;
    s32 v1;

    (void)arg1;
    memset(buf10, 0, 0x10);
    memset(buf20, 0, 0x10);
    s1 = D_003878C8;
    if (s1 == NULL) {
        return;
    }
    v1 = *(s32 *)(s1 + 0x210);
    if (v1 != 0) {
        for (;;) {
            if (*(s32 *)(v1 + 4) == arg0) {
                if (*(s32 *)(v1 + 0) != 0) {
                    return;
                }
            }
            v1 = *(s32 *)(v1 + 0xC);
            if (v1 == 0) {
                break;
            }
        }
    }
    r = BtlCharApi_GetAuraType(arg0);
    aura = ((r ^ 7) == 0) ? 0 : r;
    if (aura == 8) {
        aura = 2;
    }
    sp[0] = *(s32 *)(s1 + 0);
    r = BtlTaskList_AddTail(*(s32 *)(s1 + 0x254), (s32)D_00342EB0, (s32)sp);
    r3 = func_001CDC40(r, arg0);
    if (r3 != 0) {
        func_001CDBA8((s32)(s1 + 0x210), (s32)(s1 + 0x214), r3);
    }
}
