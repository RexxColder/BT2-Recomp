#include "common.h"

void func_00306F28(s32 arg0);
void func_00331710(s32 arg0, s32 arg1, s32 arg2);
void func_002FB520(void);
void func_00306FA0(void);
extern s8 D_00355338[] __attribute__((section(".data")));
extern s32 D_0035539C __attribute__((section(".data")));
extern u8 D_0037DE00[] __attribute__((section(".data")));
extern u8 D_0037DE40[] __attribute__((section(".data")));

void func_002FB5D8(u8 *arg0) {
    s8 temp_a0;

    func_00306F28((s32)arg0);
    if (arg0 != (u8 *)D_00355338) {
        func_00331710((s32)D_0037DE00, (s32)arg0, (s32)D_00355338);
    } else {
        temp_a0 = *(s8 *)(arg0 + 2);
        if ((temp_a0 != 0) && (temp_a0 != 3) && (temp_a0 != 9)) {
            func_00331710((s32)D_0037DE40, (s32)arg0, (s32)D_00355338);
        }
        func_002FB520();
        D_00355338[0] = 0;
        D_0035539C += 1;
    }
    func_00306FA0();
}
