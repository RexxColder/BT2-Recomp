#include "m2c_macros.h"

M2C_UNK func_0028BB60(s32);                         /* extern */
extern s8 D_00387DF0;
extern s8 D_00387DF1;
extern s32 D_00387EDC;
extern s32 D_00387EE4;
extern s32 D_00387EE8;
extern s32 gFontCursorStack;

void func_002A0780(void) {
    if (D_00387EDC != 0) {
        func_0028BB60(D_00387EDC);
        D_00387EDC = 0;
    }
    if (gFontCursorStack != 0) {
        func_0028BB60(gFontCursorStack);
        gFontCursorStack = 0;
    }
    if (D_00387EE4 != 0) {
        func_0028BB60(D_00387EE4);
        D_00387EE4 = 0;
    }
    if (D_00387EE8 != 0) {
        func_0028BB60(D_00387EE8);
        D_00387EE8 = 0;
    }
    D_00387DF0 = 0;
    D_00387DF1 = 0;
}
