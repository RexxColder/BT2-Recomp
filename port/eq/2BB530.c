#include "common.h"

s32 func_002B8328(s32 arg0);
s32 func_002B8398(s32 arg0);
void func_002BB5F8(s32 arg0);
s32 func_002BB6B0(s32 arg0);
void func_002BB770(s32 arg0);

void func_002BB530(s32 arg0) {
    s32 temp_v0;
    s32 var_v1;

    if ((*(s32 *)((u8 *)arg0 + 0x2D8) != 0) && (*(s32 *)((u8 *)arg0 + 0x2DC) != 0)) {
        var_v1 = *(s32 *)((u8 *)arg0 + 0x2E8);
        if (var_v1 == 1) {
            temp_v0 = func_002B8328(arg0);
            if (temp_v0 != 2) {
                var_v1 = *(s32 *)((u8 *)arg0 + 0x2E8);
                goto block_8;
            }
            var_v1 = 2;
            if (func_002BB6B0(arg0) >= 0) {
                *(s32 *)((u8 *)arg0 + 0x2E8) = temp_v0;
                goto block_8;
            }
        } else {
block_8:
            if ((u32)(var_v1 - 2) < 2U) {
                if (func_002B8398(arg0) == 3) {
                    func_002BB5F8(arg0);
                }
                func_002BB770(arg0);
            }
        }
    }
}
