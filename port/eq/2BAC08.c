#include "common.h"

s32 Rand_Range();
s32 func_002B8280(s32 arg0, s32 arg1);
s32 func_002FFC08(s32 arg0, s32 arg1);
extern u8 D_00379A90[] __attribute__((section(".data")));
extern u8 D_00379AC0[] __attribute__((section(".data")));
extern u8 D_00379AF0[] __attribute__((section(".data")));

void func_002BAC08(s32 arg0, s32 arg1) {
    if (func_002B8280(arg0, arg1) != 1) {
        Rand_Range((s32)D_00379A90);
        return;
    }
    if (arg1 != 0) {
        if (func_002FFC08(*(s32 *)((u8 *)arg0 + 0x48), arg1) < 0) {
            *(s32 *)((u8 *)arg0 + 0x04) = 4;
            Rand_Range((s32)D_00379AF0, arg1);
            return;
        }
        *(s32 *)((u8 *)arg0 + 0x74) = *(s32 *)((u8 *)arg0 + 0x74) + 1;
        return;
    }
    Rand_Range((s32)D_00379AC0);
}
