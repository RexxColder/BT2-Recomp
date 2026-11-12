#include "common.h"

void BtlFacade_BeginWait(void);
void func_002FB820(void);
void func_002FB850(void *arg0);
void func_002FB878(void *arg0);
void func_00306F10(s32 arg0);
extern u8 D_00355338[] __attribute__((section(".data")));
extern s32 D_00355374 __attribute__((section(".data")));
extern s32 D_00355394 __attribute__((section(".data")));

void func_002FB9F0(void *arg0) {
    s16 s0;
    s32 s2;
    u8 temp_v0;
    s32 v1;

    s0 = 0;
    while (s0 < 0x3E8) {
        BtlFacade_BeginWait();
        if (D_00355374 == 1) {
            func_00306F10((s32)&D_00355374);
            func_002FB820();
            s0 += 1;
            continue;
        }
        D_00355374 = 1;
        func_00306F10((s32)&D_00355374);
        break;
    }
    s2 = *(s8 *)((u8 *)arg0 + 2);
    if (s2 == 2) {
        if ((s8)D_00355338[1] == 1) {
            func_002FB850(arg0);
        }
        temp_v0 = D_00355338[1];
        if ((s8)temp_v0 == s2) {
            func_002FB878(arg0);
        }
        v1 = *(s8 *)((u8 *)arg0 + 2);
        if (v1 != 9) {
            *(s8 *)((u8 *)arg0 + 2) = 3;
            D_00355394 += 1;
        }
    }
    D_00355374 = 0;
}
