#include "m2c_macros.h"

void *func_00211288(s32 arg0);
extern s32 D_00387930;

s32  func_0020B7E0(u32 arg0) {
    if (D_00387930 != 0 && arg0 < 2) {
        return (u8)(*(u8 *)((u8 *)func_00211288((s32)arg0) + 0xBD4));
    }
    return (u8)(0);
}
