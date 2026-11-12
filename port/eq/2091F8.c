#include "common.h"

s32 BtlObjVis_GetView_207EA0(s32 arg0);
u8 *func_00269A08(s32 arg0, s32 arg1);

void func_002091F8(s32 arg0, u8 *arg1, s32 arg2) {
    s32 view = BtlObjVis_GetView_207EA0(arg0);
    u8 *obj = NULL;

    if (view != 0) {
        obj = func_00269A08(view, arg2);
    }
    if (obj != NULL) {
        *(f32 *)(arg1 + 0) = *(f32 *)(obj + 0x50);
        *(f32 *)(arg1 + 4) = *(f32 *)(obj + 0x54);
        *(f32 *)(arg1 + 8) = *(f32 *)(obj + 0x58);
    } else {
        *(s32 *)(arg1 + 8) = 0;
        *(s32 *)(arg1 + 0) = 0;
        *(s32 *)(arg1 + 4) = 0;
    }
}
