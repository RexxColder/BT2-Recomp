#include "common.h"

s32 func_001FA3A8();
void func_0025F130();
void BtlObjAnim_RebaseRoot();

void func_001F9A20(s32 arg0, s32 arg1) {
    if (arg0 != 0) {
        if (func_001FA3A8(arg1, arg1) & 0x100) {
            func_0025F130(arg0, 1, 1, 1);
            return;
        }
        if (func_001FA3A8(arg1, 1, 1, 1) & 0x200) {
            BtlObjAnim_RebaseRoot(arg0);
            if (func_001FA3A8(arg1) & 2) {
                func_0025F130(arg0, 1, 0, 0);
            }
        }
    }
}
