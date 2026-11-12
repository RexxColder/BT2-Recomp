#include "common.h"

s32 func_00129C28(s32 arg0, s32 arg1);
extern s32 *D_0038780C;

s32 func_001A1298(s32 arg0, s32 arg1) {
    u8 *obj = (u8 *)D_0038780C[arg0];

    if (obj != NULL) {
        func_00129C28(*(s32 *)(obj + 0x38) + 0x10, arg1);
        return 1;
    }
    return 0;
}
