#include "common.h"

void func_002E73E0(s32 arg0);
void func_002E7538(s32 arg0);
s32 func_002F8C68(void);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern s16 D_00347BF8[] __attribute__((section(".data")));
void func_002E7390(void);
void func_002E73C0(void);

void *func_002E7418(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 idx;
    s16 *v1;
    u8 *s0;
    s32 temp;

    v1 = D_00347BF8;
    idx = 0;
    if (D_00347BF8[0] != 0) {
        idx = 1;
        for (;;) {
            v1 = (s16 *)((u8 *)v1 + 0x104);
            if (idx >= 0x10 || *v1 == 0) {
                break;
            }
            idx++;
        }
    }
    if (idx == 0x10) {
        return NULL;
    }
    s0 = (u8 *)D_00347BF8 + idx * 0x104;
    memset(s0, 0, 0x104);
    *(s16 *)s0 = 1;
    temp = func_002F8C68();
    *(s32 *)(s0 + 8) = temp;
    if (temp == 0) {
        func_002E7538((s32)s0);
        return NULL;
    }
    *(s32 *)(s0 + 0x78) = (s32)func_002E7390;
    *(s32 *)(s0 + 0x38) = arg0;
    *(s32 *)(s0 + 0x3C) = arg1;
    *(s32 *)(s0 + 0x40) = arg2;
    *(s32 *)(s0 + 0x44) = arg3;
    *(s32 *)(s0 + 0x80) = (s32)func_002E73C0;
    *(s32 *)(s0 + 0x7C) = (s32)s0;
    *(s32 *)(s0 + 0x84) = (s32)s0;
    func_002E73E0((s32)s0);
    return s0;
}
