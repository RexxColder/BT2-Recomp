#include "m2c_macros.h"

void func_001E2F60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0);

void func_001E1938(void *arg0, s32 arg1, s32 arg2, f32 farg0) {
    u8 *a = (u8 *)arg0;

    if (*(u8 *)(a + 0x16B) != 0) {
        func_001E2F60((s32)(a + 0x10), (s32)(a + 0x60), arg1, arg2 & 0xFF, farg0);
    }
}
