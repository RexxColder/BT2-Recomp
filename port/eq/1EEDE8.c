#include "common.h"

s32 func_0020B3D0(s32 arg0);
void func_00208860(s32 arg0, s32 arg1);
void func_00129B58(s32 arg0, s32 arg1, s32 arg2);

void EftVolleyAim_GetToOpponent(s32 arg0, s32 arg1) {
    s32 buf[8];

    func_00208860(func_0020B3D0(arg0), (s32)buf);
    func_00208860(arg0, (s32)&buf[4]);
    func_00129B58(arg1, (s32)buf, (s32)&buf[4]);
}
