#include "common.h"

void func_001DF600(s32 arg0, f32 farg0);
extern s32 D_003876A0;
extern s32 D_003878E0;

void func_001DF550(void) {
    s32 i;

    if ((*(s64 *)(D_003876A0 + 0x4D8) & 2) == 0) {
        func_001DF600(0, *(f32 *)D_003878E0);
        return;
    }
    for (i = 0; i < 2; i++) {
        func_001DF600(i, *(f32 *)(D_003878E0 + i * 4));
    }
}
