#include "common.h"

s32 BtlObjVis_GetView_207EA0(s32 arg0);
void *func_00269A08(s32 arg0, s32 arg1);

/* float at +0x5C of func_00269A08(view, arg1), where view = BtlObjVis_GetView_207EA0(arg0);
 * 0.0f when there is no view, 1.0f when the view has no such entry */
f32 func_00209110(s32 arg0, s32 arg1) {
    f32 r = 0.0f;
    s32 view = BtlObjVis_GetView_207EA0(arg0);
    if (view != 0) {
        void *p = func_00269A08(view, arg1);
        r = 1.0f;
        if (p != NULL) {
            r = *(f32 *)((u8 *)p + 0x5C);
        }
    }
    return r;
}
