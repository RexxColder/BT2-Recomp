#include "common.h"

s32 func_002B7CB8(s32 arg0);
void func_002B2A20(s32 arg0, s32 arg1, s32 arg2);
void BtlObjAnim_PlayModel(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_002B4E00 __attribute__((section(".data")));

void func_002B4D38(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_002B7CB8(arg0);
    if (arg1 == 0) {
        BtlObjAnim_PlayModel(temp_v0, 0, 0);
        return;
    }
    func_002B2A20(*(s32 *) (arg0 + 0x2D0), arg1, 0);
    BtlObjAnim_PlayModel(temp_v0, (s32) func_002B4E00, arg0);
}
