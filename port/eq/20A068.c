#include "common.h"

u8 *func_00211288(s32 arg0);
extern s32 D_00387930;

f32 func_0020A068(u32 arg0) {
    if (D_00387930 != 0 && arg0 < 2) {
        return *(f32 *)(func_00211288(arg0) + 0xA30);
    }
    return 0.0f;
}
