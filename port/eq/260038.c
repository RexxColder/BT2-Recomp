#include "common.h"

extern u8 *D_00387A40;

s32  func_00260038(s32 arg0) {
    u8 var_v0;

    var_v0 = 0;
    if (arg0 < 0x31) {
        var_v0 = *(*(u8 **) ((u8 *) D_00387A40 + 0x38204) + arg0);
    }
    return (u8)(var_v0);
}
