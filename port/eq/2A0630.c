#include "common.h"

s32 func_0028BAA8(s32 arg0);
void func_002A2358(s32 arg0, s32 arg1);
void memset(void *arg0, s32 arg1, s32 arg2);
extern u8 *D_003876A0;
extern s8 D_00387DF0;
extern s8 D_00387DF1;
extern s32 D_00387EDC;
extern s32 D_00387EE4;
extern s32 D_00387EE8;
extern s32 D_00387EF0;
extern s32 D_00387EF4;
extern s32 D_00387EF8;
extern u8 gFontCursor[] __attribute__((section(".data")));
extern u8 gFontStyle[] __attribute__((section(".data")));
extern s32 gFontCursorDepth;
extern s32 gFontCursorStack;

void Font_InitEx(s32 arg0, s32 arg1) {
    s32 temp;
    u8 *s0;

    *(s32 *)(gFontCursor + 0xC) = 0x10;
    *(s16 *)(gFontStyle + 0x32) = 0x1BF;
    D_00387DF1 = 1;
    *(s32 *)(gFontStyle + 0xC) = (s32)0x80FFFFFF;
    *(f32 *)(gFontStyle + 4) = 1.0f;
    *(s32 *)(gFontStyle + 0x24) = (s32)0x80808080;
    *(s16 *)(gFontStyle + 0x28) = 1;
    *(s16 *)(gFontStyle + 0x2A) = 2;
    *(s16 *)(gFontStyle + 0x30) = 0x1FF;
    D_00387DF0 = 1;
    *(s32 *)(gFontCursor + 0) = 0x10;
    *(s32 *)(gFontCursor + 4) = 0x10;
    *(s32 *)(gFontCursor + 8) = 0x10;
    *(f32 *)(gFontStyle + 8) = 1.0f;
    *(f32 *)(gFontStyle + 0) = 1.0f;
    *(s32 *)(gFontStyle + 0x20) = 1;
    *(s32 *)(gFontStyle + 0x10) = 0;
    *(s32 *)(gFontStyle + 0x14) = 0;
    *(s32 *)(gFontStyle + 0x18) = 0;
    *(s32 *)(gFontStyle + 0x1C) = 0;
    *(s16 *)(gFontStyle + 0x2C) = 0;
    *(s16 *)(gFontStyle + 0x2E) = 0;

    D_00387EDC = func_0028BAA8(0xA0);
    gFontCursorStack = func_0028BAA8(0x50);
    D_00387EE4 = func_0028BAA8(0x140);
    temp = func_0028BAA8(arg1 * 0x4C);
    gFontCursorDepth = 0;
    D_00387EF8 = arg1;
    D_00387EE8 = temp;
    D_00387EF0 = 0;
    D_00387EF4 = 0;
    memset((void *)D_00387EDC, 0, 0xA0);

    s0 = *(u8 **)(D_003876A0 + 0x70);
    func_002A2358(0, (s32)(s0 + ((*(u32 *)(s0 + 4) >> 2) * 4)));
    func_002A2358(1, (s32)(s0 + ((*(u32 *)(s0 + 8) >> 2) * 4)));
}
