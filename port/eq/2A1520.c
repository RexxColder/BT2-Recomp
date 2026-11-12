#include "common.h"
extern u8 gFontStyle[] __attribute__((section(".data")));

void func_002A1520(s32 *arg0, s32 *arg1) {
    *arg0 = *(s32 *)(gFontStyle + 0x10);
    *arg1 = *(s32 *)(gFontStyle + 0x14);
}
