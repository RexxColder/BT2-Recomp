#include "common.h"

extern u8 gFontStyle[];

void Font_GetClip(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    *arg0 = *(u16 *)(gFontStyle + 0x2C);
    *arg1 = *(u16 *)(gFontStyle + 0x2E);
    *arg2 = *(u16 *)(gFontStyle + 0x30);
    *arg3 = *(u16 *)(gFontStyle + 0x32);
}
