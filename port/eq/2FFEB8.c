#include "m2c_macros.h"

void func_003007F8(void *arg0);
extern u8 D_0037E8E8 __attribute__((section(".data")));

void func_002FFEB8(void *arg0) {
    if (arg0 == NULL) {
        func_003007F8(&D_0037E8E8);
        return;
    }
    if (*(s8 *)((u8 *)arg0 + 1) == 0) {
        *(s32 *)((u8 *)arg0 + 0x24) = 0;
        *(s32 *)((u8 *)arg0 + 0x1C) = 0;
        *(s32 *)((u8 *)arg0 + 0x20) = 0;
    }
}
