#include "common.h"
extern u8 gFontCursor[] __attribute__((section(".data")));

void func_002A1218(s32 *arg0, s32 *arg1) {
    *arg0 = *(s32 *)(gFontCursor + 0x8);
    *arg1 = *(s32 *)(gFontCursor + 0xC);
}
