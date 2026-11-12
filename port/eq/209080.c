#include "common.h"

extern u8 D_002C3630[];
extern u8 *BtlObjVis_GetView_207EA0(s32 a0);
extern u8 *func_00269A40(u8 *a0, s32 a1);
extern s32 func_003126C8(s32 a0, u8 *a1);

s32 func_00209080(s32 obj, s32 dst, s32 key) {
    u8 *view;
    u8 *ent;

    view = BtlObjVis_GetView_207EA0(obj);
    if (view == 0) {
        return func_003126C8(dst, D_002C3630);
    }
    ent = func_00269A40(view, key);
    if (ent == 0) {
        return func_003126C8(dst, D_002C3630);
    }
    return func_003126C8(dst, ent + 0x90);
}
