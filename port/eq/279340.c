#include "common.h"

s32 func_002792E8(s32 arg0);
extern s32 D_00387AD8 __attribute__((section(".data")));
extern s32 gOt;

void Ot_BuildHeads(s32 arg0) {
    s32 temp_s4;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0x1001;
    temp_s4 = D_00387AD8;
    D_00387AD8 = *(s32 *) (gOt + arg0 * 4 + 0x20);
    var_s0 = *(s32 *) gOt;
    do {
        var_s1 -= 1;
        *(s32 *) (var_s0 + arg0 * 8) = func_002792E8(arg0);
        var_s0 += 0x10;
    } while (var_s1 >= 0);
    D_00387AD8 = temp_s4;
}
