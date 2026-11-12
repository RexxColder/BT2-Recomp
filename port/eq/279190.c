#include "common.h"

extern s32 D_00387AD8 __attribute__((section(".data")));
extern u8 *gOt __attribute__((section(".data")));

s32 func_00279190(void) {
    s32 var_v0;

    var_v0 = 0;
    if ((D_00387AD8 != 0) && (gOt != NULL) && (*(s32 *)(gOt + 0x28) != 0)) {
        var_v0 = *(s32 *)(gOt + 0x30) - 0x10;
    }
    return var_v0;
}
