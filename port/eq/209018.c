#include "common.h"

/* GUESS arity: BtlObjVis_GetView_207EA0 gets arg0 (a0 passed through in the asm); ctx.h says 0 */
s32 BtlObjVis_GetView_207EA0(s32 arg0);
void func_00260CB8(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_002C3630[] __attribute__((section(".data")));

void func_00209018(s32 arg0, s32 arg1, s32 arg2) {
    s32 view;

    view = BtlObjVis_GetView_207EA0(arg0);
    if (view == 0) {
        func_003126C8(arg1, (s32)D_002C3630, arg2);
        return;
    }
    func_00260CB8(view, arg1, arg2);
}
