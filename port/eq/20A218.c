#include "common.h"

s32 BtlObjVis_GetView_207EA0(s32 arg0);
s32 func_0025FBE8(s32 arg0, u64 arg1);

s32 BtlCharApi_ObjTestAttr(s32 arg0, u64 arg1) {
    s32 view = BtlObjVis_GetView_207EA0(arg0);

    if (view != 0) {
        return func_0025FBE8(view, arg1);
    }
    return 0;
}
