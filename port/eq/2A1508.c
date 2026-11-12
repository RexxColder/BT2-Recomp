#include "common.h"

extern u8 gFontStyle[] __attribute__((section(".data")));

void func_002A1508(s32 arg0, s32 arg1) {
    *(s32 *)(gFontStyle + 0x14) = arg1;
    *(s32 *)(gFontStyle + 0x10) = arg0;
}
