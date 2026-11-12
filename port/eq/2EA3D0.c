#include "common.h"

extern u8 D_0037BAC8[];
extern u8 D_0037BB00[];
s32 func_002EA050(s32 arg0, s32 arg1);

s32 func_002EA3D0(u32 arg0, s32 arg1) {
    if (arg0 >= 0x100) {
        func_002EA050((s32)D_0037BAC8, arg1);
        return -3;
    }
    if (arg1 != 0) {
        return 0;
    }
    func_002EA050((s32)D_0037BB00, arg1);
    return -3;
}
