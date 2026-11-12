#include "common.h"
extern u8 gFontStyle[] __attribute__((section(".data")));

void func_002A16C8(s32 mask, s32 bits) {
    *(s32 *)(gFontStyle + 0x34) = (*(s32 *)(gFontStyle + 0x34) & mask) | bits;
}
