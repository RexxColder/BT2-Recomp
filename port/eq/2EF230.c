#include "common.h"

void func_002EE3A0(s32 arg0);
s32 func_002EE408(s32 arg0);
s32 func_002EE8A8(void);
extern s32 D_0034BC0C __attribute__((section(".data")));
extern s32 D_0034BC10 __attribute__((section(".data")));

void BtlChars_OnStageLoaded(void) {
    if (func_002EE408(D_0034BC0C) == D_0034BC0C) {
        func_002EE3A0(D_0034BC0C);
    }
    if (func_002EE8A8() == 1) {
        if (func_002EE408(D_0034BC10) == D_0034BC10) {
            func_002EE3A0(D_0034BC10);
        }
    }
}
