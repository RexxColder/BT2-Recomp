#include "common.h"
extern u8 gFontStyle[] __attribute__((section(".data")));

void func_002A1628(s32 *arg0, s32 *arg1) {
    *arg0 = *(u16 *)(gFontStyle + 0x28);
    *arg1 = *(u16 *)(gFontStyle + 0x2A);
}
