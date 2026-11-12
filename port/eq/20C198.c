#include "common.h"

f32 func_0020DB08(s32 arg0, s32 arg1);
s32 func_00211288(s32 arg0);
extern s32 D_00387930;

f32 func_0020C198(u32 arg0) {
    if (D_00387930 != 0 && arg0 < 2) {
        return func_0020DB08(func_00211288(arg0), 2);
    }
    return 0.0f;
}
