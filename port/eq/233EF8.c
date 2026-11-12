#include "common.h"

extern f32 D_0038693C;

extern s32 func_00211310();
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BtlAnim_SetBlend(void *arg0, f32 farg0);
extern s32 func_00212890();
s32 func_0023C710(s32 arg0);

s32 func_00233EF8(u8 *obj) {
    if (func_00211310(obj, 2, 1) == 0) {
        return -1;
    }
    func_002113C0(obj, 5, 0x100, 1);
    BtlAnim_SetBlend(obj, D_0038693C);
    func_00212890(0x5A);
    return func_0023C710((s32)obj);
}
