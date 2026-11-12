#include "common.h"

/* 0x00208DE8: s1 = BtlObjVis_GetView_207EA0(a0); if (!s1) return func_003126C8(a1, &D_002C3630, a2);
   v = func_00269A40(s1); return func_003126C8(a1, v ? v + 0x30 : s1 + 0x9A0) (a2 not restored, left as the callee left it). */
extern u8 D_002C3630[];
s32 BtlObjVis_GetView_207EA0(s32 arg0);
s32 func_00269A40(s32 arg0, s32 arg1);
s32 func_003126C8();

s32 func_00208DE8(s32 a0, s32 a1, s32 a2) {
    u8 *s1;
    s32 v;

    s1 = (u8 *)BtlObjVis_GetView_207EA0(a0);
    if (s1 == NULL) {
        return func_003126C8(a1, (s32)D_002C3630, a2);
    }
    v = func_00269A40((s32)s1, a2);
    if (v != 0) {
        return func_003126C8(a1, v + 0x30);
    }
    return func_003126C8(a1, (s32)(s1 + 0x9A0));
}
