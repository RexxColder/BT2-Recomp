#include "m2c_macros.h"

s32 func_0032EB50();                                /* extern */
M2C_UNK func_0032ECA0(s32);                         /* extern */
extern s32 D_0036AA60 __attribute__((section(".data")));
extern s32 D_0036AA64 __attribute__((section(".data")));
extern s32 D_0036AB58 __attribute__((section(".data")));

void __malloc_lock(void) {
    s32 temp_v0;

    temp_v0 = func_0032EB50();
    if (D_0036AA60 == temp_v0) {
        D_0036AA64 += 1;
        return;
    }
    func_0032ECA0(D_0036AB58);
    D_0036AA60 = temp_v0;
    D_0036AA64 += 1;
}
