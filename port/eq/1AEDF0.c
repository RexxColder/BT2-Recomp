#include "m2c_macros.h"

s32 func_003126C8(s32 arg0, void *arg1);
extern u8 *D_003876A0;

void func_001AEDF0(void *arg0) {
    u8 *a = (u8 *)arg0;

    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x100) && (*(s32 *)(a + 4) & 0x3F)) {
        func_003126C8(*(s32 *)(a + 0x38), a + 0x10);
    }
}
