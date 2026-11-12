#include "common.h"

s32 func_002FC410(void);
void func_00331710(s32 arg0, s32 arg1);
extern u8 D_00355338[] __attribute__((section(".data")));
extern s32 D_00355374 __attribute__((section(".data")));
extern s32 D_0035538C __attribute__((section(".data")));
extern u8 D_0037DF98[] __attribute__((section(".data")));
extern u8 D_0037DFA8[] __attribute__((section(".data")));
extern u8 D_0037DFC8[] __attribute__((section(".data")));
extern u8 D_0037DFE8[] __attribute__((section(".data")));
extern u8 D_0037E008[] __attribute__((section(".data")));
extern u8 D_0037E028[] __attribute__((section(".data")));
extern u8 D_0037E048[] __attribute__((section(".data")));

/* arg1 is not written before the first call: it is passed through to func_00331710 (GUESS arity 2) */
s32 func_002FC460(s32 arg0, s32 arg1) {
    u8 temp_a1;

    func_00331710((s32)D_0037DF98, arg1);
    func_00331710((s32)D_0037DFA8, D_00355374);
    func_00331710((s32)D_0037DFC8, D_0035538C);
    func_00331710((s32)D_0037DFE8, (s32)(s8)D_00355338[2]);
    temp_a1 = D_00355338[1];
    if ((s8)D_00355338[1] == 1) {
        func_00331710((s32)D_0037E008, (s32)temp_a1);
    }
    if ((s8)temp_a1 == 2) {
        func_00331710((s32)D_0037E028, (s32)temp_a1);
    }
    func_00331710((s32)D_0037E048, func_002FC410());
    return 0;
}
