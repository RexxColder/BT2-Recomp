#include "common.h"

s32 func_00129C28(s32 arg0, s32 arg1);
extern s32 *D_0038780C;

s32 func_001A1378(s32 arg0, s32 arg1) {
    u8 *e = (u8 *)D_0038780C[arg0];
    s32 v = 0;

    if (e != NULL) {
        func_00129C28(arg1, *(s32 *)(e + 0x38) + 0x60);
        v = 1;
    }
    return v;
}
