#include "common.h"

void func_0012B748(u8 *arg0, u8 *arg1, f32 farg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        f32 f0 = *(f32 *)(arg1 + i * 4);
        f32 f1 = *(f32 *)(arg1 + 0x10 + i * 4);

        f1 = f1 - f0;
        f1 = f1 * farg0;
        *(f32 *)(arg0 + i * 4) = f0 + f1;
    }
    *(s32 *)(arg0 + 0xC) = 0;
}
