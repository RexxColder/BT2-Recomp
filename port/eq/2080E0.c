#include "common.h"

u8 *func_00211288(s32 arg0);
s32 func_00203188(u8 *arg0, s32 arg1);
s32 func_00208060(u32 arg0, s32 arg1);
extern s32 D_00387930;

s32 func_002080E0(u32 arg0) {
    u8 *obj;
    s32 a1 = 0;

    if (D_00387930 == 0 || arg0 >= 2U) {
        return 0;
    }
    obj = func_00211288((s32)arg0);
    if (*(s32 *)(obj + 0x1184) > 0) {
        a1 = func_00203188(obj, 0);
    }
    return func_00208060(arg0, a1);
}
